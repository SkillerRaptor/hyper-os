#pragma once

#include "Rect.h"
#include "Widget.h"

class Window
{
private:
	const char* m_Title; //TODO: String Class
	Rect m_Rect;
	Widget* m_MainWidget;

public:
	Window();

	void SetTitle(const char* title);
	const char* GetTitle() const;

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