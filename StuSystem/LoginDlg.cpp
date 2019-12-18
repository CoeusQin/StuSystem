// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Public.h"
#include "FileIO.h"


// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	exit(0);
	//CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ڵ�¼ʱ���ж�������Ϣ�Ϸ��ԣ��ٻ�ȡ��¼��ݣ����ڶ�Ӧ�������ļ���Ѱ������Ƿ�Ϸ���
	// ���ѵ�½�û�����Ϣ���浽��ʱ�ļ��У������������ʼ��ʱ�ж���ʾʲô����
	UpdateData(TRUE);	// ͬ������
	// �ж����������Ƿ�Ϊ��
	if (m_name.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(_T("�û��������벻��Ϊ�գ�"));
		m_name = _T("");
		m_pwd = _T("");
		UpdateData(FALSE);
		return;
	}
	FileIO file;
	CString name, pwd;
	// �ж���ݰ�ť��ֵ
	if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO1), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//���ѡ����ѧ��
	{
		// TODO ��ѧ�ź������Ƿ�ƥ�䣬ƥ���򵯳�ѧ���ĶԻ���
		//MessageBox(_T("ѡ����ѧ��!"));//������ʾ
		CPublic::status = 1;
		if (!file.Login(1, m_name, m_pwd))
		{
			MessageBox(_T("��¼��Ϣ����"));
			return;
		}
		else
		{
			MessageBox(_T("��¼�ɹ���"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO2), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//���ѡ���˽�ʦ
	{
		// TODO �н�ʦ��ź������Ƿ�ƥ�䣬ƥ���򵯳���ʦ�ĶԻ���
		//MessageBox(_T("ѡ���˽�ʦ!"));
		CPublic::status = 2;
		if (!file.Login(2, m_name, m_pwd))
		{
			MessageBox(_T("��¼��Ϣ����"));
			return;
		}
		else
		{
			MessageBox(_T("��ʦ��¼�ɹ���"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO3), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//���ѡ���˹���Ա
	{
		// TODO ���û����������Ƿ�ƥ�䣬ƥ���򵯳�����Ա�ĶԻ���
		//MessageBox(TEXT("ѡ���˹���Ա��"));
		CPublic::status = 3;
		if (!file.Login(3, m_name, m_pwd))
		{
			MessageBox(_T("��¼��Ϣ����"));
			return;
		}
		else
		{
			MessageBox(_T("����Ա��¼�ɹ���"));
			ofstream ofs(_LOGIN);
			ofs << CT2A(m_name.GetString()) << "|" << CT2A(m_pwd.GetString()) << endl;
			ofs.close();
			CDialog::OnCancel();
		}
	}
	else
	{
		MessageBox(_T("����ѡ����ȷ�ĵ�¼��ݣ�"));
		return;
	}
	// ����ʹ�ã��رյ�ǰ�Ի���
	//CDialog::OnCancel();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// Ĭ��ѡ�е�һ��ѡ��
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);

	// Ĭ����д�û���������
	m_name = _T("admin");
	m_pwd = _T("123");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}
