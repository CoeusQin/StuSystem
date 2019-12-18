// UserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "UserDlg.h"
#include "LoginDlg.h"
#include "Public.h"
#include "string.h"
#include "FileIO.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_STU_INFO)
	, m_name(_T(""))
	, m_stunum(_T(""))
	, m_courseNum(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_stunum);
	DDX_Text(pDX, IDC_EDIT3, m_courseNum);
	DDX_Text(pDX, IDC_EDIT4, m_newPwd);
	DDX_Text(pDX, IDC_EDIT5, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序




void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	FileIO file;
	// 初始化显示
	m_stunum = file.ReadLogin();		// 读取已登录用户的编号

	// 根据拿到的学号查找对应的学生信息，填充进对应的控件中
	
	student loginstu = file.FindstudentById(m_stunum);
	m_name = (CString)loginstu.stuname.c_str();

	// 根据学号查找学生成绩单，拿到课程数
	int coursenum = 0;
	CString str;
	file.FindstucourseById(m_stunum, &coursenum);
	str.Format(_T("%d"), coursenum);
	m_courseNum = str;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{	// 修改密码按键
	// TODO: 在此添加控件通知处理程序代码
	// 验证数据的合法性
	UpdateData(TRUE);
	if (m_newPwd == "" || m_surePwd == "")
	{
		MessageBox(_T("修改的密码或确认密码不能为空!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_newPwd != m_surePwd)
	{
		MessageBox(_T("两次输入的密码不一致!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	// 获取对应学生的结构体
	FileIO file;
	student tmp;
	tmp = file.FindstudentById(m_stunum);
	// 判断新密码是否与旧密码一致
	if (m_newPwd == tmp.password.c_str())
	{
		MessageBox(_T("新密码不能和原密码一样!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	// 进行修改
	if (file.UpdatePwd(1, m_stunum, m_newPwd))
	{
		MessageBox(_T("密码修改成功！"));
	}
	else
	{
		MessageBox(_T("系统走神了，修改密码失败！请重试！"));
	}
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}


void CUserDlg::OnBnClickedButton3()
{	// 取消按键
	// TODO: 在此添加控件通知处理程序代码
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
}
