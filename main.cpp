//
// win_impl_base.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2011 achellies (achellies at 163 dot com), wangchyz (wangchyz at gmail dot com)
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#include "stdafx.h"
#include "..\DuiLib\Utils\WinImplBase.h"

#include <atlbase.h>
CComModule _Module;
#include <atlwin.h>

/*
	入口函数
*/
#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	/*init相关操作*/
    CPaintManagerUI::SetInstance(hInstance);	//句柄初始化
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HINSTANCE hInstRich = ::LoadLibrary(_T("Riched20.dll"));	//字符编辑库

	::CoInitialize(NULL);
	::OleInitialize(NULL);

	_Module.Init( 0, hInstance );

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if( FAILED(Hr) ) return 0;
	/*结束init相关操作*/

	
	/*开始exit操作*/
	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	_Module.Term();

	::OleUninitialize();
	::CoUninitialize();

	::FreeLibrary(hInstRich);
	/*结束exit操作*/

	return 0;
}