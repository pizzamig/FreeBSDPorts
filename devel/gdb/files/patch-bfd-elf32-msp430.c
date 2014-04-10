--- bfd/elf32-msp430.c.orig	2014-04-10 11:28:30.545550580 +0200
+++ bfd/elf32-msp430.c	2014-04-10 11:31:43.563551751 +0200
@@ -2464,13 +2464,13 @@
 #undef	ELF_OSABI		
 #define	ELF_OSABI		ELFOSABI_NONE
 
-static const struct bfd_elf_special_section msp430_ti_elf_special_sections[] =
-{
+//static const struct bfd_elf_special_section msp430_ti_elf_special_sections[] =
+//{
   /* prefix, prefix_length,        suffix_len, type,               attributes.  */
-  { STRING_COMMA_LEN (".TI.symbol.alias"),  0, SHT_MSP430_SYM_ALIASES, 0 },
-  { STRING_COMMA_LEN (".TI.section.flags"), 0, SHT_MSP430_SEC_FLAGS,   0 },
-  { STRING_COMMA_LEN ("_TI_build_attrib"),  0, SHT_MSP430_ATTRIBUTES,  0 },
-  { NULL, 0,                                0, 0,                      0 }
-};
+//  { STRING_COMMA_LEN (".TI.symbol.alias"),  0, SHT_MSP430_SYM_ALIASES, 0 },
+//  { STRING_COMMA_LEN (".TI.section.flags"), 0, SHT_MSP430_SEC_FLAGS,   0 },
+//  { STRING_COMMA_LEN ("_TI_build_attrib"),  0, SHT_MSP430_ATTRIBUTES,  0 },
+//  { NULL, 0,                                0, 0,                      0 }
+//};
 
 #include "elf32-target.h"
