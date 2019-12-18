#pragma once



// CAdminInfoDlg 窗体视图

class CAdminInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CAdminInfoDlg)

protected:
	CAdminInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdminInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADM_INFO };
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
	CString m_status;
public:
	virtual void OnInitialUpdate();
private:
	CString m_name;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
private:
	CString m_newPwd;
	CString m_surePwd;
};


