
// StuSystem.h : StuSystem Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CStuSystemApp:
// �йش����ʵ�֣������ StuSystem.cpp
//

class CStuSystemApp : public CWinApp
{
public:
	CStuSystemApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStuSystemApp theApp;
