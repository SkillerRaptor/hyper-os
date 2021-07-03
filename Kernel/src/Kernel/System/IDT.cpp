/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/System/GDT.hpp>
#include <Kernel/System/IDT.hpp>
#include <Kernel/System/PIC.hpp>

namespace Kernel
{
	IDT::Entry IDT::s_entries[256]{};
	
	extern "C"
	{
		uintptr_t idt_handlers[256]{ 0 };
	}

	void IDT::initialize()
	{
		Logger::info("IDT: Initializing...");

		IDT::register_trap_handler(0, reinterpret_cast<uintptr_t>(interrupt_handler_0));
		IDT::register_trap_handler(1, reinterpret_cast<uintptr_t>(interrupt_handler_1));
		IDT::register_trap_handler(2, reinterpret_cast<uintptr_t>(interrupt_handler_2));
		IDT::register_trap_handler(3, reinterpret_cast<uintptr_t>(interrupt_handler_3));
		IDT::register_trap_handler(4, reinterpret_cast<uintptr_t>(interrupt_handler_4));
		IDT::register_trap_handler(5, reinterpret_cast<uintptr_t>(interrupt_handler_5));
		IDT::register_trap_handler(6, reinterpret_cast<uintptr_t>(interrupt_handler_6));
		IDT::register_trap_handler(7, reinterpret_cast<uintptr_t>(interrupt_handler_7));
		IDT::register_trap_handler(8, reinterpret_cast<uintptr_t>(interrupt_handler_8));
		IDT::register_trap_handler(9, reinterpret_cast<uintptr_t>(interrupt_handler_9));
		IDT::register_trap_handler(10, reinterpret_cast<uintptr_t>(interrupt_handler_10));
		IDT::register_trap_handler(11, reinterpret_cast<uintptr_t>(interrupt_handler_11));
		IDT::register_trap_handler(12, reinterpret_cast<uintptr_t>(interrupt_handler_12));
		IDT::register_trap_handler(13, reinterpret_cast<uintptr_t>(interrupt_handler_13));
		IDT::register_trap_handler(14, reinterpret_cast<uintptr_t>(interrupt_handler_14));
		IDT::register_trap_handler(15, reinterpret_cast<uintptr_t>(interrupt_handler_15));
		IDT::register_trap_handler(16, reinterpret_cast<uintptr_t>(interrupt_handler_16));
		IDT::register_trap_handler(17, reinterpret_cast<uintptr_t>(interrupt_handler_17));
		IDT::register_trap_handler(18, reinterpret_cast<uintptr_t>(interrupt_handler_18));
		IDT::register_trap_handler(19, reinterpret_cast<uintptr_t>(interrupt_handler_19));
		IDT::register_trap_handler(20, reinterpret_cast<uintptr_t>(interrupt_handler_20));
		IDT::register_trap_handler(21, reinterpret_cast<uintptr_t>(interrupt_handler_21));
		IDT::register_trap_handler(22, reinterpret_cast<uintptr_t>(interrupt_handler_22));
		IDT::register_trap_handler(23, reinterpret_cast<uintptr_t>(interrupt_handler_23));
		IDT::register_trap_handler(24, reinterpret_cast<uintptr_t>(interrupt_handler_24));
		IDT::register_trap_handler(25, reinterpret_cast<uintptr_t>(interrupt_handler_25));
		IDT::register_trap_handler(26, reinterpret_cast<uintptr_t>(interrupt_handler_26));
		IDT::register_trap_handler(27, reinterpret_cast<uintptr_t>(interrupt_handler_27));
		IDT::register_trap_handler(28, reinterpret_cast<uintptr_t>(interrupt_handler_28));
		IDT::register_trap_handler(29, reinterpret_cast<uintptr_t>(interrupt_handler_29));
		IDT::register_trap_handler(30, reinterpret_cast<uintptr_t>(interrupt_handler_30));
		IDT::register_trap_handler(31, reinterpret_cast<uintptr_t>(interrupt_handler_31));
		IDT::register_trap_handler(32, reinterpret_cast<uintptr_t>(interrupt_handler_32));
		IDT::register_trap_handler(33, reinterpret_cast<uintptr_t>(interrupt_handler_33));
		IDT::register_trap_handler(34, reinterpret_cast<uintptr_t>(interrupt_handler_34));
		IDT::register_trap_handler(35, reinterpret_cast<uintptr_t>(interrupt_handler_35));
		IDT::register_trap_handler(36, reinterpret_cast<uintptr_t>(interrupt_handler_36));
		IDT::register_trap_handler(37, reinterpret_cast<uintptr_t>(interrupt_handler_37));
		IDT::register_trap_handler(38, reinterpret_cast<uintptr_t>(interrupt_handler_38));
		IDT::register_trap_handler(39, reinterpret_cast<uintptr_t>(interrupt_handler_39));
		IDT::register_trap_handler(40, reinterpret_cast<uintptr_t>(interrupt_handler_40));
		IDT::register_trap_handler(41, reinterpret_cast<uintptr_t>(interrupt_handler_41));
		IDT::register_trap_handler(42, reinterpret_cast<uintptr_t>(interrupt_handler_42));
		IDT::register_trap_handler(43, reinterpret_cast<uintptr_t>(interrupt_handler_43));
		IDT::register_trap_handler(44, reinterpret_cast<uintptr_t>(interrupt_handler_44));
		IDT::register_trap_handler(45, reinterpret_cast<uintptr_t>(interrupt_handler_45));
		IDT::register_trap_handler(46, reinterpret_cast<uintptr_t>(interrupt_handler_46));
		IDT::register_trap_handler(47, reinterpret_cast<uintptr_t>(interrupt_handler_47));
		IDT::register_trap_handler(48, reinterpret_cast<uintptr_t>(interrupt_handler_48));
		IDT::register_trap_handler(49, reinterpret_cast<uintptr_t>(interrupt_handler_49));
		IDT::register_trap_handler(50, reinterpret_cast<uintptr_t>(interrupt_handler_50));
		IDT::register_trap_handler(51, reinterpret_cast<uintptr_t>(interrupt_handler_51));
		IDT::register_trap_handler(52, reinterpret_cast<uintptr_t>(interrupt_handler_52));
		IDT::register_trap_handler(53, reinterpret_cast<uintptr_t>(interrupt_handler_53));
		IDT::register_trap_handler(54, reinterpret_cast<uintptr_t>(interrupt_handler_54));
		IDT::register_trap_handler(55, reinterpret_cast<uintptr_t>(interrupt_handler_55));
		IDT::register_trap_handler(56, reinterpret_cast<uintptr_t>(interrupt_handler_56));
		IDT::register_trap_handler(57, reinterpret_cast<uintptr_t>(interrupt_handler_57));
		IDT::register_trap_handler(58, reinterpret_cast<uintptr_t>(interrupt_handler_58));
		IDT::register_trap_handler(59, reinterpret_cast<uintptr_t>(interrupt_handler_59));
		IDT::register_trap_handler(60, reinterpret_cast<uintptr_t>(interrupt_handler_60));
		IDT::register_trap_handler(61, reinterpret_cast<uintptr_t>(interrupt_handler_61));
		IDT::register_trap_handler(62, reinterpret_cast<uintptr_t>(interrupt_handler_62));
		IDT::register_trap_handler(63, reinterpret_cast<uintptr_t>(interrupt_handler_63));
		IDT::register_trap_handler(64, reinterpret_cast<uintptr_t>(interrupt_handler_64));
		IDT::register_trap_handler(65, reinterpret_cast<uintptr_t>(interrupt_handler_65));
		IDT::register_trap_handler(66, reinterpret_cast<uintptr_t>(interrupt_handler_66));
		IDT::register_trap_handler(67, reinterpret_cast<uintptr_t>(interrupt_handler_67));
		IDT::register_trap_handler(68, reinterpret_cast<uintptr_t>(interrupt_handler_68));
		IDT::register_trap_handler(69, reinterpret_cast<uintptr_t>(interrupt_handler_69));
		IDT::register_trap_handler(70, reinterpret_cast<uintptr_t>(interrupt_handler_70));
		IDT::register_trap_handler(71, reinterpret_cast<uintptr_t>(interrupt_handler_71));
		IDT::register_trap_handler(72, reinterpret_cast<uintptr_t>(interrupt_handler_72));
		IDT::register_trap_handler(73, reinterpret_cast<uintptr_t>(interrupt_handler_73));
		IDT::register_trap_handler(74, reinterpret_cast<uintptr_t>(interrupt_handler_74));
		IDT::register_trap_handler(75, reinterpret_cast<uintptr_t>(interrupt_handler_75));
		IDT::register_trap_handler(76, reinterpret_cast<uintptr_t>(interrupt_handler_76));
		IDT::register_trap_handler(77, reinterpret_cast<uintptr_t>(interrupt_handler_77));
		IDT::register_trap_handler(78, reinterpret_cast<uintptr_t>(interrupt_handler_78));
		IDT::register_trap_handler(79, reinterpret_cast<uintptr_t>(interrupt_handler_79));
		IDT::register_trap_handler(80, reinterpret_cast<uintptr_t>(interrupt_handler_80));
		IDT::register_trap_handler(81, reinterpret_cast<uintptr_t>(interrupt_handler_81));
		IDT::register_trap_handler(82, reinterpret_cast<uintptr_t>(interrupt_handler_82));
		IDT::register_trap_handler(83, reinterpret_cast<uintptr_t>(interrupt_handler_83));
		IDT::register_trap_handler(84, reinterpret_cast<uintptr_t>(interrupt_handler_84));
		IDT::register_trap_handler(85, reinterpret_cast<uintptr_t>(interrupt_handler_85));
		IDT::register_trap_handler(86, reinterpret_cast<uintptr_t>(interrupt_handler_86));
		IDT::register_trap_handler(87, reinterpret_cast<uintptr_t>(interrupt_handler_87));
		IDT::register_trap_handler(88, reinterpret_cast<uintptr_t>(interrupt_handler_88));
		IDT::register_trap_handler(89, reinterpret_cast<uintptr_t>(interrupt_handler_89));
		IDT::register_trap_handler(90, reinterpret_cast<uintptr_t>(interrupt_handler_90));
		IDT::register_trap_handler(91, reinterpret_cast<uintptr_t>(interrupt_handler_91));
		IDT::register_trap_handler(92, reinterpret_cast<uintptr_t>(interrupt_handler_92));
		IDT::register_trap_handler(93, reinterpret_cast<uintptr_t>(interrupt_handler_93));
		IDT::register_trap_handler(94, reinterpret_cast<uintptr_t>(interrupt_handler_94));
		IDT::register_trap_handler(95, reinterpret_cast<uintptr_t>(interrupt_handler_95));
		IDT::register_trap_handler(96, reinterpret_cast<uintptr_t>(interrupt_handler_96));
		IDT::register_trap_handler(97, reinterpret_cast<uintptr_t>(interrupt_handler_97));
		IDT::register_trap_handler(98, reinterpret_cast<uintptr_t>(interrupt_handler_98));
		IDT::register_trap_handler(99, reinterpret_cast<uintptr_t>(interrupt_handler_99));
		IDT::register_trap_handler(100, reinterpret_cast<uintptr_t>(interrupt_handler_100));
		IDT::register_trap_handler(101, reinterpret_cast<uintptr_t>(interrupt_handler_101));
		IDT::register_trap_handler(102, reinterpret_cast<uintptr_t>(interrupt_handler_102));
		IDT::register_trap_handler(103, reinterpret_cast<uintptr_t>(interrupt_handler_103));
		IDT::register_trap_handler(104, reinterpret_cast<uintptr_t>(interrupt_handler_104));
		IDT::register_trap_handler(105, reinterpret_cast<uintptr_t>(interrupt_handler_105));
		IDT::register_trap_handler(106, reinterpret_cast<uintptr_t>(interrupt_handler_106));
		IDT::register_trap_handler(107, reinterpret_cast<uintptr_t>(interrupt_handler_107));
		IDT::register_trap_handler(108, reinterpret_cast<uintptr_t>(interrupt_handler_108));
		IDT::register_trap_handler(109, reinterpret_cast<uintptr_t>(interrupt_handler_109));
		IDT::register_trap_handler(110, reinterpret_cast<uintptr_t>(interrupt_handler_110));
		IDT::register_trap_handler(111, reinterpret_cast<uintptr_t>(interrupt_handler_111));
		IDT::register_trap_handler(112, reinterpret_cast<uintptr_t>(interrupt_handler_112));
		IDT::register_trap_handler(113, reinterpret_cast<uintptr_t>(interrupt_handler_113));
		IDT::register_trap_handler(114, reinterpret_cast<uintptr_t>(interrupt_handler_114));
		IDT::register_trap_handler(115, reinterpret_cast<uintptr_t>(interrupt_handler_115));
		IDT::register_trap_handler(116, reinterpret_cast<uintptr_t>(interrupt_handler_116));
		IDT::register_trap_handler(117, reinterpret_cast<uintptr_t>(interrupt_handler_117));
		IDT::register_trap_handler(118, reinterpret_cast<uintptr_t>(interrupt_handler_118));
		IDT::register_trap_handler(119, reinterpret_cast<uintptr_t>(interrupt_handler_119));
		IDT::register_trap_handler(120, reinterpret_cast<uintptr_t>(interrupt_handler_120));
		IDT::register_trap_handler(121, reinterpret_cast<uintptr_t>(interrupt_handler_121));
		IDT::register_trap_handler(122, reinterpret_cast<uintptr_t>(interrupt_handler_122));
		IDT::register_trap_handler(123, reinterpret_cast<uintptr_t>(interrupt_handler_123));
		IDT::register_trap_handler(124, reinterpret_cast<uintptr_t>(interrupt_handler_124));
		IDT::register_trap_handler(125, reinterpret_cast<uintptr_t>(interrupt_handler_125));
		IDT::register_trap_handler(126, reinterpret_cast<uintptr_t>(interrupt_handler_126));
		IDT::register_trap_handler(127, reinterpret_cast<uintptr_t>(interrupt_handler_127));
		IDT::register_trap_handler(128, reinterpret_cast<uintptr_t>(interrupt_handler_128));
		IDT::register_trap_handler(129, reinterpret_cast<uintptr_t>(interrupt_handler_129));
		IDT::register_trap_handler(130, reinterpret_cast<uintptr_t>(interrupt_handler_130));
		IDT::register_trap_handler(131, reinterpret_cast<uintptr_t>(interrupt_handler_131));
		IDT::register_trap_handler(132, reinterpret_cast<uintptr_t>(interrupt_handler_132));
		IDT::register_trap_handler(133, reinterpret_cast<uintptr_t>(interrupt_handler_133));
		IDT::register_trap_handler(134, reinterpret_cast<uintptr_t>(interrupt_handler_134));
		IDT::register_trap_handler(135, reinterpret_cast<uintptr_t>(interrupt_handler_135));
		IDT::register_trap_handler(136, reinterpret_cast<uintptr_t>(interrupt_handler_136));
		IDT::register_trap_handler(137, reinterpret_cast<uintptr_t>(interrupt_handler_137));
		IDT::register_trap_handler(138, reinterpret_cast<uintptr_t>(interrupt_handler_138));
		IDT::register_trap_handler(139, reinterpret_cast<uintptr_t>(interrupt_handler_139));
		IDT::register_trap_handler(140, reinterpret_cast<uintptr_t>(interrupt_handler_140));
		IDT::register_trap_handler(141, reinterpret_cast<uintptr_t>(interrupt_handler_141));
		IDT::register_trap_handler(142, reinterpret_cast<uintptr_t>(interrupt_handler_142));
		IDT::register_trap_handler(143, reinterpret_cast<uintptr_t>(interrupt_handler_143));
		IDT::register_trap_handler(144, reinterpret_cast<uintptr_t>(interrupt_handler_144));
		IDT::register_trap_handler(145, reinterpret_cast<uintptr_t>(interrupt_handler_145));
		IDT::register_trap_handler(146, reinterpret_cast<uintptr_t>(interrupt_handler_146));
		IDT::register_trap_handler(147, reinterpret_cast<uintptr_t>(interrupt_handler_147));
		IDT::register_trap_handler(148, reinterpret_cast<uintptr_t>(interrupt_handler_148));
		IDT::register_trap_handler(149, reinterpret_cast<uintptr_t>(interrupt_handler_149));
		IDT::register_trap_handler(150, reinterpret_cast<uintptr_t>(interrupt_handler_150));
		IDT::register_trap_handler(151, reinterpret_cast<uintptr_t>(interrupt_handler_151));
		IDT::register_trap_handler(152, reinterpret_cast<uintptr_t>(interrupt_handler_152));
		IDT::register_trap_handler(153, reinterpret_cast<uintptr_t>(interrupt_handler_153));
		IDT::register_trap_handler(154, reinterpret_cast<uintptr_t>(interrupt_handler_154));
		IDT::register_trap_handler(155, reinterpret_cast<uintptr_t>(interrupt_handler_155));
		IDT::register_trap_handler(156, reinterpret_cast<uintptr_t>(interrupt_handler_156));
		IDT::register_trap_handler(157, reinterpret_cast<uintptr_t>(interrupt_handler_157));
		IDT::register_trap_handler(158, reinterpret_cast<uintptr_t>(interrupt_handler_158));
		IDT::register_trap_handler(159, reinterpret_cast<uintptr_t>(interrupt_handler_159));
		IDT::register_trap_handler(160, reinterpret_cast<uintptr_t>(interrupt_handler_160));
		IDT::register_trap_handler(161, reinterpret_cast<uintptr_t>(interrupt_handler_161));
		IDT::register_trap_handler(162, reinterpret_cast<uintptr_t>(interrupt_handler_162));
		IDT::register_trap_handler(163, reinterpret_cast<uintptr_t>(interrupt_handler_163));
		IDT::register_trap_handler(164, reinterpret_cast<uintptr_t>(interrupt_handler_164));
		IDT::register_trap_handler(165, reinterpret_cast<uintptr_t>(interrupt_handler_165));
		IDT::register_trap_handler(166, reinterpret_cast<uintptr_t>(interrupt_handler_166));
		IDT::register_trap_handler(167, reinterpret_cast<uintptr_t>(interrupt_handler_167));
		IDT::register_trap_handler(168, reinterpret_cast<uintptr_t>(interrupt_handler_168));
		IDT::register_trap_handler(169, reinterpret_cast<uintptr_t>(interrupt_handler_169));
		IDT::register_trap_handler(170, reinterpret_cast<uintptr_t>(interrupt_handler_170));
		IDT::register_trap_handler(171, reinterpret_cast<uintptr_t>(interrupt_handler_171));
		IDT::register_trap_handler(172, reinterpret_cast<uintptr_t>(interrupt_handler_172));
		IDT::register_trap_handler(173, reinterpret_cast<uintptr_t>(interrupt_handler_173));
		IDT::register_trap_handler(174, reinterpret_cast<uintptr_t>(interrupt_handler_174));
		IDT::register_trap_handler(175, reinterpret_cast<uintptr_t>(interrupt_handler_175));
		IDT::register_trap_handler(176, reinterpret_cast<uintptr_t>(interrupt_handler_176));
		IDT::register_trap_handler(177, reinterpret_cast<uintptr_t>(interrupt_handler_177));
		IDT::register_trap_handler(178, reinterpret_cast<uintptr_t>(interrupt_handler_178));
		IDT::register_trap_handler(179, reinterpret_cast<uintptr_t>(interrupt_handler_179));
		IDT::register_trap_handler(180, reinterpret_cast<uintptr_t>(interrupt_handler_180));
		IDT::register_trap_handler(181, reinterpret_cast<uintptr_t>(interrupt_handler_181));
		IDT::register_trap_handler(182, reinterpret_cast<uintptr_t>(interrupt_handler_182));
		IDT::register_trap_handler(183, reinterpret_cast<uintptr_t>(interrupt_handler_183));
		IDT::register_trap_handler(184, reinterpret_cast<uintptr_t>(interrupt_handler_184));
		IDT::register_trap_handler(185, reinterpret_cast<uintptr_t>(interrupt_handler_185));
		IDT::register_trap_handler(186, reinterpret_cast<uintptr_t>(interrupt_handler_186));
		IDT::register_trap_handler(187, reinterpret_cast<uintptr_t>(interrupt_handler_187));
		IDT::register_trap_handler(188, reinterpret_cast<uintptr_t>(interrupt_handler_188));
		IDT::register_trap_handler(189, reinterpret_cast<uintptr_t>(interrupt_handler_189));
		IDT::register_trap_handler(190, reinterpret_cast<uintptr_t>(interrupt_handler_190));
		IDT::register_trap_handler(191, reinterpret_cast<uintptr_t>(interrupt_handler_191));
		IDT::register_trap_handler(192, reinterpret_cast<uintptr_t>(interrupt_handler_192));
		IDT::register_trap_handler(193, reinterpret_cast<uintptr_t>(interrupt_handler_193));
		IDT::register_trap_handler(194, reinterpret_cast<uintptr_t>(interrupt_handler_194));
		IDT::register_trap_handler(195, reinterpret_cast<uintptr_t>(interrupt_handler_195));
		IDT::register_trap_handler(196, reinterpret_cast<uintptr_t>(interrupt_handler_196));
		IDT::register_trap_handler(197, reinterpret_cast<uintptr_t>(interrupt_handler_197));
		IDT::register_trap_handler(198, reinterpret_cast<uintptr_t>(interrupt_handler_198));
		IDT::register_trap_handler(199, reinterpret_cast<uintptr_t>(interrupt_handler_199));
		IDT::register_trap_handler(200, reinterpret_cast<uintptr_t>(interrupt_handler_200));
		IDT::register_trap_handler(201, reinterpret_cast<uintptr_t>(interrupt_handler_201));
		IDT::register_trap_handler(202, reinterpret_cast<uintptr_t>(interrupt_handler_202));
		IDT::register_trap_handler(203, reinterpret_cast<uintptr_t>(interrupt_handler_203));
		IDT::register_trap_handler(204, reinterpret_cast<uintptr_t>(interrupt_handler_204));
		IDT::register_trap_handler(205, reinterpret_cast<uintptr_t>(interrupt_handler_205));
		IDT::register_trap_handler(206, reinterpret_cast<uintptr_t>(interrupt_handler_206));
		IDT::register_trap_handler(207, reinterpret_cast<uintptr_t>(interrupt_handler_207));
		IDT::register_trap_handler(208, reinterpret_cast<uintptr_t>(interrupt_handler_208));
		IDT::register_trap_handler(209, reinterpret_cast<uintptr_t>(interrupt_handler_209));
		IDT::register_trap_handler(210, reinterpret_cast<uintptr_t>(interrupt_handler_210));
		IDT::register_trap_handler(211, reinterpret_cast<uintptr_t>(interrupt_handler_211));
		IDT::register_trap_handler(212, reinterpret_cast<uintptr_t>(interrupt_handler_212));
		IDT::register_trap_handler(213, reinterpret_cast<uintptr_t>(interrupt_handler_213));
		IDT::register_trap_handler(214, reinterpret_cast<uintptr_t>(interrupt_handler_214));
		IDT::register_trap_handler(215, reinterpret_cast<uintptr_t>(interrupt_handler_215));
		IDT::register_trap_handler(216, reinterpret_cast<uintptr_t>(interrupt_handler_216));
		IDT::register_trap_handler(217, reinterpret_cast<uintptr_t>(interrupt_handler_217));
		IDT::register_trap_handler(218, reinterpret_cast<uintptr_t>(interrupt_handler_218));
		IDT::register_trap_handler(219, reinterpret_cast<uintptr_t>(interrupt_handler_219));
		IDT::register_trap_handler(220, reinterpret_cast<uintptr_t>(interrupt_handler_220));
		IDT::register_trap_handler(221, reinterpret_cast<uintptr_t>(interrupt_handler_221));
		IDT::register_trap_handler(222, reinterpret_cast<uintptr_t>(interrupt_handler_222));
		IDT::register_trap_handler(223, reinterpret_cast<uintptr_t>(interrupt_handler_223));
		IDT::register_trap_handler(224, reinterpret_cast<uintptr_t>(interrupt_handler_224));
		IDT::register_trap_handler(225, reinterpret_cast<uintptr_t>(interrupt_handler_225));
		IDT::register_trap_handler(226, reinterpret_cast<uintptr_t>(interrupt_handler_226));
		IDT::register_trap_handler(227, reinterpret_cast<uintptr_t>(interrupt_handler_227));
		IDT::register_trap_handler(228, reinterpret_cast<uintptr_t>(interrupt_handler_228));
		IDT::register_trap_handler(229, reinterpret_cast<uintptr_t>(interrupt_handler_229));
		IDT::register_trap_handler(230, reinterpret_cast<uintptr_t>(interrupt_handler_230));
		IDT::register_trap_handler(231, reinterpret_cast<uintptr_t>(interrupt_handler_231));
		IDT::register_trap_handler(232, reinterpret_cast<uintptr_t>(interrupt_handler_232));
		IDT::register_trap_handler(233, reinterpret_cast<uintptr_t>(interrupt_handler_233));
		IDT::register_trap_handler(234, reinterpret_cast<uintptr_t>(interrupt_handler_234));
		IDT::register_trap_handler(235, reinterpret_cast<uintptr_t>(interrupt_handler_235));
		IDT::register_trap_handler(236, reinterpret_cast<uintptr_t>(interrupt_handler_236));
		IDT::register_trap_handler(237, reinterpret_cast<uintptr_t>(interrupt_handler_237));
		IDT::register_trap_handler(238, reinterpret_cast<uintptr_t>(interrupt_handler_238));
		IDT::register_trap_handler(239, reinterpret_cast<uintptr_t>(interrupt_handler_239));
		IDT::register_trap_handler(240, reinterpret_cast<uintptr_t>(interrupt_handler_240));
		IDT::register_trap_handler(241, reinterpret_cast<uintptr_t>(interrupt_handler_241));
		IDT::register_trap_handler(242, reinterpret_cast<uintptr_t>(interrupt_handler_242));
		IDT::register_trap_handler(243, reinterpret_cast<uintptr_t>(interrupt_handler_243));
		IDT::register_trap_handler(244, reinterpret_cast<uintptr_t>(interrupt_handler_244));
		IDT::register_trap_handler(245, reinterpret_cast<uintptr_t>(interrupt_handler_245));
		IDT::register_trap_handler(246, reinterpret_cast<uintptr_t>(interrupt_handler_246));
		IDT::register_trap_handler(247, reinterpret_cast<uintptr_t>(interrupt_handler_247));
		IDT::register_trap_handler(248, reinterpret_cast<uintptr_t>(interrupt_handler_248));
		IDT::register_trap_handler(249, reinterpret_cast<uintptr_t>(interrupt_handler_249));
		IDT::register_trap_handler(250, reinterpret_cast<uintptr_t>(interrupt_handler_250));
		IDT::register_trap_handler(251, reinterpret_cast<uintptr_t>(interrupt_handler_251));
		IDT::register_trap_handler(252, reinterpret_cast<uintptr_t>(interrupt_handler_252));
		IDT::register_trap_handler(253, reinterpret_cast<uintptr_t>(interrupt_handler_253));
		IDT::register_trap_handler(254, reinterpret_cast<uintptr_t>(interrupt_handler_254));
		IDT::register_trap_handler(255, reinterpret_cast<uintptr_t>(interrupt_handler_255));

		IDT::install();

		Logger::info("IDT: Initializing finished!");
	}

	void IDT::install()
	{
		IDT::Pointer pointer =
			{
				.size = sizeof(s_entries) - 1,
				.address = reinterpret_cast<uintptr_t>(s_entries)
			};

		__asm__ __volatile__(
			"lidt %0"
			:
			: "m"(pointer)
		);
	}
	
	void IDT::default_handler(Registers* registers)
	{
		Logger::error("IDT: Unhandled interrupt %u", registers->vector);
		
		while (true)
		{
			__asm__ __volatile__("cli");
			__asm__ __volatile__("hlt");
		}
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
		
		idt_handlers[index] = reinterpret_cast<uintptr_t>(default_handler);
	}

	void IDT::register_interrupt_handler(size_t index, uintptr_t handler)
	{
		register_handler(index, IDT::HandlerType::Present | IDT::HandlerType::InterruptGate, handler);
	}

	void IDT::register_trap_handler(size_t index, uintptr_t handler)
	{
		register_handler(index, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, handler);
	}
} // namespace Kernel
