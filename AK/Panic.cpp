#include <AK/Panic.h>

#include <LibGUI/Painter.h>

void Panic(const String& string)
{
    Painter& painter = Painter::Get();
    painter.Clear(Color{ 8, 39, 245 });
}