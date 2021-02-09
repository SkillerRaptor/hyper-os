include ../Makefile.common

OBJS = \
	./Bitmap.o \
	./Exception.o \
	./IO.o \
	./Panic.o \
	./String.o \
	./StringBuilder.o

APP = AK

all: $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)