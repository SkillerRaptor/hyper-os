#pragma once

#include <AK/String.h>
#include <LibGUI/Rect.h>
#include <LibGUI/Widget.h>

class Window
{
private:
	AK::String m_Title;
	Rect m_Rect;
	Widget* m_MainWidget;

public:
	Window();

	void SetTitle(const AK::String& title);
	const AK::String& GetTitle() const;

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