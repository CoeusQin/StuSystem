#pragma once



// CTeaApplyDlg 窗体视图

class CTeaApplyDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaApplyDlg)

protected:
	CTeaApplyDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CTeaApplyDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
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
	CString m_teaname;
	CString m_plan;
public:
	afx_msg void OnBnClickedOk();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCancel();

	// 教师编号
	CString teanum;
};


