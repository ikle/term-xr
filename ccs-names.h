/*
 * Coded Character Set Names
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35, ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_NAMES_H
#define CCS_NAMES_H  1

/* ECMA-35 6.2 Fixed coded characters */

#define CCS_DEL		0x7f
#define CCS_SP		0x20

/* ECMA-35 13.2 Types of escape sequences */

#define CCS_TYPE_ACS	0x20	/* Announce Code Structure		*/
#define CCS_TYPE_CZD	0x21	/* C0-designate				*/
#define CCS_TYPE_C1D	0x22	/* C1-designate				*/
#define CCS_TYPE_3FP	0x23	/* single control function		*/
#define CCS_TYPE_GDM	0x24	/* designation of miltiple-byte charsets */
#define CCS_TYPE_DOCS	0x25	/* Designate Other Coding System	*/
#define CCS_TYPE_IRR	0x26	/* Identity Revised Registration	*/
#define CCS_TYPE_GZD4	0x28	/* G0-designate 94-set			*/
#define CCS_TYPE_G1D4	0x29	/* G1-designate 94-set			*/
#define CCS_TYPE_G2D4	0x2a	/* G2-designate 94-set			*/
#define CCS_TYPE_G3D4	0x2b	/* G3-designate 94-set			*/
#define CCS_TYPE_G1D6	0x2d	/* G1-designate 96-set			*/
#define CCS_TYPE_G2D6	0x2e	/* G2-designate 96-set			*/
#define CCS_TYPE_G3D6	0x2f	/* G3-designate 96-set			*/

#define CCS_TYPE_FP	0x30	/* private control function		*/
#define CCS_TYPE_FE	0x40	/* control function in C1 set		*/
#define CCS_TYPE_FS	0x60	/* standardized control function	*/

/* ECMA-48 5.2 Elements of C0 set */

#define CCS_NUL		0x00
#define CCS_SOH		0x01
#define CCS_STX		0x02
#define CCS_ETX		0x03
#define CCS_EOT		0x04
#define CCS_ENQ		0x05
#define CCS_ACK		0x06
#define CCS_BEL		0x07
#define CCS_BS		0x08
#define CCS_HT		0x09
#define CCS_LF		0x0a
#define CCS_VT		0x0b
#define CCS_FF		0x0c
#define CCS_CR		0x0d
#define CCS_SO		0x0e	/* ECMA-35 7.3 */
#define CCS_SI		0x0f	/* ECMA-35 7.3 */

#define CCS_LS0		CCS_SI	/* ECMA-35 7.3 */
#define CCS_LS1		CCS_SO	/* ECMA-35 7.3 */

#define CCS_DLE		0x10
#define CCS_DC1		0x11
#define CCS_DC2		0x12
#define CCS_DC3		0x13
#define CCS_DC4		0x14
#define CCS_NAK		0x15
#define CCS_SYN		0x16
#define CCS_ETB		0x17
#define CCS_CAN		0x18
#define CCS_EM		0x19
#define CCS_SUB		0x1a
#define CCS_ESC		0x1b	/* ECMA-35 6.2 */
#define CCS_IS4		0x1c
#define CCS_IS3		0x1d
#define CCS_IS2		0x1e
#define CCS_IS1		0x1f

/* ECMA-48 8.2.10 Information separators */

#define CCS_FS		CCS_IS4
#define CCS_GS		CCS_IS3
#define CCS_RS		CCS_IS2
#define CCS_US		CCS_IS1

/* ECMA-48 8.3.28 DC1, 8.3.30 DC3 */

#define CCS_XON		CCS_DC1
#define CCS_XOFF	CCS_DC3

/* ECMA-48 5.3 Elements of C1 set */

#define CCS_PAD		0x80	/* ISO 2022 padding character		*/
#define CCS_HOP		0x81	/* RFC 1342, high octet present		*/
#define CCS_BPH		0x82
#define CCS_NBH		0x83
#define CCS_IND		0x84	/* index, deprecated, f.8.2	*/
#define CCS_NEL		0x85
#define CCS_SSA		0x86	/* start of selected area, 6.5.1	*/
#define CCS_ESA		0x87	/* end of selected area, 6.5.1		*/
#define CCS_HTS		0x88	/* character tabulation set, 6.7	*/
#define CCS_HTJ		0x89
#define CCS_VTS		0x8a	/* line tabulation set, 6.7		*/
#define CCS_PLD		0x8b	/* partial line forward,  8.3.92	*/
#define CCS_PLU		0x8c	/* partial line backward, 8.3.93	*/
#define CCS_RI		0x8d
#define CCS_SS2		0x8e	/* ECMA-35 7.3 */
#define CCS_SS3		0x8f	/* ECMA-35 7.3 */

#define CCS_DCS		0x90	/* device control string, 5.6		*/
#define CCS_PU1		0x91
#define CCS_PU2		0x92
#define CCS_STS		0x93
#define CCS_CCH		0x94	/* cancel character, 8.3.8		*/
#define CCS_MW		0x95
#define CCS_SPA		0x96	/* start of guarded area, 6.5.2.2	*/
#define CCS_EPA		0x97	/* end of guarded area, 6.5.2.2		*/
#define CCS_SOS		0x98	/* start of string, 5.6			*/
#define CCS_SGCI	0x99	/* RFC 1345 single graphic char introd.	*/
#define CCS_SCI		0x9a
#define CCS_CSI		0x9b	/* control sequence introducer, 5.4	*/
#define CCS_ST		0x9c	/* string terminator, 5.6		*/
#define CCS_OSC		0x9d	/* operating system command, 5.6	*/
#define CCS_PM		0x9e	/* privacy message, 5.6			*/
#define CCS_APC		0x9f	/* application program command, 5.6	*/

