include ../../Makefile.common

OBJS = \
	Color.o \
	Painter.o \
	Point.o \
	Rect.o \
	Widget.o \
	Window.o \
	WindowManager.o

APP = libgui.a

all: $(APP)

$(APP): $(OBJS)
	@echo "LIB $@"; $(AR) rcs $@ $(OBJS)

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS)

-include $(OBJS:%.o=%.d)