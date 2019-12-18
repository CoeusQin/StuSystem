// TeaApplyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaApplyDlg.h"
#include "FileIO.h"


// CTeaApplyDlg

IMPLEMENT_DYNCREATE(CTeaApplyDlg, CFormView)

CTeaApplyDlg::CTeaApplyDlg()
	: CFormView(IDD_DIALOG2)
	, m_coursename(_T(""))
	, m_teaname(_T(""))
	, m_plan(_T(""))
{

}

CTeaApplyDlg::~CTeaApplyDlg()
{
}

void CTeaApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_coursename);
	DDX_Text(pDX, IDC_EDIT2, m_teaname);
	DDX_Text(pDX, IDC_EDIT3, m_plan);
}

BEGIN_MESSAGE_MAP(CTeaApplyDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CTeaApplyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTeaApplyDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTeaApplyDlg 诊断

#ifdef _DEBUG
void CTeaApplyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaApplyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaApplyDlg 消息处理程序


void CTeaApplyDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 将教师姓名默认输添加到申请人处
	// 初始化显示
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// 读取已登录用户信息

	char *info = strtok(buf, "|");
	string name = info;
	teanum = name.c_str();
	ifs.close();

	// 根据拿到的教师编号查找对应的教师信息，填充进对应的控件中
	FileIO file;
	teacher logintea = file.FindteacherById(teanum);
	m_teaname = (CString)logintea.teaname.c_str();

	UpdateData(FALSE);
}



void CTeaApplyDlg::OnBnClickedOk()
{	// 提交新课程申请
	// TODO: 在此添加控件通知处理程序代码
	// 检查数据合法性
	UpdateData(TRUE);
	if (m_coursename.IsEmpty() || m_plan.IsEmpty())
	{
		MessageBox(_T("课程名称或授课计划不能为空！"));
		return;
	}
	if (CStringA(m_plan).GetLength() >= 1000)
	{
		MessageBox(_T("授课计划字数过长，请限制在600字以内！"));
		return;
	}
	// 生成message结构体，并保存到对应的文件中
	message tmp;
	tmp.teanum = CStringA(teanum).GetBuffer();	// 教师编号
	tmp.teaname = CStringA(m_teaname).GetBuffer();	// 教师姓名
	tmp.coursename = CStringA(m_coursename).GetBuffer();	// 新课程名字
	m_plan.TrimRight();			// 去掉右侧空格
	m_plan.TrimLeft();			// 去掉左侧空格
	m_plan.Replace(_T(" "), _T(""));		// 去掉空格
	m_plan.Replace(_T("\r\n"), _T("&"));	// 用空格代替换行符
	tmp.courseplan = CStringA(m_plan).GetBuffer();		// 授课计划
	// 把这条申请提交到数据中
	FileIO file;
	// 先读取现存消息列表
	file.ReadMessage();
	// 把新消息添加进去
	file.messagev.push_back(tmp);
	// 把消息写入文件
	file.WriteMessage();
	MessageBox(_T("申请发送成功！"));
	m_coursename.Empty();
	m_plan.Empty();
	UpdateData(FALSE);
}



void CTeaApplyDlg::OnBnClickedCancel()
{	// 清空数据
	// TODO: 在此添加控件通知处理程序代码
	m_plan = _T("");
	m_coursename = _T("");
	UpdateData(FALSE);
}
