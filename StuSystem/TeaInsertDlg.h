#pragma once
#include "afxwin.h"



// CTeaInsertDlg ������ͼ

class CTeaInsertDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaInsertDlg)

protected:
	CTeaInsertDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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


