#pragma once
#include "afxwin.h"



// CTeaRatio ������ͼ

class CTeaRatioDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaRatioDlg)

protected:
	CTeaRatioDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTeaRatioDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_RATIO };
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
private:
	CComboBox m_combo;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
private:
	CString m_ratio;
public:
	virtual void OnInitialUpdate();
};


