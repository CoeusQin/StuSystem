// TeaUpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaUpdateDlg.h"
#include "FileIO.h"


// CTeaUpdateDlg

IMPLEMENT_DYNCREATE(CTeaUpdateDlg, CFormView)

CTeaUpdateDlg::CTeaUpdateDlg()
	: CFormView(DIALOG_TEA_UPDATE)
	, m_stunum(_T(""))
	, m_score(0)
	, m_oldscore(0)
	, m_newscore(0)
{

}

CTeaUpdateDlg::~CTeaUpdateDlg()
{
}

void CTeaUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_stunum);
	DDX_Text(pDX, IDC_EDIT6, m_score);
	DDX_Text(pDX, IDC_EDIT4, m_oldscore);
	DDX_Text(pDX, IDC_EDIT5, m_newscore);
}

BEGIN_MESSAGE_MAP(CTeaUpdateDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeaUpdateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeaUpdateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTeaUpdateDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTeaUpdateDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTeaUpdateDlg ���

#ifdef _DEBUG
void CTeaUpdateDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaUpdateDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaUpdateDlg ��Ϣ�������


void CTeaUpdateDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ������ʦ�Ŀ��μ�¼���飬��䵽��������
	FileIO file;
	CString teanum = file.ReadLogin();		// ��ȡ�ѵ�¼��ʦ���
	vector<CString> courselist = file.ReadCourseList();		// ��ȡ�γ��б�
	teacher tmp;
	tmp = file.FindteacherById(teanum);		// ��ȡ��ʦ�����Ϣ
	for (vector<int>::iterator it = tmp.courseList.begin(); it != tmp.courseList.end(); it++)
	{
		m_combo.AddString(courselist[*it]);		// ͨ���γ̺��ڿγ��б����ҵ���Ӧ�Ŀγ�����
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CTeaUpdateDlg::OnBnClickedButton1()
{	// ��ѯѧ���ɼ�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ͬ������
	UpdateData(TRUE);
	// �ж����ݵĺϷ���
	if (m_score<0 && m_stunum == "")
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

	// ��ȡҪ��ѯ�γ̵Ŀγ̺�
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

	// �鿴ѧ�����ſγ̼�¼�Ƿ��Ѿ����ڣ�����������ȡ�ɼ�
	int num;
	int flag = 0;	// �ж��Ƿ��ҵ���Ӧ��Ŀ�ĳɼ���Ĭ��Ϊû�ҵ�
	stucourse tmp1 = file.FindstucourseById(m_stunum, &num);
	for (vector<lesson>::iterator it = tmp1.courses.begin(); it != tmp1.courses.end(); it++)
	{
		if (it->courseid == coursenum)
		{	// �ҵ�ѧ����Ӧ�γ̵ĳɼ�
			m_score = it->score;
			m_oldscore = m_score;
			flag = 1;
			UpdateData(FALSE);
			return;
		}
	}

	// û�з��أ�˵��δ�ҵ��ɼ�
	if (!flag)
	{
		MessageBox(_T("ѧ��û�и��ſγ̳ɼ�������¼��ɼ����ܴ�¼�룡"));
		m_stunum = _T("");
		m_score = 0;
		m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ�ſγ�
		UpdateData(FALSE);
	}
}


void CTeaUpdateDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ղ�ѯ������
	m_score = 0;
	m_stunum = _T("");
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}


void CTeaUpdateDlg::OnBnClickedButton4()
{	// �޸ĳɼ�
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡҪ�޸ĵĳɼ�
	UpdateData(TRUE);
	// �ж����ݺϷ���
	if (m_newscore < 0 || m_newscore > 100)
	{
		MessageBox(_T("��������ȷ���³ɼ���"));
		m_newscore = 0;
		UpdateData(FALSE);
		return;
	}
	if (m_newscore == m_oldscore)
	{
		MessageBox(_T("�޸ĺ�ĳɼ���ԭʼ�ɼ�����һ��!"));
		m_newscore = 0;
		UpdateData(FALSE);
		return;
	}

	// �޸ĳɼ�
	// ����ѧ���ҵ�ѧ��
	FileIO file;
	student findstu = file.FindstudentById(m_stunum);
	if (findstu.password == "")
	{
		MessageBox(_T("δ�ҵ�ѧ������������ȷ��ѧ�ţ�"));
		return;
	}

	// ��ȡҪ�޸Ŀγ̵Ŀγ̺�
	int coursenum;
	int selnum = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(selnum, coursename);		// ��ȡҪ�޸ĵĿγ���
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

	// ��ȡ��Ӧѧ���������У������޸ĺ���д��
	// ���ҵ�ѧ����������
	CString fstunum;
	ifstream ifs;
	int flag = 0;		// �ж��Ƿ��޸ĳɹ�
	ifs.open(_S_COURSE);
	char buf[1024] = { 0 };

	while (!ifs.eof())
	{
		stucourse tmp;
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			fstunum = info;		// ѧ�����
			tmp.stunum = info;	// ���浽��ʱ�ṹ����
		}
		else
		{
			break;
		}
		if (m_stunum == fstunum)	// �ҵ���Ӧѧ���ĳɼ������ȶ�ȡ���ݺ���tmp�в����³ɼ�
		{
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				if (coursenum == stoi(info))	// �ҵ���ӦҪ�޸ĵĳɼ�
				{
					tmplesson.courseid = coursenum;
					info = strtok(NULL, "|");
					tmplesson.score = m_newscore;
					tmp.courses.push_back(tmplesson);
					info = strtok(NULL, "|");
					flag = 1;		// �޸ĳɹ�
					continue;
				}
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			}
		}
		else
		{//		����Ҫ�޸ĵ�ѧ�������У�ֱ�ӱ���
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			}
		}
		file.ls.push_back(tmp);		// ���������ݱ��浽��ʱ����
	}
	ifs.close();
	// ���ݶ�ȡ���޸���ϣ� ��ʼд��
	file.WriteStuCourse();
	if (flag)
	{
		MessageBox(_T("�޸ĳɹ���"));
	}
	// ���µ�ǰ��������
	m_newscore = 0;
	OnBnClickedButton1();
}


void CTeaUpdateDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����޸����ݿ�
	m_oldscore = 0;
	m_newscore = 0;
	UpdateData(FALSE);
}
