
// RP_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRP_MFCApp:
// �йش����ʵ�֣������ RP_MFC.cpp
//

class CRP_MFCApp : public CWinAppEx
{
public:
	CRP_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRP_MFCApp theApp;