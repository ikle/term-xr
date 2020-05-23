# Caracter Code Structure

## Coding System

*  Function: parse input to sequence of codes.
*  Input: unspecified, depends on coding system.
*  Output: sequence of codes.

Standart ECMA-35 requires that, regardless of the encoding system used,
the following three characters always have fixed code positions:

*  Delete, DEL — 07/15.
*  Escape, ESC — 01/11.
*  Space,  SP  — 02/00.

We define two types of decoders, raw and unicode:

*  Raw: output 7- or 8-bit codes, ECMA-35 conditions are meet.
*  Unicode: output Unicode codes.

For unicode decoder input characters that have Unicode codes are mapped
to them, the rest are mapped into Private Use Area into window from U+F000
to U+F8FF. Since unicode decoder converts to Unicode, the ECMA-35 condition
is always fulfilled.

## Data Element

A data element is either a character encoded as a true Unicode character,
or a special control character, possibly with a an argument.

## Character Mapping

*  Function: convert sequence of codes.
*  Input: sequence of codes.
*  Output: sequence of Unicode codes.

The system has six mapping tables: two for converting control characters
(C0 and C1 sets) and four for converting graphic characters (G0 — G3 sets).

Standard ECMA-35 defines four disjoint code windows:

*  CL in range from 00/00 to 01/15 for designated and invoked C0 set.
*  GL in range from 02/01 to 07/14 for invoked graphic set, any of the sets
   from G0 — G3 can be invoken in this window.
*  CR in range from 08/00 to 09/15 for designated and invoked C1 set.
*  GR in range from 10/00 to 15/00 for invoked graphic set, any of the sets
   from G1 — G3 can be invoken in this window.

And, as stated earlier, the characters SP and DEL have fixed positions.
We add the U window to which all characters with codes over 15/15 fall.
This window always has a one-to-one mapping.

If there is no match for the active mapping for the input code, then such
code is silently discarded. If a graphic symbol is present in the invoked
set, but cannot be converted to a Unicode symbol, then symbol SUB is
substituted:

*  Substitute, SUB — 01/10.

## Escape Sequence Parser

*  Function: convert sequence of codes to sequence of data elements.
*  Input: sequence of codes.
*  Output: sequence of data elements.

If the input code is not part of the escape sequence, then it is mapped
to a character. Symbols NUL and SYN, if present in the input, are silently
discarded:

*  Null, NUL — 00/00.
*  Synchronous Idle, SYN — 01/06.

It is worth noting that the parser works with untransformed characters at
the input.

## Control Sequence Parser

*  Function: parse control sequences to sequence of data elements.
*  Input: sequence of data elements.
*  Output: sequence of data elements without control sequence introducers.

Will be defined later.

## Annex A: C Language Interface

This annex describes the C language interface for the Caracter Code
Structure library.

### Data Element

Data elements are represented by the next structure:
```c
struct ccs_de {
	ccs_code_t  code;
	ccs_size_t  size, len;
	ccs_code_t  arg[];
};
```
where
*  code — a control or graphic character code;
*  size — the size of the argument buffer in characters, specified by
   the caller;
*  len  — the argument string length;
*  arg  — the argument buffer allocated by the caller.

Note that argument if present (depends on code) is the NUL-terminated string
and the field len specify length of that string without terminating NUL
character. In case of buffer overflow, field len will be equal to the size
of buffer and terminating character will not be written.

### Character Set

Constructor and destructor:
```c
struct ccs_charset *ccs_charset_alloc (FILE *f);
void ccs_charset_free (struct ccs_charset *o);
```

Method to locate character set by ISO-IR code:
```c
struct ccs_charset *ccs_charset_locate (const struct ccs_de *de);
```

### Pool

The CCS pool is designed for caching CCS objects, such as character sets
and coding system decoders.

Constructor and destructor:
```c
struct ccs_pool *ccs_pool_alloc (void);
void ccs_pool_free (struct ccs_pool *o);
```

Methods to locate objects:
```c
struct ccs_charset *
ccs_pool_get_charset (struct ccs_pool *o, const struct ccs_de *de);
```

### Character Mapping

Constructor and destructor:
```c
struct ccs_map *ccs_map_alloc (void);
void ccs_map_free (struct ccs_map *o);
```

Methods to designate character set to Ci and Gi set:
```c
int ccs_map_load_cs (struct ccs_map *o, int i, struct ccs_charset *s);
int ccs_map_load_gs (struct ccs_map *o, int i, struct ccs_charset *s);

```
If s is NULL then the identity mapping is loaded. By default, identity
mapping is designated to all sets.

