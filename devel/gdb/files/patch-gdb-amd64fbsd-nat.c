--- gdb/amd64fbsd-nat.c.orig	2015-02-19 12:58:07.000000000 +0100
+++ gdb/amd64fbsd-nat.c	2015-02-22 14:12:55.721736807 +0100
@@ -24,8 +24,11 @@
 
 #include <signal.h>
 #include <sys/types.h>
+#include <sys/procfs.h>
 #include <sys/ptrace.h>
 #include <sys/sysctl.h>
+#include <sys/user.h>
+#include <sys/param.h>
 #include <machine/reg.h>
 
 #include "fbsd-nat.h"
@@ -244,6 +247,10 @@
 
   SC_RBP_OFFSET = offset;
 
+// Newer versions of FreeBSD provide a better way to locate the signtramp
+#if ( __FreeBSD_version/100000 < 9 ) \
+	|| ( ( __FreeBSD_version/100000 == 9 ) && ( __FreeBSD_version < 902505 ) ) \
+	|| ( ( __FreeBSD_version/100000 == 10 ) && ( __FreeBSD_version < 1000700 ) )
   /* FreeBSD provides a kern.ps_strings sysctl that we can use to
      locate the sigtramp.  That way we can still recognize a sigtramp
      if its location is changed in a new kernel.  Of course this is
@@ -264,4 +271,25 @@
 	amd64fbsd_sigtramp_end_addr = ps_strings;
       }
   }
+#else
+  /* FreeBSD provides a kern.proc.sigtramp sysctl that we can use to
+     locate the sigtramp.  That way we can still recognize a sigtramp
+     if its location is changed in a new kernel. */
+  {
+    int mib[4];
+    struct kinfo_sigtramp kst;
+    size_t len;
+
+    mib[0] = CTL_KERN;
+    mib[1] = KERN_PROC;
+    mib[2] = KERN_PROC_SIGTRAMP;
+    mib[3] = getpid();
+    len = sizeof (kst);
+    if (sysctl (mib, sizeof(mib)/sizeof(mib[0]), &kst, &len, NULL, 0) == 0)
+      {
+	amd64fbsd_sigtramp_start_addr = kst.ksigtramp_start;
+	amd64fbsd_sigtramp_end_addr = kst.ksigtramp_end;
+      }
+  }
+#endif
 }
