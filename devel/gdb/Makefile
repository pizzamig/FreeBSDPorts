# Created by: Steven Kreuzer <skreuzer@FreeBSD.org>
# $FreeBSD: head/devel/gdb/Makefile 371280 2014-10-20 16:04:12Z mva $

PORTNAME=	gdb
PORTVERSION=	7.8.1
CATEGORIES=	devel
MASTER_SITES=	GNU:gdb http://aldan.algebra.com/~mi/:gdbtk
DISTFILES=	${PORTNAME}-${PORTVERSION}${EXTRACT_SUFX}:gdb
EXTRACT_ONLY=	${PORTNAME}-${PORTVERSION}${EXTRACT_SUFX}

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	GNU GDB of newer version than comes with the system

LICENSE=	GPLv3

USES=		iconv gmake libtool tar:xz
USE_CSTD=	gnu89
GNU_CONFIGURE=	yes
CONFIGURE_ENV=	CONFIGURED_M4=m4 CONFIGURED_BISON=byacc
CONFIGURE_ARGS=	--program-suffix=${PORTVERSION:S/.//g} \
		--enable-targets=all \
		--with-gdb-datadir=${PREFIX}/share/gdb${PORTVERSION:S/.//g} \
		--with-separate-debug-dir=/usr/lib/debug \
		${ICONV_CONFIGURE_ARG} \
		--without-libunwind-ia64
CFLAGS:=	${CFLAGS:C/ +$//}	# blanks at EOL creep in sometimes
CFLAGS+=	-DRL_NO_COMPAT -Wno-unused-function -Wno-unused-variable
EXCLUDE=	dejagnu expect sim texinfo intl
EXTRACT_AFTER_ARGS=	${EXCLUDE:S/^/--exclude /}

VER=		${PORTVERSION:S/.//g}
PLIST_SUB=	VER=${VER}

ONLY_FOR_ARCHS=	i386 amd64 powerpc powerpc64	# untested elsewhere, might work

OPTIONS_DEFINE=	DEBUG EXPAT GDB_LINK INSIGHT PYTHON THREADS TUI

OPTIONS_DEFAULT=	GDB_LINK THREADS TUI PORT_READLINE

OPTIONS_SINGLE=	READLINE
OPTIONS_SINGLE_READLINE=	BASE_READLINE BUNDLED_READLINE PORT_READLINE

GDB_LINK_DESC=		Create the gdb link
INSIGHT_DESC=		Tcl/Tk GUI (experimental!)
BASE_READLINE_DESC=	from base system(EXPERIMENTAL)
BUNDLED_READLINE_DESC=	from gdb distfile
PORT_READLINE_DESC=	from devel/readline port
TUI_DESC=		Text User Interface enabled

OPTIONS_SUB=	yes

BASE_READLINE_USES=	readline
BASE_READLINE_CFLAGS=	-D_rl_echoing_p=readline_echoing_p
BUNDLED_READLINE_CONFIGURE_OFF=	--with-system-readline
DEBUG_CFLAGS=		-g
EXPAT_CONFIGURE_ON=	--with-expat=yes
EXPAT_CONFIGURE_OFF=	--without-expat
EXPAT_LIB_DEPENDS=	libexpat.so:${PORTSDIR}/textproc/expat2
INSIGHT_USES=	tk
INSIGHT_CONFIGURE_ENABLE=	gdbtk
INSIGHT_CONFIGURE_ON=	--with-tclconfig=${TCL_LIBDIR} \
			--with-tclinclude=${TCL_INCLUDEDIR}/generic \
			--with-tkconfig=${TK_LIBDIR} \
			--with-tkinclude=${TK_INCLUDEDIR}/generic \
			--with-itclconfig=${LOCALBASE}/lib/itcl3.4 \
			--with-itkconfig=${LOCALBASE}/lib/itk3.3
INSIGHT_DISTFILES=	gdbtk-20140114.tar.xz:gdbtk
INSIGHT_EXTRA_PATCHES=	${FILESDIR}/itcl33-patch \
			${FILESDIR}/extrapatch-configure-for-tcl \
			${FILESDIR}/extrapatch-gdbtk \
			${FILESDIR}/extrapatch-libgui \
			${FILESDIR}/extrapatch-system-tkTable
INSIGHT_LIB_DEPENDS=	libitk.so:${PORTSDIR}/x11-toolkits/itk
INSIGHT_RUN_DEPENDS=	${LOCALBASE}/lib/iwidgets:${PORTSDIR}/x11-toolkits/iwidgets	\
			${LOCALBASE}/lib/Tktable2.10/pkgIndex.tcl:${PORTSDIR}/x11-toolkits/tktable
PYTHON_CONFIGURE_ON=	--with-python=${PYTHON_CMD}
PYTHON_CONFIGURE_OFF=	--without-python
PYTHON_USES=		python:2
PORT_READLINE_EXTRA_PATCHES=	${FILESDIR}/extrapatch-gdb-tui-tui-io.c
PORT_READLINE_USES=	readline:port
TUI_CONFIGURE_ENABLE=	tui

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MINSIGHT}
PKGNAMESUFFIX=	-insight
CONFLICTS+=	gdb*
post-extract:
	${TAR} -C ${WRKSRC} --exclude tkTable\* -xpf ${DISTDIR}/${_DISTFILES:Mgdbtk*}
.else
CONFLICTS+=	gdb-insight*
.endif

.if ! ${PORT_OPTIONS:MBUNDLED_READLINE}
EXCLUDE+=	readline
.endif

.if ${PORT_OPTIONS:MTHREADS}
EXTRA_PATCHES+=	${FILESDIR}/extrapatch-gdb-configure.tgt \
		${FILESDIR}/extrapatch-gdb-Makefile.in
.endif

.if ${ARCH} == "amd64"
CONFIGURE_TARGET=	x86_64-portbld-freebsd${OSREL}
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|$$| [GDB v${PORTVERSION} for FreeBSD]|' \
		${WRKSRC}/gdb/version.in

.if ${PORT_OPTIONS:MTHREADS}
	@${CP} ${FILESDIR}/fbsd-threads.c ${WRKSRC}/gdb/
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/gdb/gdb \
		${STAGEDIR}${PREFIX}/bin/gdb${VER}
	${INSTALL_MAN} ${WRKSRC}/gdb/doc/gdb.1 \
		${STAGEDIR}${MAN1PREFIX}/man/man1/gdb${VER}.1

.if ${PORT_OPTIONS:MTUI}
	${LN} -sf gdb${VER} ${STAGEDIR}${PREFIX}/bin/gdbtui${VER}
.endif
.if ${PORT_OPTIONS:MINSIGHT}
	${LN} -sf gdb${VER} ${STAGEDIR}${PREFIX}/bin/insight
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/redhat/gui
	${CP} -p ${WRKSRC}/libgui/library/*.tcl	\
		${WRKSRC}/libgui/library/tclIndex \
			${STAGEDIR}${PREFIX}/share/redhat/gui/
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/insight1.0
	${CP} -Rp ${WRKSRC}/gdb/gdbtk/library/*.tcl	\
		${WRKSRC}/gdb/gdbtk/library/*.itcl	\
		${WRKSRC}/gdb/gdbtk/library/*.ith	\
		${WRKSRC}/gdb/gdbtk/library/*.itb	\
		${WRKSRC}/gdb/gdbtk/library/help	\
		${WRKSRC}/gdb/gdbtk/library/images*	\
		${WRKSRC}/gdb/gdbtk/library/tclIndex	\
			${STAGEDIR}${PREFIX}/lib/insight1.0
.endif

.if ${PORT_OPTIONS:MGDB_LINK}
	${LN} -sf gdb${VER} ${STAGEDIR}${PREFIX}/bin/gdb
.endif

.if ${PORT_OPTIONS:MPYTHON}
	(cd ${WRKSRC}/gdb; ${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} install-python )
	(cd ${WRKSRC}/gdb/data-directory ; \
		${SETENV} ${MAKE_ENV} ${MAKE_CMD} ${MAKE_ARGS} install-python )
.endif

.if ${PORT_OPTIONS:MPYTHON}
. for f in gdb gdb/command gdb/function
	@(cd ${STAGEDIR}${PREFIX}/share/gdb${VER}/python/${f} ; ${CHMOD} 644 *.py* )
. endfor
.endif

.include <bsd.port.mk>
