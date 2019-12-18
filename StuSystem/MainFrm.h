
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

//WM_USER		是用户自定义消息的一个起始值
//WM_USER+100	是为了区分系统消息和用户消息，避免冲突
#define STU_A	WM_USER+100	// 五个学生消息
#define STU_B	WM_USER+101	
#define STU_C	WM_USER+102	
#define STU_D	WM_USER+103	
#define STU_E	WM_USER+104	

#define TEA_A	WM_USER+105	// 五个教师消息
#define TEA_B	WM_USER+106	
#define TEA_C	WM_USER+107	
#define TEA_D	WM_USER+108	
#define TEA_E	WM_USER+109	

#define ADMIN_A	WM_USER+110	// 四个管理员消息
#define ADMIN_B	WM_USER+111	
#define ADMIN_C	WM_USER+112	
#define ADMIN_D	WM_USER+113	
//#define ADMIN_E WM_USER+114	// 添加学生
//#define ADMIN_F WM_USER+115	// 删除学生
//#define ADMIN_G WM_USER+116 // 添加教师
//#define ADMIN_H WM_USER+117 // 删除教师

class CMainFrame : public CFrameWnd
{							  
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	// 切分窗口对象
	CSplitterWnd m_splitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32771();
};


