// AdminInsertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminInsertDlg.h"
#include "FileIO.h"


// CAdminInsertDlg

IMPLEMENT_DYNCREATE(CAdminInsertDlg, CFormView)

CAdminInsertDlg::CAdminInsertDlg()
	: CFormView(DIALOG_ADM_INSERT)
	, m_coursename(_T(""))
	, m_classnum(0)
	//, m_courseid(_T(""))
	, m_courseid(0)
{

}

CAdminInsertDlg::~CAdminInsertDlg()
{
}

void CAdminInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_coursename);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT4, m_classnum);
	//  DDX_Text(pDX, IDC_EDIT5, m_courseid);
	DDX_Text(pDX, IDC_EDIT5, m_courseid);
}

BEGIN_MESSAGE_MAP(CAdminInsertDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminInsertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdminInsertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminInsertDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAdminInsertDlg 诊断

#ifdef _DEBUG
void CAdminInsertDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminInsertDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminInsertDlg 消息处理程序


void CAdminInsertDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 读取教师列表，添加到下拉控件中
	FileIO file;
	file.ReadUserInfo(2);	// 读取所有教师信息
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{
		m_combo.AddString(CString(it->teaname.c_str()));		// 添加所有老师
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CAdminInsertDlg::OnBnClickedButton3()
{	// 自动生成课程号
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	FileIO file;
	vector<CString> courselist = file.ReadCourseList();
	int num = courselist.size();
	m_courseid = num;
	UpdateData(FALSE);
}

void CAdminInsertDlg::OnBnClickedButton1()
{	// 点击添加新课程
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 读取总课程列表
	FileIO file;
	vector<CString> courselist = file.ReadCourseList();
	// 添加新课程到总课程表
	courselist.push_back(m_coursename);
	// 写入到文件中
	file.WriteCourseList(courselist);

	// 还要把申请课程的教师的课程列表更新
	// 先获取教师编号
	CString teanum;
	int index = m_combo.GetCurSel();
	file.ReadUserInfo(2);		// 所有的教师列表信息
	// 添加对应教师的课程表
	file.teals[index].courseList.push_back(m_courseid);
	// 写入教师课程表
	file.WriteTeaCourse();
	m_courseid = 0;
	m_classnum = 0;
	m_coursename.Empty();
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
	MessageBox(_T("课程添加成功"));
}


void CAdminInsertDlg::OnBnClickedButton2()
{	// 取消清空
	// TODO: 在此添加控件通知处理程序代码
	m_coursename.Empty();
	m_courseid = 0;
	m_classnum = 0;
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}
