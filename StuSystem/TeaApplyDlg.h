#pragma once



// CTeaApplyDlg ������ͼ

class CTeaApplyDlg : public CFormView
{
	DECLARE_DYNCREATE(CTeaApplyDlg)

protected:
	CTeaApplyDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_coursename;
	CString m_teaname;
	CString m_plan;
public:
	afx_msg void OnBnClickedOk();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedCancel();

	// ��ʦ���
	CString teanum;
};


