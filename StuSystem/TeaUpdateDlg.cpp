// TeaUpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaUpdateDlg.h"
#include "FileIO.h"


// CTeaUpdateDlg

IMPLEMENT_DYNCREATE(CTeaUpdateDlg, CFormView)

CTeaUpdateDlg::CTeaUpdateDlg()
	: CFormView(DIALOG_TEA_UPDATE)
	, m_stunum(_T(""))
	, m_score(0)
	, m_oldscore(0)
	, m_newscore(0)
{

}

CTeaUpdateDlg::~CTeaUpdateDlg()
{
}

void CTeaUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_stunum);
	DDX_Text(pDX, IDC_EDIT6, m_score);
	DDX_Text(pDX, IDC_EDIT4, m_oldscore);
	DDX_Text(pDX, IDC_EDIT5, m_newscore);
}

BEGIN_MESSAGE_MAP(CTeaUpdateDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeaUpdateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeaUpdateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTeaUpdateDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTeaUpdateDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTeaUpdateDlg 诊断

#ifdef _DEBUG
void CTeaUpdateDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaUpdateDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaUpdateDlg 消息处理程序


void CTeaUpdateDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 遍历教师的开课记录数组，填充到下拉框中
	FileIO file;
	CString teanum = file.ReadLogin();		// 读取已登录教师编号
	vector<CString> courselist = file.ReadCourseList();		// 读取课程列表
	teacher tmp;
	tmp = file.FindteacherById(teanum);		// 获取教师相关信息
	for (vector<int>::iterator it = tmp.courseList.begin(); it != tmp.courseList.end(); it++)
	{
		m_combo.AddString(courselist[*it]);		// 通过课程号在课程列表中找到对应的课程名字
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CTeaUpdateDlg::OnBnClickedButton1()
{	// 查询学生成绩
	// TODO: 在此添加控件通知处理程序代码
	// 同步数据
	UpdateData(TRUE);
	// 判断数据的合法性
	if (m_score<0 && m_stunum == "")
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

	// 获取要查询课程的课程号
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

	// 查看学生这门课程记录是否已经存在，如果存在则读取成绩
	int num;
	int flag = 0;	// 判读是否找到对应科目的成绩，默认为没找到
	stucourse tmp1 = file.FindstucourseById(m_stunum, &num);
	for (vector<lesson>::iterator it = tmp1.courses.begin(); it != tmp1.courses.end(); it++)
	{
		if (it->courseid == coursenum)
		{	// 找到学生对应课程的成绩
			m_score = it->score;
			m_oldscore = m_score;
			flag = 1;
			UpdateData(FALSE);
			return;
		}
	}

	// 没有返回，说明未找到成绩
	if (!flag)
	{
		MessageBox(_T("学生没有该门课程成绩！请在录入成绩功能处录入！"));
		m_stunum = _T("");
		m_score = 0;
		m_combo.SetCurSel(0);	///默认选中第一门课程
		UpdateData(FALSE);
	}
}


void CTeaUpdateDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 清空查询框数据
	m_score = 0;
	m_stunum = _T("");
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}


void CTeaUpdateDlg::OnBnClickedButton4()
{	// 修改成绩
	// TODO: 在此添加控件通知处理程序代码
	// 获取要修改的成绩
	UpdateData(TRUE);
	// 判断数据合法性
	if (m_newscore < 0 || m_newscore > 100)
	{
		MessageBox(_T("请输入正确的新成绩！"));
		m_newscore = 0;
		UpdateData(FALSE);
		return;
	}
	if (m_newscore == m_oldscore)
	{
		MessageBox(_T("修改后的成绩和原始成绩不能一样!"));
		m_newscore = 0;
		UpdateData(FALSE);
		return;
	}

	// 修改成绩
	// 根据学号找到学生
	FileIO file;
	student findstu = file.FindstudentById(m_stunum);
	if (findstu.password == "")
	{
		MessageBox(_T("未找到学生，请输入正确的学号！"));
		return;
	}

	// 获取要修改课程的课程号
	int coursenum;
	int selnum = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(selnum, coursename);		// 获取要修改的课程名
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

	// 读取对应学生的数据行，进行修改后，再写入
	// 先找到学生的数据行
	CString fstunum;
	ifstream ifs;
	int flag = 0;		// 判断是否修改成功
	ifs.open(_S_COURSE);
	char buf[1024] = { 0 };

	while (!ifs.eof())
	{
		stucourse tmp;
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			fstunum = info;		// 学生编号
			tmp.stunum = info;	// 保存到临时结构体中
		}
		else
		{
			break;
		}
		if (m_stunum == fstunum)	// 找到对应学生的成绩单，先读取数据后，在tmp中插入新成绩
		{
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				if (coursenum == stoi(info))	// 找到对应要修改的成绩
				{
					tmplesson.courseid = coursenum;
					info = strtok(NULL, "|");
					tmplesson.score = m_newscore;
					tmp.courses.push_back(tmplesson);
					info = strtok(NULL, "|");
					flag = 1;		// 修改成功
					continue;
				}
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			}
		}
		else
		{//		不是要修改的学生数据行，直接保存
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			}
		}
		file.ls.push_back(tmp);		// 将这行数据保存到临时变量
	}
	ifs.close();
	// 数据读取并修改完毕， 开始写入
	file.WriteStuCourse();
	if (flag)
	{
		MessageBox(_T("修改成功！"));
	}
	// 更新当前框中数据
	m_newscore = 0;
	OnBnClickedButton1();
}


void CTeaUpdateDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// 清空修改数据框
	m_oldscore = 0;
	m_newscore = 0;
	UpdateData(FALSE);
}
