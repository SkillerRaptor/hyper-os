#pragma once

#include <LibC/stdint.h>

#include "Color.h"
#include "Rect.h"

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

	void FillRect(const Rect& rect, Color color);
	void DrawRect(const Rect& rect, Color color);
	// TODO: void DrawText(const Rect& rect, const String& string, TextAlignment textAlignment = TextAlignment::TOP_LEFT, const Color& color = Color());

	static Painter& Get();
};