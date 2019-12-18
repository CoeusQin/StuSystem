// ScoreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "ScoreDlg.h"
#include "FileIO.h"


// CScoreDlg

IMPLEMENT_DYNCREATE(CScoreDlg, CFormView)

CScoreDlg::CScoreDlg()
	: CFormView(DIALOG_STU_SCORE)
{

}

CScoreDlg::~CScoreDlg()
{
}

void CScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CScoreDlg, CFormView)
END_MESSAGE_MAP()


// CScoreDlg ���

#ifdef _DEBUG
void CScoreDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScoreDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScoreDlg ��Ϣ�������


void CScoreDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//������չ���
	/////|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES,����ѡ�У�����
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//��ʼ����ͷ
	CString field[] = { TEXT("��Ŀ"),TEXT("�ɼ�") };

	for (int i = 0; i<sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 200);
	}

	// ��ȡ��¼�û���Ϣ
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// ��ȡ�ѵ�¼�û���Ϣ

	char *info = strtok(buf, "|");
	string name = info;
	CString stunum;
	stunum = name.c_str();

	// ��ȡ�γ��б����飬��������
	FileIO file;
	vector<CString> courselist;
	courselist = file.ReadCourseList();

	// ��ȡ�ɼ��������list
	int coursenum = 0;
	int i = 0;
	CString str;
	stucourse tmp;
	tmp = file.FindstucourseById(stunum, &coursenum);
	for (vector<lesson>::iterator it = tmp.courses.begin(); it != tmp.courses.end(); it++)
	{
		// str.Format(TEXT("%d"), it->courseid);
		// m_list.InsertItem(i, str);
		m_list.InsertItem(i, courselist[it->courseid]);
		int column = 1;
		//m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(TEXT("%d"), it->score);
		m_list.SetItemText(i, column++, str);

		i++;
	}
}
