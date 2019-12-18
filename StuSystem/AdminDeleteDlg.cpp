// AdminDeleteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminDeleteDlg.h"
#include "FileIO.h"


// CAdminDeleteDlg

IMPLEMENT_DYNCREATE(CAdminDeleteDlg, CFormView)

CAdminDeleteDlg::CAdminDeleteDlg()
	: CFormView(DIALOG_ADM_DELETE)
	//, m_querynum(_T(""))
	//, m_deletenum(_T(""))
	//, m_detail(_T(""))
	, m_detail(_T(""))
{

}

CAdminDeleteDlg::~CAdminDeleteDlg()
{
}

void CAdminDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_querynum);
	//  DDX_Text(pDX, IDC_EDIT7, m_deletenum);
	//  DDX_Text(pDX, IDC_EDIT2, m_detail);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_detail);
}

BEGIN_MESSAGE_MAP(CAdminDeleteDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminDeleteDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminDeleteDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdminDeleteDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAdminDeleteDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAdminDeleteDlg ���

#ifdef _DEBUG
void CAdminDeleteDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminDeleteDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminDeleteDlg ��Ϣ�������


void CAdminDeleteDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��ȡ���пγ��б���ӵ���������
	FileIO file;
	vector<CString> courseList = file.ReadCourseList();
	for (vector<CString>::iterator it = courseList.begin(); it != courseList.end(); it++)
	{
		m_combo.AddString(*it);		// ͨ���γ̺��ڿγ��б����ҵ���Ӧ�Ŀγ�����
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(1);
	OnCbnSelchangeCombo1();
}


void CAdminDeleteDlg::OnBnClickedButton1()
{	// ��ѯ�γ�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ǰҪ�鿴�γ̵��±�
	int index = m_combo.GetCurSel();

}


void CAdminDeleteDlg::OnBnClickedButton3()
{	// ɾ���γ�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ǰѡ��Ŀγ̺�
	int index = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(index, coursename);	// ��ȡ�γ���
	// ͨ���γ�����ȡ�γ̺�
	FileIO file;
	vector<lcourse> courselist = file.ReadCourses();
	int courseid;	// �γ̺�
	for (vector<lcourse>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if (it->coursename.c_str() == coursename)
		{	// �ҵ�Ҫ�鿴�Ŀγ�,����ѭ��
			courseid = it->courseid;
			break;
		}
	}
	// ͨ���γ̺ţ��޸Ŀ���ÿγ̵���ʦ�Ŀγ̱���д���ļ�
	file.ReadUserInfo(2);	// ��ȡ��ʦ����Ϣ
	vector<teacher> findteachers;	// �������濪ͨ�θÿγ̵Ľ�ʦ
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{	// �������н�ʦ
		teacher tmp;
		for (vector<int>::iterator it1 = it->courseList.begin(); it1 != it->courseList.end(); )
		{	// ����ÿ����ʦ�Ŀγ̱��Ƿ���������ſγ�
			if (courseid == (*it1))
			{	
				it1 = it->courseList.erase(it1);
			}
			else
			{
				++it1;
			}
		}
	}
	file.WriteTeaCourse();
	// ͨ���γ̺ţ��޸�ѡ�޸ÿγ̵�ѧ���ĳɼ�������д���ļ�
	file.FindAllStuCourse();
	vector<stucourse> findstudents;
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{	// �������н�ʦ
		teacher tmp;
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); )
		{	// ����ÿ����ʦ�Ŀγ̱��Ƿ���������ſγ�
			if (courseid == it1->courseid)
			{
				it1 = it->courses.erase(it1);
			}
			else
			{
				++it1;
			}
		}
	}
	file.WriteStuCourse();
	// ɾ�����ÿγ��б��е�����
	vector<CString> oldlist = file.ReadCourseList();		// ��ȡ�ɵĿγ��б�
	for (vector<CString>::iterator it = oldlist.begin(); it != oldlist.end(); )
	{
		if (coursename == (*it))
		{
			it = oldlist.erase(it);
		}
		else
		{
			++it;
		}
	}
	file.WriteCourseList(oldlist);
	// ��ʾɾ���ɹ�������������Ȼ��Ĭ��ˢ��
	MessageBox(_T("�γ�ɾ���ɹ���"));
	m_detail.Empty();
	m_combo.SetCurSel(1);
	UpdateData(FALSE);
}


void CAdminDeleteDlg::OnBnClickedButton4()
{	// �������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_detail.Empty();
	m_combo.SetCurSel(1);
	UpdateData(FALSE);

}


void CAdminDeleteDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ǰҪɾ���γ̵��±�
	UpdateData(TRUE);
	int index = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(index, coursename);	// ��ȡ��ǰ��ѡ�γ̵�����
	// ���ݿγ��������ҿγ̺�
	FileIO file;
	vector<lcourse> courselist = file.ReadCourses();
	int courseid;	// �γ̺�
	for (vector<lcourse>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if (it->coursename.c_str() == coursename)
		{	// �ҵ�Ҫ�鿴�Ŀγ�,����ѭ��
			courseid = it->courseid;
			break;
		}
	}
	// ͨ���γ̺Ų��ҿ�ͨ�ÿγ̵Ľ�ʦ
	file.ReadUserInfo(2);	// ��ȡ��ʦ����Ϣ
	vector<teacher> findteachers;	// �������濪ͨ�θÿγ̵Ľ�ʦ
	for (vector<teacher>::iterator it = file.teals.begin(); it != file.teals.end(); it++)
	{	// �������н�ʦ
		for (vector<int>::iterator it1 = it->courseList.begin(); it1 != it->courseList.end(); it1++)
		{	// ����ÿ����ʦ�Ŀγ̱��Ƿ���������ſγ�
			if (courseid == (*it1))
			{
				findteachers.push_back(*it);
			}
		}
	}
	// ͨ���γ̺Ų���ѡ�޸ÿγ̵�ѧ��,Ӧ���Ƕ�ȡ_S_COURSE�е�����
	file.FindAllStuCourse();
	vector<stucourse> findstudents;	// ��������ѡ�޸ÿγ̵�ѧ��
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{	// ��������ѧ��
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)
		{	// ����ÿ��ѧ���ĳɼ���,��������ѡ�����ſγ̵�ѧ��
			if (it1->courseid == courseid)
			{
				findstudents.push_back(*it);
			}
		}
	}

	// ����������е�����
	string content;
	content = "�ÿγ������Ϣ���£�\r\n����ÿγ̵Ľ�ʦ�У�\r\n";
	for (vector<teacher>::iterator it = findteachers.begin(); it != findteachers.end(); it++)
	{
		content += it->teaname;
		content += "\r\n";
	}
	content += "ѡ�޸ÿγ̵�ѧ���У�\r\n";
	for (vector<stucourse>::iterator it = findstudents.begin(); it != findstudents.end(); it++)
	{
		content += "ѧ�ţ�";
		content += it->stunum;
		content += " �ɼ�Ϊ:";
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)
		{	// ����ÿ��ѧ���ĳɼ���,��������ѡ�����ſγ̵�ѧ��
			if (it1->courseid == courseid)
			{
				content += to_string(it1->score);
			}
		}
		content += "\r\n";
	}
	m_detail = (CString)content.c_str();
	UpdateData(FALSE);
}
