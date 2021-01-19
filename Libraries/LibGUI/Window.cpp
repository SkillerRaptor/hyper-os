#include <LibGUI/Window.h>

#include <LibGUI/WindowManager.h>

Window::Window()
{
	//WindowManager::Get()->AddWindow(*this);
}

void Window::SetTitle(const String& title)
{
	//if (m_Title == title)
	//	return;
	m_Title = title;
}

const String& Window::GetTitle() const
{
	return m_Title;
}

uint32_t Window::GetX() const
{
	return m_Rect.GetX();
}

uint32_t Window::GetY() const
{
	return m_Rect.GetY();
}

uint32_t Window::GetWidth() const
{
	return m_Rect.GetWidth();
}

uint32_t Window::GetHeight()
{
	return m_Rect.GetHeight();
}

void Window::SetRect(const Rect& rect)
{
	if (m_Rect == rect)
		return;
	m_Rect = rect;
}

const Rect& Window::GetRect() const
{
	return m_Rect;
}

void Window::SetMainWidget(Widget* widget)
{
	m_MainWidget = widget;
}

Widget* Window::GetMainWidget()
{
	return m_MainWidget;
}

const Widget* Window::GetMainWidget() const
{
	return m_MainWidget;
}