Methods to invoke designated character set into GL and GR:
```c
int ccs_map_lock_gl  (struct ccs_map *o, int i);
int ccs_map_lock_gr  (struct ccs_map *o, int i);
int ccs_map_shift_gl (struct ccs_map *o, int i);
```

By default, G0 is locked into GL and G1 is locked into GR.

Method to do conversion:
```c
ccs_code_t ccs_map_process (struct ccs_map *o, ccs_code_t c);
```

This method returns converted code or NUL if input code consumed but output
character is not available yet (in case of multibyte charset invoked) or
no match for input code found.

### Escape Sequence Parser

Constructor and destructor:
```c
struct ccs_core *ccs_core_alloc (struct ccs_map *map);
void ccs_core_free (struct ccs_core *o);
```

Method to do conversion:
```c
int ccs_core_process (struct ccs_core *o, ccs_code_t c, struct ccs_de *de);
```

### Control Sequence Parser

Constructor and destructor:
```c
struct ccs_func *ccs_func_alloc (void);
void ccs_func_free (struct ccs_func *o);
```

Method to do conversion:
```c
int ccs_process (struct ccs_func *o, struct ccs_de *de);
```

### Upper Level Interface

Constructor and destructor:
```c
struct ccs *ccs_alloc (void);
void ccs_free (struct ccs *o);
```

Constructor creates and incapsulates character mapping, escape sequence
parser and conrol sequence parser objects.

Method to do conversion:
```c
int ccs_process (struct ccs *o, ccs_code_t c, struct ccs_de *de);
```

Process method:
1. parses escape sequences;
2. maps characters;
3. process designate, invoke, lock and shift operations;
4. parses control sequences.

## Annex B: Character Set Description File

*  A sequence of characters starting with octothorpe (HASH) character to
   the end of line (EOL) is a comment and is ignored during parsing.
*  Empty lines are ignored.
*  Space is the SP or TAB character.
*  Spaces separate tokens and ignored during parsing.
*  Codes represented by hexadecimal numbers.
*  Multibyte character mapping (map) is a non-empty sequence of input codes,
   colon character and Unicode code for that character terminated by EOL.
*  Include directive references base character set and consists keyword
   “include” (without quotes) and referenced charset name, terminated by EOL.
*  Character set is a sequence of directives and mutibyte character
   mappings.

### Example: DEC Special Graphics Character Set

The DEC special graphics character set can be specified as:
```
include d4-42	# US ASCII

5f	: 0a	# NBSP
60	: 25c6	# ◆
61	: 2592	# ▒
62	: 2409	# ␉
63	: 240c	# ␌
64	: 240d	# ␍
65	: 240a	# ␊
66	: b0	# °
67	: b1	# ±
68	: 2424	# ␤
69	: 240b	# ␋
6a	: 2518	# ┘
6b	: 2510	# ┐
6c	: 250c	# ┌
6d	: 2514	# └
6e	: 253c	# ┼
6f	: 23ba	# ⎺
70	: 23bb	# ⎻
71	: 2500	# ─
72	: 23bc	# ⎼
73	: 23bd	# ⎽
74	: 251c	# ├
75	: 2524	# ┤
76	: 2534	# ┴
77	: 252c	# ┬
78	: 2502	# │
79	: 2264	# ≤
7a	: 2265	# ≥
7b	: 03c0	# π
7c	: 2260	# ≠
7d	: a3	# £
7e	: b7	# ·
```

### Example: ISO-IR 002 — international reference version (IRV) of ISO 646

```
include d4-42	# US ASCII

24	: a4	# ¤
```

### Example: ISO-IR 004 — Unated Kingdom 7-bit data code

```
include d4-42	# US ASCII

24	: a3	# £
```

### Example: ISO-IR 042 — Japanese Graphic Character Set

The ARIB STD B24 character set 0x24 (row number 4, Hiragana), first column:
```
24 41	: 3041	# ぁ
24 42	: 3042	# あ
24 43	: 3043	# ぃ
24 44	: 3044	# い
24 45	: 3045	# ぅ
24 46	: 3046	# う
24 47	: 3047	# ぇ
24 48	: 3048	# え
24 49	: 3049	# ぉ
24 4a	: 304a	# お
24 4b	: 304b	# か
24 4c	: 304c	# が
24 4d	: 304d	# き
24 4e	: 304e	# ぎ
24 4f	: 304f	# く
```
