// AdminApplyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "AdminApplyDlg.h"
#include "FileIO.h"


// CAdminApplyDlg

IMPLEMENT_DYNCREATE(CAdminApplyDlg, CFormView)

CAdminApplyDlg::CAdminApplyDlg()
	: CFormView(DIALOG_ADM_APPLY)
	, m_message(_T(""))
{

}

CAdminApplyDlg::~CAdminApplyDlg()
{
}

void CAdminApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_message);
}

BEGIN_MESSAGE_MAP(CAdminApplyDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminApplyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdminApplyDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAdminApplyDlg 诊断

#ifdef _DEBUG
void CAdminApplyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdminApplyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdminApplyDlg 消息处理程序


void CAdminApplyDlg::UpdateCombo()
{	// 加载最新的消息列表到下拉框
	FileIO file;
	file.ReadMessage();
	int count = 1;
	m_combo.ResetContent();
	for (vector<message>::iterator it = file.messagev.begin(); it != file.messagev.end(); it++)
	{
		CString str;
		str.Format(_T("消息%d"), count);
		m_combo.AddString(str);		// 通过课程号在课程列表中找到对应的课程名字
		count++;
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CAdminApplyDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 读取消息列表，添加进下拉框中
	UpdateCombo();
}


void CAdminApplyDlg::OnBnClickedButton1()
{	// 查看消息
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 获取下拉框所选择的消息
	int selectnum = m_combo.GetCurSel();
	FileIO file;
	file.ReadMessage();
	message tmp = file.messagev[selectnum];
	
	// 将message输出到右侧m_message中
	m_message.Empty();	// 先清空框中原本的信息
	CString str;
	str = _T("申请教师：") + (CString)tmp.teaname.c_str();	// 教师姓名
	str += (_T("\r\n教师编号：") + (CString)tmp.teanum.c_str());	// 教师编号
	str += (_T("\r\n新课程名：") + (CString)tmp.coursename.c_str());	// 新课程名
	CString planstr = (CString)tmp.courseplan.c_str();		// 处理授课计划字符串
	planstr.Replace(_T("&"), _T("\r\n"));
	str += (_T("\r\n授课计划：\r\n") + planstr);		// 授课计划
	m_message = str;
	UpdateData(FALSE);
}


void CAdminApplyDlg::OnBnClickedButton2()
{	// 将当前消息标为已读，并从数据中删除该条消息
	// TODO: 在此添加控件通知处理程序代码
	// 先清空框中内容
	UpdateData(TRUE);
	FileIO file;
	file.ReadMessage();
	// 获取下拉框所选择的消息
	int selectnum = m_combo.GetCurSel();
	vector<message>::iterator  it = file.messagev.begin() + selectnum;
	file.messagev.erase(it);
	CString str;
	str.Format(_T("成功删除消息%d"), selectnum + 1);
	MessageBox(str);
	file.WriteMessage();
	m_message.Empty();
	UpdateCombo();
}

