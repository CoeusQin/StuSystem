// TeaInsertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaInsertDlg.h"
#include "FileIO.h"


// CTeaInsertDlg

IMPLEMENT_DYNCREATE(CTeaInsertDlg, CFormView)

CTeaInsertDlg::CTeaInsertDlg()
	: CFormView(DIALOG_TEA_INSERT)
	, m_stunum(_T(""))
	, m_score(0)
{

}

CTeaInsertDlg::~CTeaInsertDlg()
{
}

void CTeaInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_stunum);
	DDX_Text(pDX, IDC_EDIT2, m_score);
}

BEGIN_MESSAGE_MAP(CTeaInsertDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CTeaInsertDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTeaInsertDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTeaInsertDlg 诊断

#ifdef _DEBUG
void CTeaInsertDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaInsertDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaInsertDlg 消息处理程序


void CTeaInsertDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 遍历教师的开课记录数组，填充到下拉框中
	FileIO file;
	CString teanum = file.ReadLogin();		// 读取已登录教师编号
	vector<CString> courselist = file.ReadCourseList();		// 读取课程列表
	teacher tmp;
	tmp = file.FindteacherById(teanum);		// 获取教师相关信息
	for (vector<int>::iterator it = tmp.courseList.begin(); it!= tmp.courseList.end(); it++)
	{
		m_combo.AddString(courselist[*it]);		// 通过课程号在课程列表中找到对应的课程名字
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CTeaInsertDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// 录入学生成绩并修改对应的文件数据
	// 同步输入的信息：学生学号和录入课程以及课程号
	UpdateData(TRUE);	// 同步数据
	// 验证数据合法性
	if (m_score<0 && m_stunum=="")
	{
		MessageBox(_T("请输入正确的学号或成绩"));
		return;
	}
	// 根据学号找到学生
	FileIO file;
	student findstu = file.FindstudentById(m_stunum);
	if (findstu.password == "")
	{
		MessageBox(_T("未找到学生，请输入正确的学号！"));
		return;
	}

	// 获取要插入课程的课程号
	int coursenum;
	int selnum = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(selnum, coursename);		// 获取要插入的课程名
	vector<CString> courselist = file.ReadCourseList();		// 读取课程列表
	int count = 0;
	for (vector<CString>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if ((*it) == coursename)
		{
			coursenum = count;			// 获取到课程号后，跳出循环
			break;
		}
		count++;
	}

	// 查看学生这门课程记录是否已经存在
	int num;
	stucourse tmp1 = file.FindstucourseById(m_stunum, &num);
	for (vector<lesson>::iterator it = tmp1.courses.begin(); it != tmp1.courses.end(); it++)
	{
		if (it->courseid == coursenum)
		{	// 课程号已存在，说明学生成绩已经录入,清空数据并返回
			MessageBox(_T("学生成绩已存在！要修改成绩请使用修改成绩功能！"));
			m_stunum = _T("");
			m_score = 0;
			m_combo.SetCurSel(0);	///默认选中第一门课程

			UpdateData(FALSE);
			return;
		}
	}

	// 插入学生成绩
	if (file.Insertscore(m_stunum, coursenum, m_score))
	{
		MessageBox(_T("成绩添加成功！"));
	}
	else
		MessageBox(_T("成绩添加失败！"));
	m_stunum = _T("");
	m_score = 0;
	UpdateData(FALSE);
}


void CTeaInsertDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	UpdateData(TRUE);
	m_stunum = _T("");
	m_score = 0;
	m_combo.SetCurSel(0);	///默认选中第一门课程

	UpdateData(FALSE);
}
