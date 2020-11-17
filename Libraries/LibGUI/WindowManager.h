#pragma once

//#include <AK/Vector.h>

#include "Rect.h"

class Window;

class WindowManager
{
private:
	//Vector<Window*> m_Windows; // TODO: Hash Table

	static WindowManager m_Instance;

public:
	WindowManager() = default;

	void AddWindow(Window& window);
	void PaintWindowFrame(Window& window);
	void PaintWindowFrames();

	static WindowManager& Get();

private:
};