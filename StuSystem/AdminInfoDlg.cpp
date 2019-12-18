// AdminInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminInfoDlg.h"
#include "FileIO.h"


// CAdminInfoDlg

IMPLEMENT_DYNCREATE(CAdminInfoDlg, CFormView)

CAdminInfoDlg::CAdminInfoDlg()
	: CFormView(DIALOG_ADM_INFO)
	, m_status(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CAdminInfoDlg::~CAdminInfoDlg()
{
}

void CAdminInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_status);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT4, m_newPwd);
	DDX_Text(pDX, IDC_EDIT5, m_surePwd);
}

BEGIN_MESSAGE_MAP(CAdminInfoDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdminInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminInfoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAdminInfoDlg 诊断

#ifdef _DEBUG
void CAdminInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminInfoDlg 消息处理程序


void CAdminInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 身份始终显示为管理员
	CString str;
	str = _T("管理员");
	m_status = str;
	// 初始化显示
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// 读取已登录用户信息
	char *info = strtok(buf, "|");
	string name = info;
	m_name = name.c_str();
	ifs.close();

	UpdateData(FALSE);
}


void CAdminInfoDlg::OnBnClickedButton2()
{	// 修改密码
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
	FileIO file;
	admin tmp;
	tmp = file.FindAdminById(m_name);
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
	if (file.UpdatePwd(3, m_name, m_newPwd))
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


void CAdminInfoDlg::OnBnClickedButton3()
{	// 取消
	// TODO: 在此添加控件通知处理程序代码
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}
