
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "StuSystem.h"
#include "LoginDlg.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "Public.h"
#include "UserDlg.h"
#include "ScoreDlg.h"
#include "TeaInfoDlg.h"
#include "TeaInsertDlg.h"
#include "TeaUpdateDlg.h"
#include "TeaRatio.h"
#include "TeaApplyDlg.h"
#include "AdminInfoDlg.h"
#include "AdminApplyDlg.h"
#include "AdminInsertDlg.h"
#include "AdminDeleteDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE��Ӧ�����Զ�����Ϣ
	//����STU_X��Ϣ���Զ�����OnMyChange()����
	ON_MESSAGE(STU_A, OnMyChange)
	ON_MESSAGE(STU_B, OnMyChange)
	ON_MESSAGE(STU_C, OnMyChange)
	ON_MESSAGE(STU_D, OnMyChange)
	ON_MESSAGE(STU_E, OnMyChange)

	ON_MESSAGE(TEA_A, OnMyChange)
	ON_MESSAGE(TEA_B, OnMyChange)
	ON_MESSAGE(TEA_C, OnMyChange)
	ON_MESSAGE(TEA_D, OnMyChange)
	ON_MESSAGE(TEA_E, OnMyChange)

	ON_MESSAGE(ADMIN_A, OnMyChange)
	ON_MESSAGE(ADMIN_B, OnMyChange)
	ON_MESSAGE(ADMIN_C, OnMyChange)
	ON_MESSAGE(ADMIN_D, OnMyChange)
	ON_COMMAND(ID_32771, &CMainFrame::On32771)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// ���ô���ͼ�꣬IDI_ICON_WINΪͼ����ԴID���˴�ΪWINAPI����
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_RE));
	
	// ���ô����Ҳ����
	
	SetTitle(_T("��ӭʹ��ѧ���ɼ�����ϵͳ��"));

	//���ô��ڴ�С
	MoveWindow(0, 0, 800, 500);
	//���ô��ھ���
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	//��̬��ִ��ڣ�1��2��,CSplitterWnd::CreateStatic
	m_splitter.CreateStatic(this, 1, 2);
	//������ͼCSplitterWnd::CreateView
	//0��0	���ڵ�0�е�0�е�λ��
	//RUNTIME_CLASS(CSelectView) ��Ҫͷ�ļ�#include "SelectView.h"
	//CSelectView��SelectView.h������
	//CSize(200,500);	ָ����ͼ��Ⱥ͸߶�
	//pContext ΪonCreateClient�������һ���β�

	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);

	//0��1	���ڵ�0�е�1�е�λ��
	//RUNTIME_CLASS(CDisplayView) ��Ҫͷ�ļ�#include "DisplayView.h"
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE;	// ��ʾ�Լ���ִ���
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	//
	CCreateContext context;
	if (CPublic::status == 1)
	{	// ����ѧ����Ϣ�ж�
		if (STU_A == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &context);
			CUserDlg *pNewView = (CUserDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (STU_B == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CScoreDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CScoreDlg), CSize(600, 500), &context);
			CScoreDlg *pNewView = (CScoreDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
	}
	else if (CPublic::status == 2)
	{	// ���н�ʦ��Ϣ�ж�
		if (TEA_A == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CTeaInfoDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTeaInfoDlg), CSize(600, 500), &context);
			CTeaInfoDlg *pNewView = (CTeaInfoDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (TEA_B == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CTeaInsertDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTeaInsertDlg), CSize(600, 500), &context);
			CTeaInsertDlg *pNewView = (CTeaInsertDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (TEA_C == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CTeaUpdateDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTeaUpdateDlg), CSize(600, 500), &context);
			CTeaUpdateDlg *pNewView = (CTeaUpdateDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (TEA_D == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CTeaRatioDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTeaRatioDlg), CSize(600, 500), &context);
			CTeaRatioDlg *pNewView = (CTeaRatioDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (TEA_E == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CTeaApplyDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CTeaApplyDlg), CSize(600, 500), &context);
			CTeaApplyDlg *pNewView = (CTeaApplyDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
	}
	else if (CPublic::status == 3)
	{	// ���й���Ա��Ϣ�ж�
		if (ADMIN_A == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CAdminInfoDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdminInfoDlg), CSize(600, 500), &context);
			CAdminInfoDlg *pNewView = (CAdminInfoDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (ADMIN_B == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CAdminApplyDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdminApplyDlg), CSize(600, 500), &context);
			CAdminApplyDlg *pNewView = (CAdminApplyDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (ADMIN_C == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CAdminInsertDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdminInsertDlg), CSize(600, 500), &context);
			CAdminInsertDlg *pNewView = (CAdminInsertDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
		else if (ADMIN_D == wParam)
		{
			context.m_pNewViewClass = RUNTIME_CLASS(CAdminDeleteDlg);
			context.m_pCurrentFrame = this;
			context.m_pLastView = (CFormView *)m_splitter.GetPane(0, 1);
			m_splitter.DeleteView(0, 1);
			m_splitter.CreateView(0, 1, RUNTIME_CLASS(CAdminDeleteDlg), CSize(600, 500), &context);
			CAdminDeleteDlg *pNewView = (CAdminDeleteDlg *)m_splitter.GetPane(0, 1);
			m_splitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_splitter.SetActivePane(0, 1);
		}
	}

	return 0;
}


void CMainFrame::On32771()
{
	// TODO: �ڴ���������������
	exit(0);
}
