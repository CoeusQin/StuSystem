#pragma once
#include "afxwin.h"



// CAdminInsertDlg 窗体视图

class CAdminInsertDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdminInsertDlg)

protected:
	CAdminInsertDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdminInsertDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_INSERT };
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
	CString m_coursename;
	CComboBox m_combo;
	int m_classnum;
//	CString m_courseid;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual void OnInitialUpdate();
private:
	int m_courseid;
};


