#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "stdafx.h"

class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual void    Notify(TNotifyUI& msg) 
	{
		if (msg.sType == _T("click"))
		{
			//取得控件的name，然后进行操作
			if (msg.pSender->GetName() == _T("btnHello"))
			{
				::MessageBox(NULL, _T("我是按钮"), _T("点击了按钮"), NULL);
			}
		}
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;

		if (uMsg == WM_CREATE)
		{
			m_PaintManager.Init(m_hWnd);

			CDialogBuilder builder;
			CControlUI* pWnd = builder.Create(_T("test001.xml"), (UINT)0, NULL, &m_PaintManager);   // test001.xml需要放到exe目录下
			ASSERT(pWnd && "Failed to parse XML");

			m_PaintManager.AttachDialog(pWnd);
			m_PaintManager.AddNotifier(this);// 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
			return lRes;
		}  
#if 0
		// 以下3个消息WM_NCACTIVATE、WM_NCCALCSIZE、WM_NCPAINT用于屏蔽系统标题栏
		else if (uMsg == WM_NCACTIVATE)
		{
			if (!::IsIconic(m_hWnd))
			{
				return (wParam == 0) ? TRUE : FALSE;
			}
		 } else if (uMsg == WM_NCCALCSIZE){
			return 0;
		 } else if (uMsg == WM_NCPAINT){
			return 0;
		 }
#endif

		if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	CPaintManagerUI m_PaintManager;
};

#endif