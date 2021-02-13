#pragma once

#include <AK/String.hpp>
#include <LibGUI/Rect.h>
#include <LibGUI/Widget.h>

class Window
{
private:
	String m_Title;
	Rect m_Rect;
	Widget* m_MainWidget;

public:
	Window();

	void SetTitle(const String& title);
	const String& GetTitle() const;

	uint32_t GetX() const;
	uint32_t GetY() const;
	uint32_t GetWidth() const;
	uint32_t GetHeight();

	void SetRect(const Rect& rect);
	const Rect& GetRect() const;

	void SetMainWidget(Widget* widget);
	Widget* GetMainWidget();
	const Widget* GetMainWidget() const;
};