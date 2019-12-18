// TeaApplyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaApplyDlg.h"
#include "FileIO.h"


// CTeaApplyDlg

IMPLEMENT_DYNCREATE(CTeaApplyDlg, CFormView)

CTeaApplyDlg::CTeaApplyDlg()
	: CFormView(IDD_DIALOG2)
	, m_coursename(_T(""))
	, m_teaname(_T(""))
	, m_plan(_T(""))
{

}

CTeaApplyDlg::~CTeaApplyDlg()
{
}

void CTeaApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_coursename);
	DDX_Text(pDX, IDC_EDIT2, m_teaname);
	DDX_Text(pDX, IDC_EDIT3, m_plan);
}

BEGIN_MESSAGE_MAP(CTeaApplyDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CTeaApplyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTeaApplyDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTeaApplyDlg ���

#ifdef _DEBUG
void CTeaApplyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaApplyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaApplyDlg ��Ϣ�������


void CTeaApplyDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ����ʦ����Ĭ������ӵ������˴�
	// ��ʼ����ʾ
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// ��ȡ�ѵ�¼�û���Ϣ

	char *info = strtok(buf, "|");
	string name = info;
	teanum = name.c_str();
	ifs.close();

	// �����õ��Ľ�ʦ��Ų��Ҷ�Ӧ�Ľ�ʦ��Ϣ��������Ӧ�Ŀؼ���
	FileIO file;
	teacher logintea = file.FindteacherById(teanum);
	m_teaname = (CString)logintea.teaname.c_str();

	UpdateData(FALSE);
}



void CTeaApplyDlg::OnBnClickedOk()
{	// �ύ�¿γ�����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������ݺϷ���
	UpdateData(TRUE);
	if (m_coursename.IsEmpty() || m_plan.IsEmpty())
	{
		MessageBox(_T("�γ����ƻ��ڿμƻ�����Ϊ�գ�"));
		return;
	}
	if (CStringA(m_plan).GetLength() >= 1000)
	{
		MessageBox(_T("�ڿμƻ�������������������600�����ڣ�"));
		return;
	}
	// ����message�ṹ�壬�����浽��Ӧ���ļ���
	message tmp;
	tmp.teanum = CStringA(teanum).GetBuffer();	// ��ʦ���
	tmp.teaname = CStringA(m_teaname).GetBuffer();	// ��ʦ����
	tmp.coursename = CStringA(m_coursename).GetBuffer();	// �¿γ�����
	m_plan.TrimRight();			// ȥ���Ҳ�ո�
	m_plan.TrimLeft();			// ȥ�����ո�
	m_plan.Replace(_T(" "), _T(""));		// ȥ���ո�
	m_plan.Replace(_T("\r\n"), _T("&"));	// �ÿո���滻�з�
	tmp.courseplan = CStringA(m_plan).GetBuffer();		// �ڿμƻ�
	// �����������ύ��������
	FileIO file;
	// �ȶ�ȡ�ִ���Ϣ�б�
	file.ReadMessage();
	// ������Ϣ��ӽ�ȥ
	file.messagev.push_back(tmp);
	// ����Ϣд���ļ�
	file.WriteMessage();
	MessageBox(_T("���뷢�ͳɹ���"));
	m_coursename.Empty();
	m_plan.Empty();
	UpdateData(FALSE);
}



void CTeaApplyDlg::OnBnClickedCancel()
{	// �������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_plan = _T("");
	m_coursename = _T("");
	UpdateData(FALSE);
}
