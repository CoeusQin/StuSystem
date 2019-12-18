// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Public.h"
#include "FileIO.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
	, m_nRadio(FALSE)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	exit(0);
	//CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 在登录时先判断输入信息合法性，再获取登录身份，并在对应的数据文件中寻找身份是否合法，
	// 最后把登陆用户的信息保存到临时文件中，便于主窗体初始化时判断显示什么界面
	UpdateData(TRUE);	// 同步数据
	// 判断所填内容是否为空
	if (m_name.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空！"));
		m_name = _T("");
		m_pwd = _T("");
		UpdateData(FALSE);
		return;
	}
	FileIO file;
	CString name, pwd;
	// 判断身份按钮的值
	if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO1), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了学生
	{
		// TODO 判学号和密码是否匹配，匹配则弹出学生的对话框
		//MessageBox(_T("选择了学生!"));//弹出提示
		CPublic::status = 1;
		if (!file.Login(1, m_name, m_pwd))
		{
			MessageBox(_T("登录信息有误！"));
			return;
		}
		else
		{
			MessageBox(_T("登录成功！"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO2), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了教师
	{
		// TODO 判教师编号和密码是否匹配，匹配则弹出教师的对话框
		//MessageBox(_T("选择了教师!"));
		CPublic::status = 2;
		if (!file.Login(2, m_name, m_pwd))
		{
			MessageBox(_T("登录信息有误！"));
			return;
		}
		else
		{
			MessageBox(_T("教师登录成功！"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO3), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了管理员
	{
		// TODO 判用户名和密码是否匹配，匹配则弹出管理员的对话框
		//MessageBox(TEXT("选择了管理员！"));
		CPublic::status = 3;
		if (!file.Login(3, m_name, m_pwd))
		{
			MessageBox(_T("登录信息有误！"));
			return;
		}
		else
		{
			MessageBox(_T("管理员登录成功！"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else
	{
		MessageBox(_T("必须选择正确的登录身份！"));
		return;
	}
	// 调试使用，关闭当前对话框
	//CDialog::OnCancel();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 默认选中第一个选项
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);

	// 默认填写用户名和密码
	m_name = _T("admin");
	m_pwd = _T("123");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}
