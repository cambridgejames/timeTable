
// Timetable_3.1.1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTimetable_311App: 
// �йش����ʵ�֣������ Timetable_3.1.1.cpp
//

class CTimetable_311App : public CWinApp
{
public:
	CTimetable_311App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTimetable_311App theApp;