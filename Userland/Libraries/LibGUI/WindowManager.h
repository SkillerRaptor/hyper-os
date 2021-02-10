#pragma once

#include <AK/Vector.h>

class Painter;
class Window;

class WindowManager
{
private:
	Vector<Window*> m_Windows;

public:
	WindowManager() = default;

	void AddWindow(Window& window);
	void PaintWindowFrame(Window& window);
	void PaintWindowFrames();
};