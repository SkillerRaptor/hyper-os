#include <AK/Logger.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/IDT.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	IDT::Entry IDT::s_entries[256]{};
	
	extern "C"
	{
		extern int interrupt_handler_0();
		extern int interrupt_handler_1();
		extern int interrupt_handler_2();
		extern int interrupt_handler_3();
		extern int interrupt_handler_4();
		extern int interrupt_handler_5();
		extern int interrupt_handler_6();
		extern int interrupt_handler_7();
		extern int interrupt_handler_8();
		extern int interrupt_handler_9();
		extern int interrupt_handler_10();
		extern int interrupt_handler_11();
		extern int interrupt_handler_12();
		extern int interrupt_handler_13();
		extern int interrupt_handler_14();
		extern int interrupt_handler_15();
		
		extern int exception_handler_0();
		extern int exception_handler_1();
		extern int exception_handler_2();
		extern int exception_handler_3();
		extern int exception_handler_4();
		extern int exception_handler_5();
		extern int exception_handler_6();
		extern int exception_handler_7();
		extern int exception_handler_8();
		extern int exception_handler_10();
		extern int exception_handler_11();
		extern int exception_handler_12();
		extern int exception_handler_13();
		extern int exception_handler_14();
		extern int exception_handler_16();
		extern int exception_handler_17();
		extern int exception_handler_18();
		extern int exception_handler_19();
		extern int exception_handler_20();
		extern int exception_handler_30();
	}
	
	void IDT::initialize()
	{
		AK::Logger::info("IDT: Initializing...!");
		
		IDT::register_interrupt_handler(32 + 0, (uintptr_t) interrupt_handler_0);
		IDT::register_interrupt_handler(32 + 1, (uintptr_t) interrupt_handler_1);
		IDT::register_interrupt_handler(32 + 2, (uintptr_t) interrupt_handler_2);
		IDT::register_interrupt_handler(32 + 3, (uintptr_t) interrupt_handler_3);
		IDT::register_interrupt_handler(32 + 4, (uintptr_t) interrupt_handler_4);
		IDT::register_interrupt_handler(32 + 5, (uintptr_t) interrupt_handler_5);
		IDT::register_interrupt_handler(32 + 6, (uintptr_t) interrupt_handler_6);
		IDT::register_interrupt_handler(32 + 7, (uintptr_t) interrupt_handler_7);
		IDT::register_interrupt_handler(32 + 8, (uintptr_t) interrupt_handler_8);
		IDT::register_interrupt_handler(32 + 9, (uintptr_t) interrupt_handler_9);
		IDT::register_interrupt_handler(32 + 10, (uintptr_t) interrupt_handler_10);
		IDT::register_interrupt_handler(32 + 11, (uintptr_t) interrupt_handler_11);
		IDT::register_interrupt_handler(32 + 12, (uintptr_t) interrupt_handler_12);
		IDT::register_interrupt_handler(32 + 13, (uintptr_t) interrupt_handler_13);
		IDT::register_interrupt_handler(32 + 14, (uintptr_t) interrupt_handler_14);
		IDT::register_interrupt_handler(32 + 15, (uintptr_t) interrupt_handler_15);
		
		IDT::register_trap_handler(0, (uintptr_t) exception_handler_0);
		IDT::register_trap_handler(1, (uintptr_t) exception_handler_1);
		IDT::register_trap_handler(2, (uintptr_t) exception_handler_2);
		IDT::register_trap_handler(3, (uintptr_t) exception_handler_3);
		IDT::register_trap_handler(4, (uintptr_t) exception_handler_4);
		IDT::register_trap_handler(5, (uintptr_t) exception_handler_5);
		IDT::register_trap_handler(6, (uintptr_t) exception_handler_6);
		IDT::register_trap_handler(7, (uintptr_t) exception_handler_7);
		IDT::register_trap_handler(8, (uintptr_t) exception_handler_8);
		IDT::register_trap_handler(10, (uintptr_t) exception_handler_10);
		IDT::register_trap_handler(11, (uintptr_t) exception_handler_11);
		IDT::register_trap_handler(12, (uintptr_t) exception_handler_12);
		IDT::register_trap_handler(13, (uintptr_t) exception_handler_13);
		IDT::register_trap_handler(14, (uintptr_t) exception_handler_14);
		IDT::register_trap_handler(16, (uintptr_t) exception_handler_16);
		IDT::register_trap_handler(17, (uintptr_t) exception_handler_17);
		IDT::register_trap_handler(18, (uintptr_t) exception_handler_18);
		IDT::register_trap_handler(19, (uintptr_t) exception_handler_19);
		IDT::register_trap_handler(20, (uintptr_t) exception_handler_20);
		IDT::register_trap_handler(30, (uintptr_t) exception_handler_30);
		
		IDT::reload();
		
		AK::Logger::info("IDT: Initializing finished!");
	}
	
	void IDT::reload()
	{
		IDT::Pointer pointer =
			{
				sizeof(s_entries) - 1,
				reinterpret_cast<uintptr_t>(s_entries)
			};
		
		asm volatile (
		"lidt %0"
		:
		: "m"(pointer)
		);
	}
	
	void IDT::register_handler(size_t index, uint8_t flags, uintptr_t handler)
	{
		s_entries[index].offset_low = (handler & 0x0000FFFF) >> 0;
		s_entries[index].selector = GDT::s_kernel_code_selector;
		s_entries[index].ist = 0x0;
		s_entries[index].attributes = flags;
		s_entries[index].offset_middle = (handler & 0xFFFF0000) >> 16;
		s_entries[index].offset_high = (handler & 0xFFFFFFFF00000000) >> 32;
		s_entries[index].zero = 0;
	}
	
	void IDT::register_interrupt_handler(size_t index, uintptr_t handler)
	{
		register_handler(index, IDT::HandlerType::Present | IDT::HandlerType::InterruptGate, handler);
	}
	
	void IDT::register_trap_handler(size_t index, uintptr_t handler)
	{
		register_handler(index, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, handler);
	}
	
	extern "C"
	{
	void c_interrupt_handler_0()
	{
		PIC::send_end_of_interrupt(0);
	}
	
	void c_interrupt_handler_1()
	{
		PIC::send_end_of_interrupt(1);
	}
	
	void c_interrupt_handler_2()
	{
		PIC::send_end_of_interrupt(2);
	}
	
	void c_interrupt_handler_3()
	{
		PIC::send_end_of_interrupt(3);
	}
	
	void c_interrupt_handler_4()
	{
		PIC::send_end_of_interrupt(4);
	}
	
	void c_interrupt_handler_5()
	{
		PIC::send_end_of_interrupt(5);
	}
	
	void c_interrupt_handler_6()
	{
		PIC::send_end_of_interrupt(6);
	}
	
	void c_interrupt_handler_7()
	{
		PIC::send_end_of_interrupt(7);
	}
	
	void c_interrupt_handler_8()
	{
		PIC::send_end_of_interrupt(8);
	}
	
	void c_interrupt_handler_9()
	{
		PIC::send_end_of_interrupt(9);
	}
	
	void c_interrupt_handler_10()
	{
		PIC::send_end_of_interrupt(10);
	}
	
	void c_interrupt_handler_11()
	{
		PIC::send_end_of_interrupt(11);
	}
	
	void c_interrupt_handler_12()
	{
		PIC::send_end_of_interrupt(12);
	}
	
	void c_interrupt_handler_13()
	{
		PIC::send_end_of_interrupt(13);
	}
	
	void c_interrupt_handler_14()
	{
		PIC::send_end_of_interrupt(14);
	}
	
	void c_interrupt_handler_15()
	{
		PIC::send_end_of_interrupt(15);
	}
	
	__attribute__((noreturn)) void c_exception_handler_0()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_1()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_2()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_3()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_4()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_5()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_6()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_7()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_8()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_10()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_11()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_12()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_13()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_14()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_16()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_17()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_18()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_19()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_20()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	
	__attribute__((noreturn)) void c_exception_handler_30()
	{
		for (;;)
		{
			asm volatile ("cli");
			asm volatile ("hlt");
		}
	}
	}
}
