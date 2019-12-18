// AdminDeleteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminDeleteDlg.h"
#include "FileIO.h"


// CAdminDeleteDlg

IMPLEMENT_DYNCREATE(CAdminDeleteDlg, CFormView)

CAdminDeleteDlg::CAdminDeleteDlg()
	: CFormView(DIALOG_ADM_DELETE)
	//, m_querynum(_T(""))
	//, m_deletenum(_T(""))
	//, m_detail(_T(""))
	, m_detail(_T(""))
{

}

CAdminDeleteDlg::~CAdminDeleteDlg()
{
}

void CAdminDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_querynum);
	//  DDX_Text(pDX, IDC_EDIT7, m_deletenum);
	//  DDX_Text(pDX, IDC_EDIT2, m_detail);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_detail);
}

BEGIN_MESSAGE_MAP(CAdminDeleteDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminDeleteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminDeleteDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdminDeleteDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAdminDeleteDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAdminDeleteDlg 诊断

#ifdef _DEBUG
void CAdminDeleteDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminDeleteDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminDeleteDlg 消息处理程序


void CAdminDeleteDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 读取所有课程列表，添加到下拉框中
	FileIO file;
	vector<CString> courseList = file.ReadCourseList();
	for (vector<CString>::iterator it = courseList.begin(); it != courseList.end(); it++)
	{
		m_combo.AddString(*it);		// 通过课程号在课程列表中找到对应的课程名字
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(1);
	OnCbnSelchangeCombo1();
}


void CAdminDeleteDlg::OnBnClickedButton1()
{	// 查询课程
	// TODO: 在此添加控件通知处理程序代码
	// 获取当前要查看课程的下标
	int index = m_combo.GetCurSel();

}


void CAdminDeleteDlg::OnBnClickedButton3()
{	// 删除课程
	// TODO: 在此添加控件通知处理程序代码
	// 获取当前选择的课程号
	int index = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(index, coursename);	// 获取课程名
	// 通过课程名获取课程号
	FileIO file;
	vector<lcourse> courselist = file.ReadCourses();
	int courseid;	// 课程号
	for (vector<lcourse>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if (it->coursename.c_str() == coursename)
		{	// 找到要查看的课程,跳出循环
			courseid = it->courseid;
			break;
		}
	}
	// 通过课程号，修改开设该课程的老师的课程表，并写入文件
	file.ReadUserInfo(2);	// 读取教师的信息
	vector<teacher> findteachers;	// 用来保存开通课该课程的教师
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{	// 遍历所有教师
		teacher tmp;
		for (vector<int>::iterator it1 = it->courseList.begin(); it1 != it->courseList.end(); )
		{	// 遍历每个教师的课程表是否包含有这门课程
			if (courseid == (*it1))
			{	
				it1 = it->courseList.erase(it1);
			}
			else
			{
				++it1;
			}
		}
	}
	file.WriteTeaCourse();
	// 通过课程号，修改选修该课程的学生的成绩单，并写入文件
	file.FindAllStuCourse();
	vector<stucourse> findstudents;
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{	// 遍历所有教师
		teacher tmp;
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); )
		{	// 遍历每个教师的课程表是否包含有这门课程
			if (courseid == it1->courseid)
			{
				it1 = it->courses.erase(it1);
			}
			else
			{
				++it1;
			}
		}
	}
	file.WriteStuCourse();
	// 删除公用课程列表中的内容
	vector<CString> oldlist = file.ReadCourseList();		// 读取旧的课程列表
	for (vector<CString>::iterator it = oldlist.begin(); it != oldlist.end(); )
	{
		if (coursename == (*it))
		{
			it = oldlist.erase(it);
		}
		else
		{
			++it;
		}
	}
	file.WriteCourseList(oldlist);
	// 提示删除成功，并清空详情框，然后默认刷新
	MessageBox(_T("课程删除成功！"));
	m_detail.Empty();
	m_combo.SetCurSel(1);
	UpdateData(FALSE);
}


void CAdminDeleteDlg::OnBnClickedButton4()
{	// 清空数据
	// TODO: 在此添加控件通知处理程序代码
	m_detail.Empty();
	m_combo.SetCurSel(1);
	UpdateData(FALSE);

}


void CAdminDeleteDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取当前要删除课程的下标
	UpdateData(TRUE);
	int index = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(index, coursename);	// 获取当前所选课程的名字
	// 根据课程名，查找课程号
	FileIO file;
	vector<lcourse> courselist = file.ReadCourses();
	int courseid;	// 课程号
	for (vector<lcourse>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if (it->coursename.c_str() == coursename)
		{	// 找到要查看的课程,跳出循环
			courseid = it->courseid;
			break;
		}
	}
	// 通过课程号查找开通该课程的教师
	file.ReadUserInfo(2);	// 读取教师的信息
	vector<teacher> findteachers;	// 用来保存开通课该课程的教师
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{	// 遍历所有教师
		for (vector<int>::iterator it1 = it->courseList.begin(); it1 != it->courseList.end(); it1++)
		{	// 遍历每个教师的课程表是否包含有这门课程
			if (courseid == (*it1))
			{
				findteachers.push_back(*it);
			}
		}
	}
	// 通过课程号查找选修该课程的学生,应该是读取_S_COURSE中的数据
	file.FindAllStuCourse();
	vector<stucourse> findstudents;	// 用来保存选修该课程的学生
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{	// 遍历所有学生
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)
		{	// 遍历每个学生的成绩单,查找所有选修这门课程的学生
			if (it1->courseid == courseid)
			{
				findstudents.push_back(*it);
			}
		}
	}

	// 完善详情框中的内容
	string content;
	content = "该课程相关信息如下：\r\n开设该课程的教师有：\r\n";
	for (vector<teacher>::iterator it = findteachers.begin(); it != findteachers.end(); it++)
	{
		content += it->teaname;
		content += "\r\n";
	}
	content += "选修该课程的学生有：\r\n";
	for (vector<stucourse>::iterator it = findstudents.begin(); it != findstudents.end(); it++)
	{
		content += "学号：";
		content += it->stunum;
		content += " 成绩为:";
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)
		{	// 遍历每个学生的成绩单,查找所有选修这门课程的学生
			if (it1->courseid == courseid)
			{
				content += to_string(it1->score);
			}
		}
		content += "\r\n";
	}
	m_detail = (CString)content.c_str();
	UpdateData(FALSE);
}
