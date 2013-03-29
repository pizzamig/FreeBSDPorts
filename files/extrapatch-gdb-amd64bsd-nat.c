--- gdb/amd64bsd-nat.c.orig	2013-03-29 17:26:45.000000000 +0100
+++ gdb/amd64bsd-nat.c	2013-03-29 17:27:00.000000000 +0100
@@ -36,6 +36,21 @@
 #include "inf-ptrace.h"
 
 
+static void
+print_regs( const char * msg, struct reg *r )
+{
+  printf("%s reg={"
+    "r15=%llx r14=%llx r13=%llx r12=%llx r11=%llx r10=%llx r9=%llx r8=%llx"
+    " rdi=%llx rsi=%llx rbp=%llx rbx=%llx rdx=%llx rcx=%llx rax=%llx"
+    " trapno=%x fs=%x gs=%x err=%x es=%x ds=%x"
+    " rip=%llx cs=%llx rflags=%llx rsp=%llx ss=%llx}\n",
+    msg,
+    r->r_r15, r->r_r14, r->r_r13, r->r_r12, r->r_r11, r->r_r10, r->r_r9, r->r_r8,
+    r->r_rdi, r->r_rsi, r->r_rbp, r->r_rbx, r->r_rdx, r->r_rcx, r->r_rax,
+    r->r_trapno, (uint32_t)r->r_fs, (uint32_t)r->r_gs, r->r_err, (uint32_t)r->r_es, (uint32_t)r->r_ds,
+    r->r_rip, r->r_cs, r->r_rflags, r->r_rsp, r->r_ss );
+}
+
 /* Fetch register REGNUM from the inferior.  If REGNUM is -1, do this
    for all registers (including the floating-point registers).  */
 
@@ -86,13 +101,15 @@
       if (ptrace (PT_GETREGS, PIDGET (inferior_ptid),
                   (PTRACE_TYPE_ARG3) &regs, 0) == -1)
         perror_with_name (_("Couldn't get registers"));
-
+      print_regs("After PT_GETREGS - before collect_native_gregset\n", &regs);
       amd64_collect_native_gregset (regcache, &regs, regnum);
+      print_regs("Before PT_SETREGS - after collect_native_gregset\n", &regs);
 
       if (ptrace (PT_SETREGS, PIDGET (inferior_ptid),
 	          (PTRACE_TYPE_ARG3) &regs, 0) == -1)
         perror_with_name (_("Couldn't write registers"));
 
+      print_regs("After PT_SETREGS - after collect_native_gregset\n", &regs);
       if (regnum != -1)
 	return;
     }
