/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <Kernel/Common/Registers.hpp>
#include <stdint.h>
#include <stddef.h>

namespace Kernel
{
	class IDT
	{
	public:
		enum HandlerType : uint8_t
		{
			Present = 1 << 7,
			InterruptGate = 1 << 1 | 1 << 2 | 1 << 3,
			TrapGate = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3
		};
		
	private:
		struct Entry
		{
			uint16_t offset_low;
			uint16_t selector;
			uint8_t ist;
			uint8_t attributes;
			uint16_t offset_middle;
			uint32_t offset_high;
			uint32_t zero;
		} __attribute__((packed));

		struct Pointer
		{
			uint16_t size;
			uint64_t address;
		} __attribute__((packed));

	public:
		static void initialize();
		static void install();

		static void set_handler(uint8_t index, uint8_t flags, void (*handler)(Registers*));
		static void register_handler(uint8_t index, uint8_t flags, void (*handler)());

	private:
		__attribute__((noreturn)) static void default_handler(Registers* registers);

	private:
		static Entry s_entries[256];
	};

	extern "C"
	{
		extern void interrupt_handler_0();
		extern void interrupt_handler_1();
		extern void interrupt_handler_2();
		extern void interrupt_handler_3();
		extern void interrupt_handler_4();
		extern void interrupt_handler_5();
		extern void interrupt_handler_6();
		extern void interrupt_handler_7();
		extern void interrupt_handler_8();
		extern void interrupt_handler_9();
		extern void interrupt_handler_10();
		extern void interrupt_handler_11();
		extern void interrupt_handler_12();
		extern void interrupt_handler_13();
		extern void interrupt_handler_14();
		extern void interrupt_handler_15();
		extern void interrupt_handler_16();
		extern void interrupt_handler_17();
		extern void interrupt_handler_18();
		extern void interrupt_handler_19();
		extern void interrupt_handler_20();
		extern void interrupt_handler_21();
		extern void interrupt_handler_22();
		extern void interrupt_handler_23();
		extern void interrupt_handler_24();
		extern void interrupt_handler_25();
		extern void interrupt_handler_26();
		extern void interrupt_handler_27();
		extern void interrupt_handler_28();
		extern void interrupt_handler_29();
		extern void interrupt_handler_30();
		extern void interrupt_handler_31();
		extern void interrupt_handler_32();
		extern void interrupt_handler_33();
		extern void interrupt_handler_34();
		extern void interrupt_handler_35();
		extern void interrupt_handler_36();
		extern void interrupt_handler_37();
		extern void interrupt_handler_38();
		extern void interrupt_handler_39();
		extern void interrupt_handler_40();
		extern void interrupt_handler_41();
		extern void interrupt_handler_42();
		extern void interrupt_handler_43();
		extern void interrupt_handler_44();
		extern void interrupt_handler_45();
		extern void interrupt_handler_46();
		extern void interrupt_handler_47();
		extern void interrupt_handler_48();
		extern void interrupt_handler_49();
		extern void interrupt_handler_50();
		extern void interrupt_handler_51();
		extern void interrupt_handler_52();
		extern void interrupt_handler_53();
		extern void interrupt_handler_54();
		extern void interrupt_handler_55();
		extern void interrupt_handler_56();
		extern void interrupt_handler_57();
		extern void interrupt_handler_58();
		extern void interrupt_handler_59();
		extern void interrupt_handler_60();
		extern void interrupt_handler_61();
		extern void interrupt_handler_62();
		extern void interrupt_handler_63();
		extern void interrupt_handler_64();
		extern void interrupt_handler_65();
		extern void interrupt_handler_66();
		extern void interrupt_handler_67();
		extern void interrupt_handler_68();
		extern void interrupt_handler_69();
		extern void interrupt_handler_70();
		extern void interrupt_handler_71();
		extern void interrupt_handler_72();
		extern void interrupt_handler_73();
		extern void interrupt_handler_74();
		extern void interrupt_handler_75();
		extern void interrupt_handler_76();
		extern void interrupt_handler_77();
		extern void interrupt_handler_78();
		extern void interrupt_handler_79();
		extern void interrupt_handler_80();
		extern void interrupt_handler_81();
		extern void interrupt_handler_82();
		extern void interrupt_handler_83();
		extern void interrupt_handler_84();
		extern void interrupt_handler_85();
		extern void interrupt_handler_86();
		extern void interrupt_handler_87();
		extern void interrupt_handler_88();
		extern void interrupt_handler_89();
		extern void interrupt_handler_90();
		extern void interrupt_handler_91();
		extern void interrupt_handler_92();
		extern void interrupt_handler_93();
		extern void interrupt_handler_94();
		extern void interrupt_handler_95();
		extern void interrupt_handler_96();
		extern void interrupt_handler_97();
		extern void interrupt_handler_98();
		extern void interrupt_handler_99();
		extern void interrupt_handler_100();
		extern void interrupt_handler_101();
		extern void interrupt_handler_102();
		extern void interrupt_handler_103();
		extern void interrupt_handler_104();
		extern void interrupt_handler_105();
		extern void interrupt_handler_106();
		extern void interrupt_handler_107();
		extern void interrupt_handler_108();
		extern void interrupt_handler_109();
		extern void interrupt_handler_110();
		extern void interrupt_handler_111();
		extern void interrupt_handler_112();
		extern void interrupt_handler_113();
		extern void interrupt_handler_114();
		extern void interrupt_handler_115();
		extern void interrupt_handler_116();
		extern void interrupt_handler_117();
		extern void interrupt_handler_118();
		extern void interrupt_handler_119();
		extern void interrupt_handler_120();
		extern void interrupt_handler_121();
		extern void interrupt_handler_122();
		extern void interrupt_handler_123();
		extern void interrupt_handler_124();
		extern void interrupt_handler_125();
		extern void interrupt_handler_126();
		extern void interrupt_handler_127();
		extern void interrupt_handler_128();
		extern void interrupt_handler_129();
		extern void interrupt_handler_130();
		extern void interrupt_handler_131();
		extern void interrupt_handler_132();
		extern void interrupt_handler_133();
		extern void interrupt_handler_134();
		extern void interrupt_handler_135();
		extern void interrupt_handler_136();
		extern void interrupt_handler_137();
		extern void interrupt_handler_138();
		extern void interrupt_handler_139();
		extern void interrupt_handler_140();
		extern void interrupt_handler_141();
		extern void interrupt_handler_142();
		extern void interrupt_handler_143();
		extern void interrupt_handler_144();
		extern void interrupt_handler_145();
		extern void interrupt_handler_146();
		extern void interrupt_handler_147();
		extern void interrupt_handler_148();
		extern void interrupt_handler_149();
		extern void interrupt_handler_150();
		extern void interrupt_handler_151();
		extern void interrupt_handler_152();
		extern void interrupt_handler_153();
		extern void interrupt_handler_154();
		extern void interrupt_handler_155();
		extern void interrupt_handler_156();
		extern void interrupt_handler_157();
		extern void interrupt_handler_158();
		extern void interrupt_handler_159();
		extern void interrupt_handler_160();
		extern void interrupt_handler_161();
		extern void interrupt_handler_162();
		extern void interrupt_handler_163();
		extern void interrupt_handler_164();
		extern void interrupt_handler_165();
		extern void interrupt_handler_166();
		extern void interrupt_handler_167();
		extern void interrupt_handler_168();
		extern void interrupt_handler_169();
		extern void interrupt_handler_170();
		extern void interrupt_handler_171();
		extern void interrupt_handler_172();
		extern void interrupt_handler_173();
		extern void interrupt_handler_174();
		extern void interrupt_handler_175();
		extern void interrupt_handler_176();
		extern void interrupt_handler_177();
		extern void interrupt_handler_178();
		extern void interrupt_handler_179();
		extern void interrupt_handler_180();
		extern void interrupt_handler_181();
		extern void interrupt_handler_182();
		extern void interrupt_handler_183();
		extern void interrupt_handler_184();
		extern void interrupt_handler_185();
		extern void interrupt_handler_186();
		extern void interrupt_handler_187();
		extern void interrupt_handler_188();
		extern void interrupt_handler_189();
		extern void interrupt_handler_190();
		extern void interrupt_handler_191();
		extern void interrupt_handler_192();
		extern void interrupt_handler_193();
		extern void interrupt_handler_194();
		extern void interrupt_handler_195();
		extern void interrupt_handler_196();
		extern void interrupt_handler_197();
		extern void interrupt_handler_198();
		extern void interrupt_handler_199();
		extern void interrupt_handler_200();
		extern void interrupt_handler_201();
		extern void interrupt_handler_202();
		extern void interrupt_handler_203();
		extern void interrupt_handler_204();
		extern void interrupt_handler_205();
		extern void interrupt_handler_206();
		extern void interrupt_handler_207();
		extern void interrupt_handler_208();
		extern void interrupt_handler_209();
		extern void interrupt_handler_210();
		extern void interrupt_handler_211();
		extern void interrupt_handler_212();
		extern void interrupt_handler_213();
		extern void interrupt_handler_214();
		extern void interrupt_handler_215();
		extern void interrupt_handler_216();
		extern void interrupt_handler_217();
		extern void interrupt_handler_218();
		extern void interrupt_handler_219();
		extern void interrupt_handler_220();
		extern void interrupt_handler_221();
		extern void interrupt_handler_222();
		extern void interrupt_handler_223();
		extern void interrupt_handler_224();
		extern void interrupt_handler_225();
		extern void interrupt_handler_226();
		extern void interrupt_handler_227();
		extern void interrupt_handler_228();
		extern void interrupt_handler_229();
		extern void interrupt_handler_230();
		extern void interrupt_handler_231();
		extern void interrupt_handler_232();
		extern void interrupt_handler_233();
		extern void interrupt_handler_234();
		extern void interrupt_handler_235();
		extern void interrupt_handler_236();
		extern void interrupt_handler_237();
		extern void interrupt_handler_238();
		extern void interrupt_handler_239();
		extern void interrupt_handler_240();
		extern void interrupt_handler_241();
		extern void interrupt_handler_242();
		extern void interrupt_handler_243();
		extern void interrupt_handler_244();
		extern void interrupt_handler_245();
		extern void interrupt_handler_246();
		extern void interrupt_handler_247();
		extern void interrupt_handler_248();
		extern void interrupt_handler_249();
		extern void interrupt_handler_250();
		extern void interrupt_handler_251();
		extern void interrupt_handler_252();
		extern void interrupt_handler_253();
		extern void interrupt_handler_254();
		extern void interrupt_handler_255();
	}
} // namespace Kernel
