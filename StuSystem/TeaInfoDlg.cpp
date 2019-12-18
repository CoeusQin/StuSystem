// TeaInfoDlg.cpp : ʵ���ļ�
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


// CTeaInfoDlg ���

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


// CTeaInfoDlg ��Ϣ�������


void CTeaInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��ʼ����ʾ
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// ��ȡ�ѵ�¼�û���Ϣ

	char *info = strtok(buf, "|");
	string name = info;
	m_teanum = name.c_str();
	ifs.close();

	// �����õ��Ľ�ʦ��Ų��Ҷ�Ӧ�Ľ�ʦ��Ϣ��������Ӧ�Ŀؼ���
	FileIO file;
	teacher logintea = file.FindteacherById(m_teanum);
	m_teaname = (CString)logintea.teaname.c_str();

	UpdateData(FALSE);
}


void CTeaInfoDlg::OnBnClickedButton2()
{
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
	// ��ȡ��Ӧ��ʦ�Ľṹ��
	FileIO file;
	teacher tmp;
	tmp = file.FindteacherById(m_teanum);
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
	if (file.UpdatePwd(2, m_teanum, m_newPwd))
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


void CTeaInfoDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_newPwd = _T("");
	m_surePwd = _T("");
	UpdateData(FALSE);
	return;
}
