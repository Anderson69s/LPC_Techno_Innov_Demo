/************************************************************************
 * lib/font.c
 *
 * Copyright (C) Lisa Milne 2014 <lisa@ltmnet.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 ************************************************************************/

/*
 * The font has been found on opengameart.org:
 * http://opengameart.org/content/8x8-ascii-bitmap-font-with-c-source
 */

#include <stdint.h>
#include "lib/font.h"

/*
 * The values in this array are a 8x8 bitmap font for ascii characters
 * As memory is a very precious ressource on a micro-controller all chars
 * before "space" (0x20) have been removed.
 */
uint8_t first_font_char = 0x20;
uint64_t font[NB_FONT_TILES] = {
	0x0000000000000000, /* (space) */  /* 0x20 */
	0x0808080800080000, /* ! */
	0x2828000000000000, /* " */
	0x00287C287C280000, /* # */
	0x081E281C0A3C0800, /* $ */
	0x6094681629060000, /* % */
	0x1C20201926190000, /* & */
	0x0808000000000000, /* ' */
	0x0810202010080000, /* ( */
	0x1008040408100000, /* ) */
	0x2A1C3E1C2A000000, /* * */
	0x0008083E08080000, /* + */
	0x0000000000081000, /* , */
	0x0000003C00000000, /* - */
	0x0000000000080000, /* . */
	0x0204081020400000, /* / */
	0x1824424224180000, /* 0 */ /*x30 */
	0x08180808081C0000, /* 1 */
	0x3C420418207E0000, /* 2 */
	0x3C420418423C0000, /* 3 */
	0x081828487C080000, /* 4 */
	0x7E407C02423C0000, /* 5 */
	0x3C407C42423C0000, /* 6 */
	0x7E04081020400000, /* 7 */
	0x3C423C42423C0000, /* 8 */
	0x3C42423E023C0000, /* 9 */
	0x0000080000080000, /* : */
	0x0000080000081000, /* ; */
	0x0006186018060000, /* < */
	0x00007E007E000000, /* = */
	0x0060180618600000, /* > */
	0x3844041800100000, /* ? */
	0x003C449C945C201C, /* @ */ /* 0x40 */
	0x1818243C42420000, /* A */
	0x7844784444780000, /* B */
	0x3844808044380000, /* C */
	0x7844444444780000, /* D */
	0x7C407840407C0000, /* E */
	0x7C40784040400000, /* F */
	0x3844809C44380000, /* G */
	0x42427E4242420000, /* H */
	0x3E080808083E0000, /* I */
	0x1C04040444380000, /* J */
	0x4448507048440000, /* K */
	0x40404040407E0000, /* L */
	0x4163554941410000, /* M */
	0x4262524A46420000, /* N */
	0x1C222222221C0000, /* O */
	0x7844784040400000, /* P */ /* 0x50 */
	0x1C222222221C0200, /* Q */
	0x7844785048440000, /* R */
	0x1C22100C221C0000, /* S */
	0x7F08080808080000, /* T */
	0x42424242423C0000, /* U */
	0x8142422424180000, /* V */
	0x4141495563410000, /* W */
	0x4224181824420000, /* X */
	0x4122140808080000, /* Y */
	0x7E040810207E0000, /* Z */
	0x3820202020380000, /* [ */
	0x4020100804020000, /* \ */
	0x3808080808380000, /* ] */
	0x1028000000000000, /* ^ */
	0x00000000007E0000, /* _ */
	0x1008000000000000, /* ` */ /* 0x60 */
	0x003C023E463A0000, /* a */
	0x40407C42625C0000, /* b */
	0x00001C20201C0000, /* c */
	0x02023E42463A0000, /* d */
	0x003C427E403C0000, /* e */
	0x0018103810100000, /* f */
	0x0000344C44340438, /* g */
	0x2020382424240000, /* h */
	0x0800080808080000, /* i */
	0x0800180808080870, /* j */
	0x20202428302C0000, /* k */
	0x1010101010180000, /* l */
	0x0000665A42420000, /* m */
	0x00002E3222220000, /* n */
	0x00003C42423C0000, /* o */
	0x00005C62427C4040, /* p */ /* 0x70 */
	0x00003A46423E0202, /* q */
	0x00002C3220200000, /* r */
	0x001C201804380000, /* s */
	0x00103C1010180000, /* t */
	0x00002222261A0000, /* u */
	0x0000424224180000, /* v */
	0x000081815A660000, /* w */
	0x0000422418660000, /* x */
	0x0000422214081060, /* y */
	0x00003C08103C0000, /* z */
	0x1C103030101C0000, /* { */
	0x0808080808080800, /* | */
	0x38080C0C08380000, /* } */
	0x000000324C000000, /* ~ */
};

