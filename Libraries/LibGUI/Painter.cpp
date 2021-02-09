#include <LibGUI/Painter.h>

#include <LibC/string.h>
#include <LibGUI/Font.h>

Painter Painter::s_Instance;

void Painter::Init(const FrameBufferInfo& frameBufferInfo)
{
	m_FrameBufferInfo = frameBufferInfo;

	m_BackBuffer = new uint8_t[m_FrameBufferInfo.FramebufferHeight * m_FrameBufferInfo.FramebufferPitch];
}

void Painter::Clear(Color color) const
{
	uint8_t* screen = m_BackBuffer;
	for (uint32_t y = 0; y < m_FrameBufferInfo.FramebufferHeight; ++y)
	{
		uint32_t screenSpaceY = y * m_FrameBufferInfo.FramebufferPitch;
		for (uint32_t x = 0; x < m_FrameBufferInfo.FramebufferWidth; ++x)
		{
			uint32_t screenSpaceX = x * (m_FrameBufferInfo.FramebufferBpp / 8);
			screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
			screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
			screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;
		}
	}
}

void Painter::SwapBuffers()
{
	memcpy((void*)m_FrameBufferInfo.FramebufferAddress, (void*)m_BackBuffer, m_FrameBufferInfo.FramebufferHeight * m_FrameBufferInfo.FramebufferPitch);
}

void Painter::FillRect(const Rect& rect, Color color) const
{
	uint8_t* screen = m_BackBuffer;
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

void Painter::DrawRect(const Rect& rect, Color color) const
{
	uint8_t* screen = m_BackBuffer;
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

void Painter::DrawText(const Rect& rect, const AK::String& string, TextAlignment textAlignment, const Color& color)
{
	for (size_t i = 0; i < string.length(); i++)
	{
		switch (textAlignment)
		{
		case TextAlignment::CENTER:
		{
			uint32_t x = ((rect.GetX() + rect.GetWidth()) / 2) - ((string.length() / 2) * FONT_WIDTH - 1);
			uint32_t y = (rect.GetY() + rect.GetHeight()) / 2;
			PutChar(string[i], Point{ x + i * FONT_WIDTH - 1, y }, color);
			break;
		}
		case TextAlignment::TOP_LEFT:
		{
			uint32_t x = rect.GetX() + 6;
			uint32_t y = rect.GetY();
			PutChar(string[i], Point{ x + i * FONT_WIDTH - 1, y }, color);
			break;
		}
		case TextAlignment::LEFT:
		{
			uint32_t x = rect.GetX() + 6;
			uint32_t y = rect.GetY() + 6;
			PutChar(string[i], Point{ x + i * FONT_WIDTH - 1, y }, color);
			break;
		}
		default:
			return;
		}
	}
}

void Painter::PutChar(uint16_t c, const Point& cursorPosition, const Color& color)
{
	char* bitmap = (char*)font[c - FONT_OFFSET];
	uint8_t* screen = m_BackBuffer;
	for (size_t x = cursorPosition.GetX(); x < cursorPosition.GetX() + FONT_WIDTH; x++)
	{
		uint32_t screenSpaceX = x * (m_FrameBufferInfo.FramebufferBpp / 8);
		for (size_t y = cursorPosition.GetY(); y < cursorPosition.GetY() + FONT_HEIGHT; y++)
		{
			uint32_t screenSpaceY = y * m_FrameBufferInfo.FramebufferPitch;

			bool set = bitmap[y - cursorPosition.GetY()] & 1 << (x - cursorPosition.GetX());
			if (set)
			{
				screen[screenSpaceX + screenSpaceY + 0] = color.GetValue() & 255;
				screen[screenSpaceX + screenSpaceY + 1] = (color.GetValue() >> 8) & 255;
				screen[screenSpaceX + screenSpaceY + 2] = (color.GetValue() >> 16) & 255;
			}
		}
	}
}

uint32_t Painter::GetWidth() const
{
	return m_FrameBufferInfo.FramebufferWidth;
}

uint32_t Painter::GetHeight() const
{
	return m_FrameBufferInfo.FramebufferHeight;
}

Painter& Painter::Get()
{
	return s_Instance;
}