#pragma once



// CTeaInfoDlg ������ͼ

class CTeaInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaInfoDlg)

protected:
	CTeaInfoDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTeaInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_TEA_INFO };
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
	CString m_newPwd;
	CString m_surePwd;
public:
	virtual void OnInitialUpdate();
private:
	CString m_teaname;
	CString m_teanum;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};


