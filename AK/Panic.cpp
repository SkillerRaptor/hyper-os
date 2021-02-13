#include <AK/Panic.h>

#include <AK/StringBuilder.h>
#include <LibGUI/Font.h>
#include <LibGUI/Painter.h>

void panic(const String& string)
{
	asm volatile ("cli" :: : "memory");

	Painter& painter = Painter::Get();
	painter.Clear(Color{ 8, 39, 245 });

	Color textColor{ 255, 255, 255 };

	uint32_t y = painter.GetHeight() / 4;

	painter.DrawText(Rect{ 0, y, painter.GetWidth(), 1 }, "Kernel Panic!", Painter::TextAlignment::CENTER, textColor);

	painter.DrawText(Rect{ 0, y + (1 * FONT_HEIGHT), painter.GetWidth(), 1 }, String{ string }, Painter::TextAlignment::LEFT, textColor);

	register uint64_t rax asm("%rax");
	register uint64_t rbx asm("%rbx");
	register uint64_t rcx asm("%rcx");
	register uint64_t rdx asm("%rdx");

	register uint64_t rsi asm("%rsi");
	register uint64_t rdi asm("%rdi");
	register uint64_t rbp asm("%rbp");
	register uint64_t rsp asm("%rsp");

	register uint64_t r8 asm("%r8");
	register uint64_t r9 asm("%r9");
	register uint64_t r10 asm("%r10");
	register uint64_t r11 asm("%r11");

	register uint64_t r12 asm("%r12");
	register uint64_t r13 asm("%r13");
	register uint64_t r14 asm("%r14");
	register uint64_t r15 asm("%r15");

	StringBuilder builder;
	painter.DrawText(Rect{ 0, y + (2 * FONT_HEIGHT), painter.GetWidth(), 1 }, "Register dump:", Painter::TextAlignment::LEFT, textColor);

	builder.append("rax=");
	builder.append(to_hex_string(rax));
	builder.append(" rbx=");
	builder.append(to_hex_string(rbx));
	builder.append(" rcx=");
	builder.append(to_hex_string(rcx));
	builder.append(" rdx=");
	builder.append(to_hex_string(rdx));
	painter.DrawText(Rect{ 0, y + (3 * FONT_HEIGHT), painter.GetWidth(), 1 }, builder.build(), Painter::TextAlignment::LEFT, textColor);
	builder.clear();

	builder.append("rsi=");
	builder.append(to_hex_string(rsi));
	builder.append(" rdi=");
	builder.append(to_hex_string(rdi));
	builder.append(" rbp=");
	builder.append(to_hex_string(rbp));
	builder.append(" rsp=");
	builder.append(to_hex_string(rsp));
	painter.DrawText(Rect{ 0, y + (4 * FONT_HEIGHT), painter.GetWidth(), 1 }, builder.build(), Painter::TextAlignment::LEFT, textColor);
	builder.clear();

	builder.append(" r8=");
	builder.append(to_hex_string(r8));
	builder.append("  r9=");
	builder.append(to_hex_string(r9));
	builder.append(" r10=");
	builder.append(to_hex_string(r10));
	builder.append(" r11=");
	builder.append(to_hex_string(r11));
	painter.DrawText(Rect{ 0, y + (5 * FONT_HEIGHT), painter.GetWidth(), 1 }, builder.build(), Painter::TextAlignment::LEFT, textColor);
	builder.clear();

	builder.append("r12=");
	builder.append(to_hex_string(r12));
	builder.append(" r13=");
	builder.append(to_hex_string(r13));
	builder.append(" r14=");
	builder.append(to_hex_string(r14));
	builder.append(" r15=");
	builder.append(to_hex_string(r15));
	painter.DrawText(Rect{ 0, y + (6 * FONT_HEIGHT), painter.GetWidth(), 1 }, builder.build(), Painter::TextAlignment::LEFT, textColor);
	builder.clear();

	painter.DrawText(Rect{ 0, y + (8 * FONT_HEIGHT), painter.GetWidth(), 1 }, "Backtrace:", Painter::TextAlignment::LEFT, textColor);

	painter.SwapBuffers();

	asm volatile ("hlt" :: : "memory");
	while (true);
}