/* ECMA-48 5.4 Control sequences, Table 3, CSI F without I */

#define CCS_ICH		0x40
#define CCS_CUU		0x41
#define CCS_CUD		0x42
#define CCS_CUF		0x43
#define CCS_CUB		0x44
#define CCS_CNL		0x45
#define CCS_CPL		0x46
#define CCS_CHA		0x47
#define CCS_CUP		0x48
#define CCS_CHT		0x49	/* cursor forward tabulation, 8.3.10	*/
#define CCS_ED		0x4a
#define CCS_EL		0x4b
#define CCS_IL		0x4c
#define CCS_DL		0x4d
#define CCS_EF		0x4e
#define CCS_EA		0x4f

#define CCS_DCH		0x50
#define CCS_SSE		0x51
#define CCS_CPR		0x52
#define CCS_SU		0x53	/* scroll up,   8.3.147	*/
#define CCS_SD		0x54	/* scroll down, 8.3.113	*/
#define CCS_NP		0x55
#define CCS_PP		0x56
#define CCS_CTC		0x57	/* cursor tabulation control, 6.7	*/
#define CCS_ECH		0x58
#define CCS_CVT		0x59	/* cursor line tabulation, 8.3.23	*/
#define CCS_CBT		0x5a	/* cursor backward tabulation, 8.3.7	*/
#define CCS_SRS		0x5b
#define CCS_PTX		0x5c
#define CCS_SDS		0x5d
#define CCS_SIMD	0x5e

#define CCS_HPA		0x60	/* character position absolute, 8.3.57	*/
#define CCS_HPR		0x61	/* character position forward, 8.3.59	*/
#define CCS_REP		0x62
#define CCS_DA		0x63
#define CCS_VPA		0x64	/* line position absolute, 8.3.158	*/
#define CCS_VPR		0x65	/* line position forward, 8.3.160	*/
#define CCS_HVP		0x66
#define CCS_TBC		0x67
#define CCS_SM		0x68	/* set mode, 7.1	*/
#define CCS_MC		0x69	/* media copy, 6.6	*/
#define CCS_HPB		0x6a	/* character position backward, 8.3.58	*/
#define CCS_VPB		0x6b	/* line position backward, 8.3.159	*/
#define CCS_RM		0x6c	/* reset mode, 7.1	*/
#define CCS_SGR		0x6d
#define CCS_DSR		0x6e
#define CCS_DAQ		0x6f	/* define area qualification, 6.5.2	*/

/* ECMA-48 5.4 Control sequences, Table 4, CSI F with I = 02/00 */

#define CCS_SL		0x40	/* scroll left,  8.3.121	*/
#define CCS_SR		0x41	/* scroll right, 8.3.135	*/
#define CCS_GSM		0x42
#define CCS_GSS		0x43
#define CCS_FNT		0x44
#define CCS_TSS		0x45
#define CCS_JFY		0x46
#define CCS_SPI		0x47
#define CCS_QUAD	0x48
#define CCS_SSU		0x49
#define CCS_PFS		0x4a
#define CCS_SHS		0x4b
#define CCS_SVS		0x4c
#define CCS_IGS		0x4d
#define CCS_HTSA	0x4e	/* char tab set abs, deprecated, f.8.3	*/
#define CCS_IDCS	0x4f

#define CCS_PPA		0x50	/* page position absolute, 8.3.96	*/
#define CCS_PPR		0x51	/* page position forward,  8.3.98	*/
#define CCS_PPB		0x52	/* page position backward, 8.3.97	*/
#define CCS_SPD		0x53
#define CCS_DTA		0x54	/* dimension text area, 8.3.36	*/
#define CCS_SLH		0x55	/* set line home,  8.3.122	*/
#define CCS_SLL		0x56	/* set line limit, 8.3.123	*/
#define CCS_FNK		0x57
#define CCS_SPQR	0x58
#define CCS_SEF		0x59
#define CCS_PEC		0x5a
#define CCS_SSW		0x5b
#define CCS_SACS	0x5c
#define CCS_SAPV	0x5d
#define CCS_STAB	0x5e
#define CCS_GCC		0x5f

#define CCS_TATE	0x60	/* tabulation aligned trailing edge, 6.7 */
#define CCS_TALE	0x61	/* tabulation aligned leading edge, 6.7	*/
#define CCS_TAC		0x62	/* tabulation aligned centered, 6.7	*/
#define CCS_TCC		0x63	/* tabulation centered on character, 6.7 */
#define CCS_TSR		0x64
#define CCS_SCO		0x65
#define CCS_SRCS	0x66
#define CCS_SCS		0x67
#define CCS_SLS		0x68
#define CCS_SPH		0x69	/* set page home,  8.3.131	*/
#define CCS_SPL		0x6a	/* set page limit, 8.3.133	*/
#define CCS_SCP		0x6b

/* ECMA-48 5.5 Independent control functions, ESC Fs */

#define CCS_DMI		0x60
#define CCS_INT		0x61
#define CCS_EMI		0x62
#define CCS_RIS		0x63
#define CCS_CMD		0x64	/* ECMA-35 15.3 */
#define CCS_LS2		0x6e	/* ECMA-35 7.3 */
#define CCS_LS3		0x6f	/* ECMA-35 7.3 */

#define CCS_LS3R	0x7c	/* ECMA-35 7.3 */
#define CCS_LS2R	0x7d	/* ECMA-35 7.3 */
#define CCS_LS1R	0x7e	/* ECMA-35 7.3 */

#endif  /* CCS_NAMES_H */
