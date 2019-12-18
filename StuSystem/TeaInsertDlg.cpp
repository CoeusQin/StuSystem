// TeaInsertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaInsertDlg.h"
#include "FileIO.h"


// CTeaInsertDlg

IMPLEMENT_DYNCREATE(CTeaInsertDlg, CFormView)

CTeaInsertDlg::CTeaInsertDlg()
	: CFormView(DIALOG_TEA_INSERT)
	, m_stunum(_T(""))
	, m_score(0)
{

}

CTeaInsertDlg::~CTeaInsertDlg()
{
}

void CTeaInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_stunum);
	DDX_Text(pDX, IDC_EDIT2, m_score);
}

BEGIN_MESSAGE_MAP(CTeaInsertDlg, CFormView)
	ON_BN_CLICKED(IDOK, &CTeaInsertDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTeaInsertDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTeaInsertDlg ���

#ifdef _DEBUG
void CTeaInsertDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaInsertDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaInsertDlg ��Ϣ�������


void CTeaInsertDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// ������ʦ�Ŀ��μ�¼���飬��䵽��������
	FileIO file;
	CString teanum = file.ReadLogin();		// ��ȡ�ѵ�¼��ʦ���
	vector<CString> courselist = file.ReadCourseList();		// ��ȡ�γ��б�
	teacher tmp;
	tmp = file.FindteacherById(teanum);		// ��ȡ��ʦ�����Ϣ
	for (vector<int>::iterator it = tmp.courseList.begin(); it!= tmp.courseList.end(); it++)
	{
		m_combo.AddString(courselist[*it]);		// ͨ���γ̺��ڿγ��б����ҵ���Ӧ�Ŀγ�����
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CTeaInsertDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ¼��ѧ���ɼ����޸Ķ�Ӧ���ļ�����
	// ͬ���������Ϣ��ѧ��ѧ�ź�¼��γ��Լ��γ̺�
	UpdateData(TRUE);	// ͬ������
	// ��֤���ݺϷ���
	if (m_score<0 && m_stunum=="")
	{
		MessageBox(_T("��������ȷ��ѧ�Ż�ɼ�"));
		return;
	}
	// ����ѧ���ҵ�ѧ��
	FileIO file;
	student findstu = file.FindstudentById(m_stunum);
	if (findstu.password == "")
	{
		MessageBox(_T("δ�ҵ�ѧ������������ȷ��ѧ�ţ�"));
		return;
	}

	// ��ȡҪ����γ̵Ŀγ̺�
	int coursenum;
	int selnum = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(selnum, coursename);		// ��ȡҪ����Ŀγ���
	vector<CString> courselist = file.ReadCourseList();		// ��ȡ�γ��б�
	int count = 0;
	for (vector<CString>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if ((*it) == coursename)
		{
			coursenum = count;			// ��ȡ���γ̺ź�����ѭ��
			break;
		}
		count++;
	}

	// �鿴ѧ�����ſγ̼�¼�Ƿ��Ѿ�����
	int num;
	stucourse tmp1 = file.FindstucourseById(m_stunum, &num);
	for (vector<lesson>::iterator it = tmp1.courses.begin(); it != tmp1.courses.end(); it++)
	{
		if (it->courseid == coursenum)
		{	// �γ̺��Ѵ��ڣ�˵��ѧ���ɼ��Ѿ�¼��,������ݲ�����
			MessageBox(_T("ѧ���ɼ��Ѵ��ڣ�Ҫ�޸ĳɼ���ʹ���޸ĳɼ����ܣ�"));
			m_stunum = _T("");
			m_score = 0;
			m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ�ſγ�

			UpdateData(FALSE);
			return;
		}
	}

	// ����ѧ���ɼ�
	if (file.Insertscore(m_stunum, coursenum, m_score))
	{
		MessageBox(_T("�ɼ���ӳɹ���"));
	}
	else
		MessageBox(_T("�ɼ����ʧ�ܣ�"));
	m_stunum = _T("");
	m_score = 0;
	UpdateData(FALSE);
}


void CTeaInsertDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	UpdateData(TRUE);
	m_stunum = _T("");
	m_score = 0;
	m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ�ſγ�

	UpdateData(FALSE);
}
