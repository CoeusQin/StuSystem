// SelectView.cpp : 实现文件
//

#include "stdafx.h"
#include "StuSystem.h"
#include "SelectView.h"
#include "Public.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//图标资源的加载CWinApp::LoadIcon
	//IDI_ICON_RE为图标资源的ID
	HICON icon = AfxGetApp()->LoadIconW(IDI_TEST);

	//图片列表的创建CImageList::Create
	//30,30	指定图标的宽度和高度
	//ILC_COLOR32	图标格式
	//1，1	有多少图标就写多少个
	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);

	//图片列表添加图标CImageList::Add
	m_imageList.Add(icon);

	//获取视图的树控件CImageList::GetTreeCtrl
	m_treeCtrl = &GetTreeCtrl();

	//树控件设置图片列表CTreeCtrl::SetImageList
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//树控件设置节点CTreeCtrl::InsertItem
	// 学生身份登录
	if (CPublic::status == 1)
	{
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("查看成绩"), 0, 0, NULL);
	}
	else if (CPublic::status == 2)	// 教师身份登录
	{
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("录入成绩"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("修改成绩"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("查看比例"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("申请新课程"), 0, 0, NULL);
	}
	else if (CPublic::status == 3)	// 管理员身份登录
	{
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("教师开课申请"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("添加课程"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("删除课程"), 0, 0, NULL);
		/*m_treectrl->insertitem(_t("添加学生"), 0, 0, null);
		m_treectrl->insertitem(_t("删除学生"), 0, 0, null);
		m_treectrl->insertitem(_t("添加教师"), 0, 0, null);
		m_treectrl->insertitem(_t("删除教师"), 0, 0, null);*/
	}
}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前选中项
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	// 通过选中的项，获取选中项的内容
	CString str = m_treeCtrl->GetItemText(item);
	// 进行学生界面的判断
	if (CPublic::status == 1)
	{
		if (str == _T("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), STU_A, (WPARAM)STU_A, (LPARAM)0);
		}
		else if (str ==_T("查看成绩"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), STU_B, (WPARAM)STU_B, (LPARAM)0);
		}
	}
	// 进行教师界面判断
	else if (CPublic::status == 2)
	{
		if (str == _T("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_A, (WPARAM)TEA_A, (LPARAM)0);
		}
		else if (str == _T("录入成绩"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_B, (WPARAM)TEA_B, (LPARAM)0);
		}
		else if (str == _T("修改成绩"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_C, (WPARAM)TEA_C, (LPARAM)0);
		}
		else if (str == _T("查看比例"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_D, (WPARAM)TEA_D, (LPARAM)0);
		}
		else if (str == _T("申请新课程"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_E, (WPARAM)TEA_E, (LPARAM)0);
		}
	}
	// 进行管理员界面挂载判断
	else if (CPublic::status == 3)
	{	
		if (str == _T("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_A, (WPARAM)ADMIN_A, (LPARAM)0);
		}
		else if (str == _T("教师开课申请"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_B, (WPARAM)ADMIN_B, (LPARAM)0);
		}
		else if (str == _T("添加课程"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_C, (WPARAM)ADMIN_C, (LPARAM)0);
		}
		else if (str == _T("删除课程"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_D, (WPARAM)ADMIN_D, (LPARAM)0);
		}
		/*else if (str == _T("添加学生"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_E, (WPARAM)ADMIN_E, (LPARAM)0);
		}
		else if (str == _T("删除学生"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_F, (WPARAM)ADMIN_F, (LPARAM)0);
		}
		else if (str == _T("添加教师"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_G, (WPARAM)ADMIN_G, (LPARAM)0);
		}
		else if (str == _T("删除教师"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_H, (WPARAM)ADMIN_H, (LPARAM)0);
		}*/
	}
}
