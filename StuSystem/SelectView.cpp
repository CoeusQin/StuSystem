// SelectView.cpp : ʵ���ļ�
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


// CSelectView ���

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


// CSelectView ��Ϣ�������


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//ͼ����Դ�ļ���CWinApp::LoadIcon
	//IDI_ICON_REΪͼ����Դ��ID
	HICON icon = AfxGetApp()->LoadIconW(IDI_TEST);

	//ͼƬ�б�Ĵ���CImageList::Create
	//30,30	ָ��ͼ��Ŀ�Ⱥ͸߶�
	//ILC_COLOR32	ͼ���ʽ
	//1��1	�ж���ͼ���д���ٸ�
	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);

	//ͼƬ�б����ͼ��CImageList::Add
	m_imageList.Add(icon);

	//��ȡ��ͼ�����ؼ�CImageList::GetTreeCtrl
	m_treeCtrl = &GetTreeCtrl();

	//���ؼ�����ͼƬ�б�CTreeCtrl::SetImageList
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//���ؼ����ýڵ�CTreeCtrl::InsertItem
	// ѧ����ݵ�¼
	if (CPublic::status == 1)
	{
		m_treeCtrl->InsertItem(TEXT("������Ϣ"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("�鿴�ɼ�"), 0, 0, NULL);
	}
	else if (CPublic::status == 2)	// ��ʦ��ݵ�¼
	{
		m_treeCtrl->InsertItem(TEXT("������Ϣ"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("¼��ɼ�"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("�޸ĳɼ�"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("�鿴����"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("�����¿γ�"), 0, 0, NULL);
	}
	else if (CPublic::status == 3)	// ����Ա��ݵ�¼
	{
		m_treeCtrl->InsertItem(TEXT("������Ϣ"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("��ʦ��������"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("��ӿγ�"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("ɾ���γ�"), 0, 0, NULL);
		/*m_treectrl->insertitem(_t("���ѧ��"), 0, 0, null);
		m_treectrl->insertitem(_t("ɾ��ѧ��"), 0, 0, null);
		m_treectrl->insertitem(_t("��ӽ�ʦ"), 0, 0, null);
		m_treectrl->insertitem(_t("ɾ����ʦ"), 0, 0, null);*/
	}
}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//��ȡ��ǰѡ����
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	// ͨ��ѡ�е����ȡѡ���������
	CString str = m_treeCtrl->GetItemText(item);
	// ����ѧ��������ж�
	if (CPublic::status == 1)
	{
		if (str == _T("������Ϣ"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), STU_A, (WPARAM)STU_A, (LPARAM)0);
		}
		else if (str ==_T("�鿴�ɼ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), STU_B, (WPARAM)STU_B, (LPARAM)0);
		}
	}
	// ���н�ʦ�����ж�
	else if (CPublic::status == 2)
	{
		if (str == _T("������Ϣ"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_A, (WPARAM)TEA_A, (LPARAM)0);
		}
		else if (str == _T("¼��ɼ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_B, (WPARAM)TEA_B, (LPARAM)0);
		}
		else if (str == _T("�޸ĳɼ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_C, (WPARAM)TEA_C, (LPARAM)0);
		}
		else if (str == _T("�鿴����"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_D, (WPARAM)TEA_D, (LPARAM)0);
		}
		else if (str == _T("�����¿γ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), TEA_E, (WPARAM)TEA_E, (LPARAM)0);
		}
	}
	// ���й���Ա��������ж�
	else if (CPublic::status == 3)
	{	
		if (str == _T("������Ϣ"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_A, (WPARAM)ADMIN_A, (LPARAM)0);
		}
		else if (str == _T("��ʦ��������"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_B, (WPARAM)ADMIN_B, (LPARAM)0);
		}
		else if (str == _T("��ӿγ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_C, (WPARAM)ADMIN_C, (LPARAM)0);
		}
		else if (str == _T("ɾ���γ�"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_D, (WPARAM)ADMIN_D, (LPARAM)0);
		}
		/*else if (str == _T("���ѧ��"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_E, (WPARAM)ADMIN_E, (LPARAM)0);
		}
		else if (str == _T("ɾ��ѧ��"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_F, (WPARAM)ADMIN_F, (LPARAM)0);
		}
		else if (str == _T("��ӽ�ʦ"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_G, (WPARAM)ADMIN_G, (LPARAM)0);
		}
		else if (str == _T("ɾ����ʦ"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), ADMIN_H, (WPARAM)ADMIN_H, (LPARAM)0);
		}*/
	}
}
