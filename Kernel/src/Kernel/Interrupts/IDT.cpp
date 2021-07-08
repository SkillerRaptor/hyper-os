/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <Kernel/Common/Logger.hpp>
#include <Kernel/Interrupts/APIC.hpp>
#include <Kernel/Interrupts/IDT.hpp>
#include <Kernel/Interrupts/PIC.hpp>
#include <Kernel/System/GDT.hpp>

namespace Kernel
{
	IDT::Entry IDT::s_entries[256] = {};

	extern "C"
	{
		uintptr_t idt_handlers[256] = { 0 };
	}

	void IDT::initialize()
	{
		Logger::info("IDT: Initializing...");

		IDT::register_handler(0, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_0);
		IDT::register_handler(1, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_1);
		IDT::register_handler(2, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_2);
		IDT::register_handler(3, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_3);
		IDT::register_handler(4, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_4);
		IDT::register_handler(5, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_5);
		IDT::register_handler(6, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_6);
		IDT::register_handler(7, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_7);
		IDT::register_handler(8, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_8);
		IDT::register_handler(9, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_9);
		IDT::register_handler(10, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_10);
		IDT::register_handler(11, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_11);
		IDT::register_handler(12, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_12);
		IDT::register_handler(13, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_13);
		IDT::register_handler(14, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_14);
		IDT::register_handler(15, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_15);
		IDT::register_handler(16, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_16);
		IDT::register_handler(17, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_17);
		IDT::register_handler(18, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_18);
		IDT::register_handler(19, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_19);
		IDT::register_handler(20, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_20);
		IDT::register_handler(21, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_21);
		IDT::register_handler(22, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_22);
		IDT::register_handler(23, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_23);
		IDT::register_handler(24, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_24);
		IDT::register_handler(25, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_25);
		IDT::register_handler(26, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_26);
		IDT::register_handler(27, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_27);
		IDT::register_handler(28, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_28);
		IDT::register_handler(29, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_29);
		IDT::register_handler(30, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_30);
		IDT::register_handler(31, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_31);
		IDT::register_handler(32, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_32);
		IDT::register_handler(33, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_33);
		IDT::register_handler(34, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_34);
		IDT::register_handler(35, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_35);
		IDT::register_handler(36, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_36);
		IDT::register_handler(37, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_37);
		IDT::register_handler(38, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_38);
		IDT::register_handler(39, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_39);
		IDT::register_handler(40, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_40);
		IDT::register_handler(41, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_41);
		IDT::register_handler(42, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_42);
		IDT::register_handler(43, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_43);
		IDT::register_handler(44, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_44);
		IDT::register_handler(45, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_45);
		IDT::register_handler(46, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_46);
		IDT::register_handler(47, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_47);
		IDT::register_handler(48, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_48);
		IDT::register_handler(49, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_49);
		IDT::register_handler(50, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_50);
		IDT::register_handler(51, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_51);
		IDT::register_handler(52, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_52);
		IDT::register_handler(53, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_53);
		IDT::register_handler(54, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_54);
		IDT::register_handler(55, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_55);
		IDT::register_handler(56, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_56);
		IDT::register_handler(57, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_57);
		IDT::register_handler(58, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_58);
		IDT::register_handler(59, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_59);
		IDT::register_handler(60, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_60);
		IDT::register_handler(61, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_61);
		IDT::register_handler(62, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_62);
		IDT::register_handler(63, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_63);
		IDT::register_handler(64, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_64);
		IDT::register_handler(65, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_65);
		IDT::register_handler(66, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_66);
		IDT::register_handler(67, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_67);
		IDT::register_handler(68, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_68);
		IDT::register_handler(69, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_69);
		IDT::register_handler(70, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_70);
		IDT::register_handler(71, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_71);
		IDT::register_handler(72, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_72);
		IDT::register_handler(73, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_73);
		IDT::register_handler(74, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_74);
		IDT::register_handler(75, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_75);
		IDT::register_handler(76, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_76);
		IDT::register_handler(77, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_77);
		IDT::register_handler(78, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_78);
		IDT::register_handler(79, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_79);
		IDT::register_handler(80, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_80);
		IDT::register_handler(81, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_81);
		IDT::register_handler(82, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_82);
		IDT::register_handler(83, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_83);
		IDT::register_handler(84, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_84);
		IDT::register_handler(85, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_85);
		IDT::register_handler(86, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_86);
		IDT::register_handler(87, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_87);
		IDT::register_handler(88, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_88);
		IDT::register_handler(89, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_89);
		IDT::register_handler(90, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_90);
		IDT::register_handler(91, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_91);
		IDT::register_handler(92, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_92);
		IDT::register_handler(93, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_93);
		IDT::register_handler(94, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_94);
		IDT::register_handler(95, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_95);
		IDT::register_handler(96, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_96);
		IDT::register_handler(97, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_97);
		IDT::register_handler(98, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_98);
		IDT::register_handler(99, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_99);
		IDT::register_handler(100, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_100);
		IDT::register_handler(101, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_101);
		IDT::register_handler(102, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_102);
		IDT::register_handler(103, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_103);
		IDT::register_handler(104, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_104);
		IDT::register_handler(105, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_105);
		IDT::register_handler(106, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_106);
		IDT::register_handler(107, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_107);
		IDT::register_handler(108, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_108);
		IDT::register_handler(109, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_109);
		IDT::register_handler(110, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_110);
		IDT::register_handler(111, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_111);
		IDT::register_handler(112, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_112);
		IDT::register_handler(113, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_113);
		IDT::register_handler(114, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_114);
		IDT::register_handler(115, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_115);
		IDT::register_handler(116, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_116);
		IDT::register_handler(117, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_117);
		IDT::register_handler(118, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_118);
		IDT::register_handler(119, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_119);
		IDT::register_handler(120, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_120);
		IDT::register_handler(121, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_121);
		IDT::register_handler(122, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_122);
		IDT::register_handler(123, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_123);
		IDT::register_handler(124, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_124);
		IDT::register_handler(125, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_125);
		IDT::register_handler(126, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_126);
		IDT::register_handler(127, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_127);
		IDT::register_handler(128, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_128);
		IDT::register_handler(129, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_129);
		IDT::register_handler(130, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_130);
		IDT::register_handler(131, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_131);
		IDT::register_handler(132, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_132);
		IDT::register_handler(133, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_133);
		IDT::register_handler(134, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_134);
		IDT::register_handler(135, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_135);
		IDT::register_handler(136, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_136);
		IDT::register_handler(137, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_137);
		IDT::register_handler(138, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_138);
		IDT::register_handler(139, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_139);
		IDT::register_handler(140, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_140);
		IDT::register_handler(141, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_141);
		IDT::register_handler(142, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_142);
		IDT::register_handler(143, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_143);
		IDT::register_handler(144, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_144);
		IDT::register_handler(145, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_145);
		IDT::register_handler(146, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_146);
		IDT::register_handler(147, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_147);
		IDT::register_handler(148, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_148);
		IDT::register_handler(149, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_149);
		IDT::register_handler(150, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_150);
		IDT::register_handler(151, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_151);
		IDT::register_handler(152, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_152);
		IDT::register_handler(153, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_153);
		IDT::register_handler(154, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_154);
		IDT::register_handler(155, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_155);
		IDT::register_handler(156, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_156);
		IDT::register_handler(157, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_157);
		IDT::register_handler(158, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_158);
		IDT::register_handler(159, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_159);
		IDT::register_handler(160, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_160);
		IDT::register_handler(161, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_161);
		IDT::register_handler(162, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_162);
		IDT::register_handler(163, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_163);
		IDT::register_handler(164, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_164);
		IDT::register_handler(165, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_165);
		IDT::register_handler(166, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_166);
		IDT::register_handler(167, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_167);
		IDT::register_handler(168, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_168);
		IDT::register_handler(169, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_169);
		IDT::register_handler(170, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_170);
		IDT::register_handler(171, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_171);
		IDT::register_handler(172, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_172);
		IDT::register_handler(173, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_173);
		IDT::register_handler(174, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_174);
		IDT::register_handler(175, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_175);
		IDT::register_handler(176, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_176);
		IDT::register_handler(177, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_177);
		IDT::register_handler(178, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_178);
		IDT::register_handler(179, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_179);
		IDT::register_handler(180, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_180);
		IDT::register_handler(181, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_181);
		IDT::register_handler(182, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_182);
		IDT::register_handler(183, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_183);
		IDT::register_handler(184, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_184);
		IDT::register_handler(185, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_185);
		IDT::register_handler(186, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_186);
		IDT::register_handler(187, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_187);
		IDT::register_handler(188, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_188);
		IDT::register_handler(189, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_189);
		IDT::register_handler(190, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_190);
		IDT::register_handler(191, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_191);
		IDT::register_handler(192, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_192);
		IDT::register_handler(193, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_193);
		IDT::register_handler(194, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_194);
		IDT::register_handler(195, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_195);
		IDT::register_handler(196, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_196);
		IDT::register_handler(197, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_197);
		IDT::register_handler(198, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_198);
		IDT::register_handler(199, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_199);
		IDT::register_handler(200, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_200);
		IDT::register_handler(201, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_201);
		IDT::register_handler(202, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_202);
		IDT::register_handler(203, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_203);
		IDT::register_handler(204, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_204);
		IDT::register_handler(205, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_205);
		IDT::register_handler(206, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_206);
		IDT::register_handler(207, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_207);
		IDT::register_handler(208, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_208);
		IDT::register_handler(209, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_209);
		IDT::register_handler(210, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_210);
		IDT::register_handler(211, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_211);
		IDT::register_handler(212, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_212);
		IDT::register_handler(213, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_213);
		IDT::register_handler(214, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_214);
		IDT::register_handler(215, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_215);
		IDT::register_handler(216, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_216);
		IDT::register_handler(217, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_217);
		IDT::register_handler(218, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_218);
		IDT::register_handler(219, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_219);
		IDT::register_handler(220, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_220);
		IDT::register_handler(221, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_221);
		IDT::register_handler(222, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_222);
		IDT::register_handler(223, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_223);
		IDT::register_handler(224, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_224);
		IDT::register_handler(225, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_225);
		IDT::register_handler(226, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_226);
		IDT::register_handler(227, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_227);
		IDT::register_handler(228, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_228);
		IDT::register_handler(229, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_229);
		IDT::register_handler(230, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_230);
		IDT::register_handler(231, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_231);
		IDT::register_handler(232, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_232);
		IDT::register_handler(233, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_233);
		IDT::register_handler(234, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_234);
		IDT::register_handler(235, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_235);
		IDT::register_handler(236, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_236);
		IDT::register_handler(237, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_237);
		IDT::register_handler(238, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_238);
		IDT::register_handler(239, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_239);
		IDT::register_handler(240, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_240);
		IDT::register_handler(241, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_241);
		IDT::register_handler(242, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_242);
		IDT::register_handler(243, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_243);
		IDT::register_handler(244, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_244);
		IDT::register_handler(245, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_245);
		IDT::register_handler(246, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_246);
		IDT::register_handler(247, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_247);
		IDT::register_handler(248, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_248);
		IDT::register_handler(249, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_249);
		IDT::register_handler(250, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_250);
		IDT::register_handler(251, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_251);
		IDT::register_handler(252, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_252);
		IDT::register_handler(253, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_253);
		IDT::register_handler(254, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_254);
		IDT::register_handler(255, IDT::HandlerType::Present | IDT::HandlerType::TrapGate, interrupt_handler_255);

		IDT::install();

		Logger::info("IDT: Initializing finished!");
	}

