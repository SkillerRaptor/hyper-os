#include "Painter.h"

void Painter::Init(const FrameBufferInfo& frameBufferInfo)
{
	m_FrameBufferInfo = frameBufferInfo;
}

void Painter::FillRect(const Rect& rect, Color color)
{
	uint8_t* screen = (uint8_t*)m_FrameBufferInfo.FramebufferAddress;
	for (uint32_t y = rect.GetTop(); y < rect.GetBottom(); ++y)
	{
		uint32_t screenSpaceY = y * m_FrameBufferInfo.FramebufferPitch;
		for (uint32_t x = rect.GetLeft(); x < rect.GetRight(); ++x)
		{
			uint32_t screenSpaceX = x * (m_FrameBufferInfo.FramebufferBpp / 8);
			screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
			screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
			screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;
		}
	}
}

void Painter::DrawRect(const Rect& rect, Color color)
{
	uint8_t* screen = (uint8_t*)m_FrameBufferInfo.FramebufferAddress;
	for (uint32_t y = rect.GetTop(); y < rect.GetBottom(); ++y)
	{
		uint32_t screenSpaceY = y * m_FrameBufferInfo.FramebufferPitch;
		if (y == rect.GetTop() || y == (rect.GetBottom() - 1))
		{
			for (uint32_t x = rect.GetLeft(); x < rect.GetRight(); ++x)
			{
				uint32_t screenSpaceX = x * (m_FrameBufferInfo.FramebufferBpp / 8);
				screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
				screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
				screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;
			}
		}
		else
		{
			uint32_t screenSpaceX = rect.GetLeft() * (m_FrameBufferInfo.FramebufferBpp / 8);
			screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
			screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
			screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;

			screenSpaceX = (rect.GetRight() - 1) * (m_FrameBufferInfo.FramebufferBpp / 8);
			screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
			screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
			screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;
		}
	}
}