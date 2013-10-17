--- gdb/dwarf2read.c.orig	2012-08-27 18:42:55.000000000 +0200
+++ gdb/dwarf2read.c	2013-03-28 17:34:19.000000000 +0100
@@ -497,6 +497,7 @@
   unsigned int checked_producer : 1;
   unsigned int producer_is_gxx_lt_4_6 : 1;
   unsigned int producer_is_icc : 1;
+  unsigned int producer_is_unknown : 1;
 };
 
 /* Persistent data held for a compilation unit, even when not
@@ -1612,6 +1613,8 @@
 
 static void process_cu_includes (void);
 
+static void check_producer (struct dwarf2_cu *cu);
+
 #if WORDS_BIGENDIAN
 
 /* Convert VALUE between big- and little-endian.  */
@@ -6649,6 +6652,17 @@
   VEC_free (dwarf2_per_cu_ptr, dwarf2_per_objfile->just_read_cus);
 }
 
+/* Return non-zero if the CU's PRODUCER string is unknown.  */
+
+static int
+producer_is_unknown (struct dwarf2_cu *cu)
+{
+  if (!cu->checked_producer)
+    check_producer (cu);
+
+  return cu->producer_is_unknown;
+}
+
 /* Generate full symbol information for PER_CU, whose DIEs have
    already been loaded into memory.  */
 
@@ -6727,7 +6741,7 @@
 	 Still one can confuse GDB by using non-standard GCC compilation
 	 options - this waits on GCC PR other/32998 (-frecord-gcc-switches).
 	 */ 
-      if (cu->has_loclist && gcc_4_minor >= 5)
+      if ((cu->has_loclist && gcc_4_minor >= 5) || producer_is_unknown (cu))
 	symtab->locations_valid = 1;
 
       if (gcc_4_minor >= 5)
@@ -9484,6 +9498,7 @@
 	 for their space efficiency GDB cannot workaround gcc-4.5.x -gdwarf-4
 	 combination.  gcc-4.5.x -gdwarf-4 binaries have DW_AT_accessibility
 	 interpreted incorrectly by GDB now - GCC PR debug/48229.  */
+      cu->producer_is_unknown = 1;
     }
   else if (strncmp (cu->producer, "GNU ", strlen ("GNU ")) == 0)
     {
@@ -9505,6 +9520,7 @@
     {
       /* For other non-GCC compilers, expect their behavior is DWARF version
 	 compliant.  */
+      cu->producer_is_unknown = 1;
     }
 
   cu->checked_producer = 1;
