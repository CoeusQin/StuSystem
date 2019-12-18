
// MainFrm.cpp : CMainFrame 类的实现
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

	//ON_MESSAGE响应的是自定义消息
	//产生STU_X消息，自动调用OnMyChange()函数
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 设置窗体图标，IDI_ICON_WIN为图标资源ID，此处为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_RE));
	
	// 设置窗体右侧标题
	
	SetTitle(_T("欢迎使用学生成绩管理系统！"));

	//设置窗口大小
	MoveWindow(0, 0, 800, 500);
	//设置窗口居中
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	//静态拆分窗口，1行2列,CSplitterWnd::CreateStatic
	m_splitter.CreateStatic(this, 1, 2);
	//创建视图CSplitterWnd::CreateView
	//0，0	放在第0行第0列的位置
	//RUNTIME_CLASS(CSelectView) 需要头文件#include "SelectView.h"
	//CSelectView在SelectView.h中声明
	//CSize(200,500);	指定视图宽度和高度
	//pContext 为onCreateClient（）最后一个形参

	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);

	//0，1	放在第0行第1列的位置
	//RUNTIME_CLASS(CDisplayView) 需要头文件#include "DisplayView.h"
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	return TRUE;	// 表示自己拆分窗体
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	//
	CCreateContext context;
	if (CPublic::status == 1)
	{	// 进行学生消息判断
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
	{	// 进行教师消息判断
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
	{	// 进行管理员消息判断
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
	// TODO: 在此添加命令处理程序代码
	exit(0);
}
