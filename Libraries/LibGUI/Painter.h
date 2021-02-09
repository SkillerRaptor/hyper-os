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
		CENTER,
		TOP_LEFT,
		LEFT,
	};

private:
	FrameBufferInfo m_FrameBufferInfo;

	uint8_t* m_BackBuffer = nullptr;

	static Painter s_Instance;

public:
	void Init(const FrameBufferInfo& frameBufferInfo);

	void Clear(Color color) const;
	void SwapBuffers();

	void FillRect(const Rect& rect, Color color) const;
	void DrawRect(const Rect& rect, Color color) const;
	void DrawText(const Rect& rect, const AK::String& string, TextAlignment textAlignment = TextAlignment::TOP_LEFT, const Color& color = Color{ 100, 100, 100 });

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	static Painter& Get();

private:
	void PutChar(uint16_t c, const Point& cursorPosition, const Color& color);
};