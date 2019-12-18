// AdminInsertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminInsertDlg.h"
#include "FileIO.h"


// CAdminInsertDlg

IMPLEMENT_DYNCREATE(CAdminInsertDlg, CFormView)

CAdminInsertDlg::CAdminInsertDlg()
	: CFormView(DIALOG_ADM_INSERT)
	, m_coursename(_T(""))
	, m_classnum(0)
	//, m_courseid(_T(""))
	, m_courseid(0)
{

}

CAdminInsertDlg::~CAdminInsertDlg()
{
}

void CAdminInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_coursename);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT4, m_classnum);
	//  DDX_Text(pDX, IDC_EDIT5, m_courseid);
	DDX_Text(pDX, IDC_EDIT5, m_courseid);
}

BEGIN_MESSAGE_MAP(CAdminInsertDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminInsertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdminInsertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminInsertDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAdminInsertDlg ���

#ifdef _DEBUG
void CAdminInsertDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminInsertDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminInsertDlg ��Ϣ�������


void CAdminInsertDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��ȡ��ʦ�б���ӵ������ؼ���
	FileIO file;
	file.ReadUserInfo(2);	// ��ȡ���н�ʦ��Ϣ
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{
		m_combo.AddString(CString(it->teaname.c_str()));		// ���������ʦ
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CAdminInsertDlg::OnBnClickedButton3()
{	// �Զ����ɿγ̺�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	FileIO file;
	vector<CString> courselist = file.ReadCourseList();
	int num = courselist.size();
	m_courseid = num;
	UpdateData(FALSE);
}

void CAdminInsertDlg::OnBnClickedButton1()
{	// �������¿γ�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ��ȡ�ܿγ��б�
	FileIO file;
	vector<CString> courselist = file.ReadCourseList();
	// ����¿γ̵��ܿγ̱�
	courselist.push_back(m_coursename);
	// д�뵽�ļ���
	file.WriteCourseList(courselist);

	// ��Ҫ������γ̵Ľ�ʦ�Ŀγ��б����
	// �Ȼ�ȡ��ʦ���
	CString teanum;
	int index = m_combo.GetCurSel();
	file.ReadUserInfo(2);		// ���еĽ�ʦ�б���Ϣ
	// ��Ӷ�Ӧ��ʦ�Ŀγ̱�
	file.teals[index].courseList.push_back(m_courseid);
	// д���ʦ�γ̱�
	file.WriteTeaCourse();
	m_courseid = 0;
	m_classnum = 0;
	m_coursename.Empty();
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
	MessageBox(_T("�γ���ӳɹ�"));
}


void CAdminInsertDlg::OnBnClickedButton2()
{	// ȡ�����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_coursename.Empty();
	m_courseid = 0;
	m_classnum = 0;
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}
