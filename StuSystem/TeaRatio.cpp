// TeaRatio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StuSystem.h"
#include "TeaRatio.h"
#include "FileIO.h"


// CTeaRatio

IMPLEMENT_DYNCREATE(CTeaRatioDlg, CFormView)

CTeaRatioDlg::CTeaRatioDlg()
	: CFormView(DIALOG_RATIO)
	, m_ratio(_T(""))
{

}

CTeaRatioDlg::~CTeaRatioDlg()
{
}

void CTeaRatioDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_ratio);
}

BEGIN_MESSAGE_MAP(CTeaRatioDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeaRatioDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeaRatioDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTeaRatio ���

#ifdef _DEBUG
void CTeaRatioDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeaRatioDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeaRatio ��Ϣ�������


void CTeaRatioDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �ѵ�ǰ��ʦ���пγ���ӵ��ؼ���ȥ
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

void CTeaRatioDlg::OnBnClickedButton2()
{	// ����Ҳ���Ϣ��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ratio.Empty();
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}


void CTeaRatioDlg::OnBnClickedButton1()
{	// ��ѯ��ѡ�γ̵ĳɼ�����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	// ��ȡҪ��ѯ�γ̵Ŀγ̺�
	FileIO file;
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

	// �ȶ�ȡ����ѧ���Ŀγ̣����浽vector<stucourse> ls����
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
		//	���浽ls��
		lesson tmplesson;
		info = strtok(NULL, "|");
		while (info != NULL) {
			tmplesson.courseid = atoi(info);
			info = strtok(NULL, "|");
			tmplesson.score = atoi(info);
			tmp.courses.push_back(tmplesson);
			info = strtok(NULL, "|");
		}
		
		file.ls.push_back(tmp);		// ���������ݱ��浽��ʱ����
	}
	ifs.close();

	// ͨ��ls��ȡ����
	int a = 0, b = 0, c = 0, d = 0, e = 0;	// �ֱ��ʾ���㣬���ã� �еȣ����񣬲����������
	double ratio_a, ratio_b, ratio_c, ratio_d, ratio_e;		// ��ʾ�����ȼ��ı���
	int sum = 0;		// ��ʾѡ�����ſε�������
	int total = 0;		// �ܷ�������������ƽ����
	// �ҵ���Ӧ�Ŀγ̺ţ��жϳɼ��ȼ�����ͳ��
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)	// ��������ѧ���ĳɼ���
	{
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)	// ��������ѧ���ɼ��������пγ�
		{
			if (it1->courseid == coursenum)
			{	
				sum++;
				total += it1->score;
				if (it1->score < 60)
					e++;
				else if (it1->score < 70)
					d++;
				else if (it1->score < 80)
					c++;
				else if (it1->score < 90)
					b++;
				else
					a++;
				break;
			}
		}
	}

	// ���㲿��
	ratio_a = 100.0*a / sum;
	ratio_b = 100.0*b / sum;
	ratio_c = 100.0*c / sum;
	ratio_d = 100.0*d / sum;
	ratio_e = 100.0*e / sum;
	double average = 1.0*total / (a + b + c + d + e);
	CString str;
	str.Format(_T("�ÿγ�ѧ��������Ϊ: %d �� \r\n�ɼ��ֲ�������ʾ��\r\n����: %d �ˣ�ռ�� %.2lf%% \r\n����: %d �ˣ�ռ�� %.2lf%% \r\n�е�: %d �ˣ�ռ�� %.2lf%% \r\n����: %d �ˣ�ռ�� %.2lf%% \r\n������: %d �ˣ�ռ�� %.2lf%% \r\nƽ���ɼ��� %.2lf"), sum, a, ratio_a, b, ratio_b, c, ratio_c, d, ratio_d, e, ratio_e, average);

	// �����չʾ����m_ratio
	m_ratio = str;
	UpdateData(FALSE);
}



