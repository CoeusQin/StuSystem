// UserDlg.cpp : ʵ���ļ�
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


// CUserDlg ���

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


// CUserDlg ��Ϣ�������




void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	FileIO file;
	// ��ʼ����ʾ
	m_stunum = file.ReadLogin();		// ��ȡ�ѵ�¼�û��ı��

	// �����õ���ѧ�Ų��Ҷ�Ӧ��ѧ����Ϣ��������Ӧ�Ŀؼ���
	
	student loginstu = file.FindstudentById(m_stunum);
	m_name = (CString)loginstu.stuname.c_str();

	// ����ѧ�Ų���ѧ���ɼ������õ��γ���
	int coursenum = 0;
	CString str;
	file.FindstucourseById(m_stunum, &coursenum);
	str.Format(_T("%d"), coursenum);
	m_courseNum = str;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{	// �޸����밴��
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
	// ��ȡ��Ӧѧ���Ľṹ��
	FileIO file;
	student tmp;
	tmp = file.FindstudentById(m_stunum);
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
	if (file.UpdatePwd(1, m_stunum, m_newPwd))
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


void CUserDlg::OnBnClickedButton3()
{	// ȡ������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
}
