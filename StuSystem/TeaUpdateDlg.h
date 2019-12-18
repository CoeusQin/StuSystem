#pragma once
#include "afxwin.h"



// CTeaUpdateDlg ������ͼ

class CTeaUpdateDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaUpdateDlg)

protected:
	CTeaUpdateDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTeaUpdateDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_TEA_UPDATE };
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
	int m_score;
	int m_oldscore;
	int m_newscore;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};


