#pragma once
#include "afxcmn.h"



// CScoreDlg ������ͼ

class CScoreDlg : public CFormView
{
	DECLARE_DYNCREATE(CScoreDlg)

protected:
	CScoreDlg();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CScoreDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_STU_SCORE };
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
//	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
private:
	CListCtrl m_list;
};


