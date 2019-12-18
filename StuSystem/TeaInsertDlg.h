#pragma once
#include "afxwin.h"



// CTeaInsertDlg 窗体视图

class CTeaInsertDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaInsertDlg)

protected:
	CTeaInsertDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CTeaInsertDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_TEA_INSERT };
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
public:
	virtual void OnInitialUpdate();
private:
	CComboBox m_combo;
	CString m_stunum;
public:
	int m_score;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


