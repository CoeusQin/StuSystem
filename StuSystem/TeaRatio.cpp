// TeaRatio.cpp : 实现文件
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


// CTeaRatio 诊断

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


// CTeaRatio 消息处理程序


void CTeaRatioDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 把当前教师所有课程添加到控件中去
	FileIO file;
	CString teanum = file.ReadLogin();		// 读取已登录教师编号
	vector<CString> courselist = file.ReadCourseList();		// 读取课程列表
	teacher tmp;
	tmp = file.FindteacherById(teanum);		// 获取教师相关信息
	for (vector<int>::iterator it = tmp.courseList.begin(); it != tmp.courseList.end(); it++)
	{
		m_combo.AddString(courselist[*it]);		// 通过课程号在课程列表中找到对应的课程名字
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}

void CTeaRatioDlg::OnBnClickedButton2()
{	// 清空右侧信息栏
	// TODO: 在此添加控件通知处理程序代码
	m_ratio.Empty();
	m_combo.SetCurSel(0);
	UpdateData(FALSE);
}


void CTeaRatioDlg::OnBnClickedButton1()
{	// 查询所选课程的成绩比例
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	// 获取要查询课程的课程号
	FileIO file;
	int coursenum;
	int selnum = m_combo.GetCurSel();
	CString coursename;
	m_combo.GetLBText(selnum, coursename);		// 获取要插入的课程名
	vector<CString> courselist = file.ReadCourseList();		// 读取课程列表
	int count = 0;
	for (vector<CString>::iterator it = courselist.begin(); it != courselist.end(); it++)
	{
		if ((*it) == coursename)
		{
			coursenum = count;			// 获取到课程号后，跳出循环
			break;
		}
		count++;
	}

	// 先读取所有学生的课程，保存到vector<stucourse> ls当中
	CString fstunum;
	ifstream ifs;
	int flag = 0;		// 判断是否修改成功
	ifs.open(_S_COURSE);
	char buf[1024] = { 0 };

	while (!ifs.eof())
	{
		stucourse tmp;
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			fstunum = info;		// 学生编号
			tmp.stunum = info;	// 保存到临时结构体中
		}
		else
		{
			break;
		}
		//	保存到ls中
		lesson tmplesson;
		info = strtok(NULL, "|");
		while (info != NULL) {
			tmplesson.courseid = atoi(info);
			info = strtok(NULL, "|");
			tmplesson.score = atoi(info);
			tmp.courses.push_back(tmplesson);
			info = strtok(NULL, "|");
		}
		
		file.ls.push_back(tmp);		// 将这行数据保存到临时变量
	}
	ifs.close();

	// 通过ls获取数据
	int a = 0, b = 0, c = 0, d = 0, e = 0;	// 分别表示优秀，良好， 中等，及格，不及格的人数
	double ratio_a, ratio_b, ratio_c, ratio_d, ratio_e;		// 表示各个等级的比例
	int sum = 0;		// 表示选修这门课的总人数
	int total = 0;		// 总分数，用来计算平均分
	// 找到对应的课程号，判断成绩等级，并统计
	for (vector<stucourse>::iterator it = file.ls.begin(); it != file.ls.end(); it++)	// 遍历所有学生的成绩单
	{
		for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)	// 遍历单个学生成绩单的所有课程
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

	// 计算部分
	ratio_a = 100.0*a / sum;
	ratio_b = 100.0*b / sum;
	ratio_c = 100.0*c / sum;
	ratio_d = 100.0*d / sum;
	ratio_e = 100.0*e / sum;
	double average = 1.0*total / (a + b + c + d + e);
	CString str;
	str.Format(_T("该课程学生总人数为: %d 人 \r\n成绩分布如下所示：\r\n优秀: %d 人，占比 %.2lf%% \r\n良好: %d 人，占比 %.2lf%% \r\n中等: %d 人，占比 %.2lf%% \r\n及格: %d 人，占比 %.2lf%% \r\n不及格: %d 人，占比 %.2lf%% \r\n平均成绩： %.2lf"), sum, a, ratio_a, b, ratio_b, c, ratio_c, d, ratio_d, e, ratio_e, average);

	// 输出到展示框中m_ratio
	m_ratio = str;
	UpdateData(FALSE);
}