	void IDT::install()
	{
		IDT::Pointer pointer = { .size = sizeof(s_entries) - 1, .address = reinterpret_cast<uintptr_t>(s_entries) };

		__asm__ __volatile__(
			"lidt %0"
			:
			: "m"(pointer));
	}

	void IDT::default_handler(Registers* registers)
	{
		Logger::error("IDT: Unhandled interrupt %u | rip = %16X", registers->isr, registers->rip);

		Logger::error(
			"Register dump:\n"
			"          rax=0x%16X rbx=0x%16X rcx=0x%16X rdx=0x%16X\n"
			"          rsi=0x%16X rdi=0x%16X rbp=0x%16X rsp=0x%16X\n"
			"           r8=0x%16X  r9=0x%16X r10=0x%16X r11=0x%16X\n"
			"          r12=0x%16X r13=0x%16X r14=0x%16X r15=0x%16X\n"
			"          rip=0x%16X  cs=0x%16X  ss=0x%16X flg=0x%16X",
			registers->rax,
			registers->rbx,
			registers->rcx,
			registers->rdx,
			registers->rsi,
			registers->rdi,
			registers->rbp,
			registers->rsp,
			registers->r8,
			registers->r9,
			registers->r10,
			registers->r11,
			registers->r12,
			registers->r13,
			registers->r14,
			registers->r15,
			registers->rip,
			registers->cs,
			registers->ss,
			registers->flags);

		APIC::lapic_end_of_interrupt();

		while (true)
		{
			__asm__ __volatile__("cli");
			__asm__ __volatile__("hlt");
		}
	}

	void IDT::set_handler(uint8_t index, uint8_t flags, void (*handler)(Registers*))
	{
		s_entries[index].attributes = flags;
		idt_handlers[index] = reinterpret_cast<uintptr_t>(handler);
	}

	void IDT::register_handler(uint8_t index, uint8_t flags, void (*handler)())
	{
		auto handler_address = reinterpret_cast<uintptr_t>(handler);

		s_entries[index].offset_low = (handler_address & 0x0000FFFF) >> 0;
		s_entries[index].selector = GDT::s_kernel_code_selector;
		s_entries[index].ist = 0x00;
		s_entries[index].attributes = flags;
		s_entries[index].offset_middle = (handler_address & 0xFFFF0000) >> 16;
		s_entries[index].offset_high = (handler_address & 0xFFFFFFFF00000000) >> 32;
		s_entries[index].zero = 0;

		idt_handlers[index] = reinterpret_cast<uintptr_t>(default_handler);
	}
} // namespace Kernel
