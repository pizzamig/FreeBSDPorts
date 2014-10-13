# Created by: Luca Pizzamiglio <luca.pizzamiglio@gmail.com>
# $FreeBSD$

PORTNAME=	gnu-efi
MAINVERSION=	3.0
PORTVERSION=	${MAINVERSION}w
CATEGORIES=	sysutils
MASTER_SITES=	SF/${PORTNAME}/
DISTNAME=	${PORTNAME}_${PORTVERSION}.orig

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	The gnu-efi library, useful for several efi tools

LICENSE=	BSD

MAKE_JOBS_UNSAFE=	yes
USES+=	gmake
USE_GCC=	4.8+
WRKSRC=	${WRKDIR}/${PORTNAME}-${MAINVERSION}

BUILD_DEPENDS+=	${LOCALBASE}/bin/objdump:${PORTSDIR}/devel/binutils

ONLY_FOR_ARCHS=	i386 amd64

.include <bsd.port.options.mk>

.if ${ARCH} == "amd64"
PLIST_SUB=	GNUARCH="x86_64"
.endif

.if ${ARCH} == "i386"
PLIST_SUB=	GNUARCH="ia32"
.endif

post-patch:
	@${REINPLACE_CMD} -e "s|gcc|gcc48|" \
		${WRKSRC}/Make.defaults
	@${REINPLACE_CMD} -e "s|apps||" \
		${WRKSRC}/Makefile
	@${REINPLACE_CMD} -e "s|GNUEFISTAGEDIR|${STAGEDIR}|" \
		${WRKSRC}/Make.defaults
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/gnuefi/Makefile
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/inc/Makefile

.include <bsd.port.mk>
