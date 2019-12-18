// TeaInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaInfoDlg.h"
#include "LoginDlg.h"
#include "Public.h"
#include "string.h"
#include "FileIO.h"


// CTeaInfoDlg

IMPLEMENT_DYNCREATE(CTeaInfoDlg, CFormView)

CTeaInfoDlg::CTeaInfoDlg()
	: CFormView(DIALOG_TEA_INFO)
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
	, m_teaname(_T(""))
	, m_teanum(_T(""))
{

}

CTeaInfoDlg::~CTeaInfoDlg()
{
}

void CTeaInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_newPwd);
	DDX_Text(pDX, IDC_EDIT5, m_surePwd);
	DDX_Text(pDX, IDC_EDIT1, m_teaname);
	DDX_Text(pDX, IDC_EDIT2, m_teanum);
}

BEGIN_MESSAGE_MAP(CTeaInfoDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeaInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTeaInfoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTeaInfoDlg 诊断

#ifdef _DEBUG
void CTeaInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaInfoDlg 消息处理程序


void CTeaInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化显示
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// 读取已登录用户信息

	char *info = strtok(buf, "|");
	string name = info;
	m_teanum = name.c_str();
	ifs.close();

	// 根据拿到的教师编号查找对应的教师信息，填充进对应的控件中
	FileIO file;
	teacher logintea = file.FindteacherById(m_teanum);
	m_teaname = (CString)logintea.teaname.c_str();

	UpdateData(FALSE);
}


void CTeaInfoDlg::OnBnClickedButton2()
{
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
	// 获取对应教师的结构体
	FileIO file;
	teacher tmp;
	tmp = file.FindteacherById(m_teanum);
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
	if (file.UpdatePwd(2, m_teanum, m_newPwd))
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


void CTeaInfoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}
