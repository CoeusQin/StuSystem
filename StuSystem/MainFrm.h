
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

//WM_USER		���û��Զ�����Ϣ��һ����ʼֵ
//WM_USER+100	��Ϊ������ϵͳ��Ϣ���û���Ϣ�������ͻ
#define STU_A	WM_USER+100	// ���ѧ����Ϣ
#define STU_B	WM_USER+101	
#define STU_C	WM_USER+102	
#define STU_D	WM_USER+103	
#define STU_E	WM_USER+104	

#define TEA_A	WM_USER+105	// �����ʦ��Ϣ
#define TEA_B	WM_USER+106	
#define TEA_C	WM_USER+107	
#define TEA_D	WM_USER+108	
#define TEA_E	WM_USER+109	

#define ADMIN_A	WM_USER+110	// �ĸ�����Ա��Ϣ
#define ADMIN_B	WM_USER+111	
#define ADMIN_C	WM_USER+112	
#define ADMIN_D	WM_USER+113	
//#define ADMIN_E WM_USER+114	// ���ѧ��
//#define ADMIN_F WM_USER+115	// ɾ��ѧ��
//#define ADMIN_G WM_USER+116 // ��ӽ�ʦ
//#define ADMIN_H WM_USER+117 // ɾ����ʦ

class CMainFrame : public CFrameWnd
{							  
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	// �зִ��ڶ���
	CSplitterWnd m_splitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32771();
};


