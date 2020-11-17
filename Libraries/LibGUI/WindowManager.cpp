#include "WindowManager.h"

#include "Painter.h"
#include "Window.h"

WindowManager WindowManager::m_Instance;

void WindowManager::AddWindow(Window& window)
{
	//m_Windows.push_back(&window);
}

void WindowManager::PaintWindowFrames()
{
	//for (auto* window : m_Windows)
	//	PaintWindowFrame(*window);
}

void WindowManager::PaintWindowFrame(Window& window)
{
	Painter& painter = Painter::Get();

	static constexpr uint8_t windowFrameWidth = 2;
	static constexpr uint8_t windowTitleBarHeight = 16;

	Rect topRect
	{
		window.GetX() - windowFrameWidth,
		window.GetY() - windowTitleBarHeight - windowFrameWidth,
		window.GetWidth() + windowFrameWidth * 2,
		windowTitleBarHeight + windowFrameWidth
	};

	Rect bottomRect
	{
		window.GetX() - windowFrameWidth,
		window.GetY() + window.GetHeight(),
		window.GetWidth() + windowFrameWidth * 2,
		windowFrameWidth
	};

	Rect leftRect
	{
		window.GetX() - windowFrameWidth,
		window.GetY(),
		windowFrameWidth,
		window.GetHeight()
	};

	Rect rightRect
	{
		window.GetX() + window.GetWidth(),
		window.GetY(),
		windowFrameWidth,
		window.GetHeight()
	};

	const Color windowBorderColor = Color(0x11, 0x11, 0x11);
	const Color windowTitleColor = Color(0xFF, 0xFF, 0xFF);

	Rect borderRect
	{
		topRect.GetX() - 1,
		topRect.GetY() - 1,
		topRect.GetWidth() + 2,
		windowFrameWidth + windowTitleBarHeight + window.GetHeight() + 4
	};

	painter.DrawRect(borderRect, Color(255, 255, 255));
	borderRect.Inflate(2, 2);
	painter.DrawRect(borderRect, windowBorderColor);

	painter.FillRect(window.GetRect(), Color(0xBB, 0xBB, 0xBB));
	painter.FillRect(topRect, windowBorderColor);
	painter.FillRect(bottomRect, windowBorderColor);
	painter.FillRect(leftRect, windowBorderColor);
	painter.FillRect(rightRect, windowBorderColor);

	//painter.DrawText(topRect, window.GetTitle(), Painter::TextAlignment::Center, windowTitleColor);
}

WindowManager& WindowManager::Get()
{
	return m_Instance;
}
