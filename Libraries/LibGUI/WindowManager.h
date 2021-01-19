#pragma once

//#include <AK/Vector.h>

#include "Rect.h"

class Painter;
class Window;

class WindowManager
{
private:
	//Vector<Window*> m_Windows; // TODO: Hash Table

public:
	WindowManager() = default;

	void AddWindow(Window& window);
	void PaintWindowFrame(Painter* painter, Window& window);
	void PaintWindowFrames();
};