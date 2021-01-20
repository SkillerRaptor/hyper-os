#pragma once

#include <AK/String.h>
#include <LibC/stdint.h>
#include <LibGUI/Color.h>
#include <LibGUI/Rect.h>

struct FrameBufferInfo
{
	uint64_t FramebufferAddress;
	uint16_t FramebufferPitch;
	uint16_t FramebufferWidth;
	uint16_t FramebufferHeight;
	uint16_t FramebufferBpp;
};

class Painter
{
public:
	enum class TextAlignment
	{
		TOP_LEFT,
		CENTER
	};

private:
	FrameBufferInfo m_FrameBufferInfo;

	static Painter m_Instance;

public:
	void Init(const FrameBufferInfo& frameBufferInfo);

	void Clear(Color color) const;

	void FillRect(const Rect& rect, Color color) const;
	void DrawRect(const Rect& rect, Color color) const;
	void DrawText(const Rect& rect, const String& string, TextAlignment textAlignment = TextAlignment::TOP_LEFT, const Color& color = Color{ 100, 100, 100 });

	static Painter& Get();

private:
	void PutChar(uint16_t c, const Point& cursorPosition, const Color& color);
};