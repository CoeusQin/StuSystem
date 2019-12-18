// AdminInfoDlg.cpp : ʵ���ļ�
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


// CAdminInfoDlg ���

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


// CAdminInfoDlg ��Ϣ�������


void CAdminInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ���ʼ����ʾΪ����Ա
	CString str;
	str = _T("����Ա");
	m_status = str;
	// ��ʼ����ʾ
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// ��ȡ�ѵ�¼�û���Ϣ
	char *info = strtok(buf, "|");
	string name = info;
	m_name = name.c_str();
	ifs.close();

	UpdateData(FALSE);
}


void CAdminInfoDlg::OnBnClickedButton2()
{	// �޸�����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��֤���ݵĺϷ���
	UpdateData(TRUE);
	if (m_newPwd == "" || m_surePwd == "")
	{
		MessageBox(_T("�޸ĵ������ȷ�����벻��Ϊ��!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	if (m_newPwd != m_surePwd)
	{
		MessageBox(_T("������������벻һ��!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	FileIO file;
	admin tmp;
	tmp = file.FindAdminById(m_name);
	// �ж��������Ƿ��������һ��
	if (m_newPwd == tmp.password.c_str())
	{
		MessageBox(_T("�����벻�ܺ�ԭ����һ��!"));
		m_newPwd = _T("");
		m_surePwd = _T("");
		UpdateData(FALSE);
		return;
	}
	// �����޸�
	if (file.UpdatePwd(3, m_name, m_newPwd))
	{
		MessageBox(_T("�����޸ĳɹ���"));
	}
	else
	{
		MessageBox(_T("ϵͳ�����ˣ��޸�����ʧ�ܣ������ԣ�"));
	}
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}


void CAdminInfoDlg::OnBnClickedButton3()
{	// ȡ��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}
