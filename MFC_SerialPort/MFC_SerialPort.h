
// MFC_SerialPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_SerialPortApp: 
// �йش����ʵ�֣������ MFC_SerialPort.cpp
//

class CMFC_SerialPortApp : public CWinApp
{
public:
	CMFC_SerialPortApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_SerialPortApp theApp;