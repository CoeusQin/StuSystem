#pragma once
#include "afxwin.h"



// CAdminApplyDlg ������ͼ

class CAdminApplyDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdminApplyDlg)

protected:
	CAdminApplyDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo;
	CString m_message;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnInitialUpdate();

	// �������µ���Ϣ�б�������
	void UpdateCombo();
};


