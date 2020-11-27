#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "stdafx.h"
#include <windows.h>
#if !defined(UNDER_CE)
#include <shellapi.h>
#endif

#include "UIGroups.hpp"
#include "UIMicroBlog.hpp"
#include "main_frame.hpp"
#include "color_skin.hpp"
#include "chat_dialog.hpp"

#endif // MAINFRAME_HPP

class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual void    Notify(TNotifyUI& msg) 
	{
		if (msg.sType == _T("click"))
		{
			//��һ����ֵ������
			if (msg.pSender->GetName() == _T("btnHello"))
			{
				::MessageBox(NULL, _T("���ǰ�ť"), _T("����˰�ť"), NULL);
			}
		}
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			CControlUI *pWnd = new CButtonUI;
			pWnd->SetName(_T("btnHello"));      // ���ÿؼ������ƣ�����������ڱ�ʶÿһ���ؼ�������Ψһ���൱��MFC����Ŀؼ�ID
			pWnd->SetText(_T("Hello World"));   // ��������
			pWnd->SetBkColor(0xFF00FF00);       // ���ñ���ɫ

			m_PaintManager.Init(m_hWnd);
			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
			return lRes;
		}

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};