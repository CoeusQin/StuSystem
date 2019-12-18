#pragma once
#include "afxwin.h"



// CAdminDeleteDlg 窗体视图

class CAdminDeleteDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdminDeleteDlg)

protected:
	CAdminDeleteDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdminDeleteDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_DELETE };
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
//	CString m_querynum;
//	CString m_deletenum;
//	CString m_detail;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
private:
	CComboBox m_combo;
public:
	virtual void OnInitialUpdate();
private:
	CString m_detail;
public:
	afx_msg void OnCbnSelchangeCombo1();
};


