#pragma once
#include "afxwin.h"



// CAdminApplyDlg 窗体视图

class CAdminApplyDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdminApplyDlg)

protected:
	CAdminApplyDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdminApplyDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_APPLY };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo;
	CString m_message;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnInitialUpdate();

	// 加载最新的消息列表到下拉框
	void UpdateCombo();
};


