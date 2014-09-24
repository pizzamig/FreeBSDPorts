23a24
> #include "gregset.h"
28a30
> #include <sys/procfs.h>
30a33,34
> #include <sys/user.h>
> #include <sys/param.h>
95a100,139
> /* Transfering the registers between GDB, inferiors and core files.  */
> 
> /* Fill GDB's register array with the general-purpose register values
>    in *GREGSETP.  */
> 
> void
> supply_gregset (struct regcache *regcache, const gregset_t *gregsetp)
> {
>   amd64_supply_native_gregset (regcache, gregsetp, -1);
> }
> 
> /* Fill register REGNUM (if it is a general-purpose register) in
>    *GREGSETPS with the value in GDB's register array.  If REGNUM is -1,
>    do this for all registers.  */
> 
> void
> fill_gregset (const struct regcache *regcache, gdb_gregset_t *gregsetp, int regnum)
> {
>   amd64_collect_native_gregset (regcache, gregsetp, regnum);
> }
> 
> /* Fill GDB's register array with the floating-point register values
>    in *FPREGSETP.  */
> 
> void
> supply_fpregset (struct regcache *regcache, const fpregset_t *fpregsetp)
> {
>   amd64_supply_fxsave (regcache, -1, fpregsetp);
> }
> 
> /* Fill register REGNUM (if it is a floating-point register) in
>    *FPREGSETP with the value in GDB's register array.  If REGNUM is -1,
>    do this for all registers.  */
> 
> void
> fill_fpregset (const struct regcache *regcache, gdb_fpregset_t *fpregsetp, int regnum)
> {
>   amd64_collect_fxsave (regcache, regnum, fpregsetp);
> }
> 
249a294,297
> // Newer versions of FreeBSD provide a better way to locate the signtramp
> #if ( __FreeBSD_version/100000 < 9 ) \
> 	|| ( ( __FreeBSD_version/100000 == 9 ) && ( __FreeBSD_version < 902505 ) ) \
> 	|| ( ( __FreeBSD_version/100000 == 10 ) && ( __FreeBSD_version < 1000700 ) )
269a318,338
> #else
>   /* FreeBSD provides a kern.proc.sigtramp sysctl that we can use to
>      locate the sigtramp.  That way we can still recognize a sigtramp
>      if its location is changed in a new kernel. */
>   {
>     int mib[4];
>     struct kinfo_sigtramp kst;
>     size_t len;
> 
>     mib[0] = CTL_KERN;
>     mib[1] = KERN_PROC;
>     mib[2] = KERN_PROC_SIGTRAMP;
>     mib[3] = getpid();
>     len = sizeof (kst);
>     if (sysctl (mib, sizeof(mib)/sizeof(mib[0]), &kst, &len, NULL, 0) == 0)
>       {
> 	amd64fbsd_sigtramp_start_addr = kst.ksigtramp_start;
> 	amd64fbsd_sigtramp_end_addr = kst.ksigtramp_end;
>       }
>   }
> #endif
