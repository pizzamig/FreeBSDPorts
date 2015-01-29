# Created by: Luca Pizzamiglio <luca.pizzamiglio@gmail.com>
# $FreeBSD$

PORTNAME=	gnu-efi
PORTVERSION=	3.0.1
CATEGORIES=	sysutils
MASTER_SITES=	SF/${PORTNAME}/

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	The gnu-efi library, useful for several efi tools

LICENSE=	BSD

MAKE_JOBS_UNSAFE=	yes
USES+=	gmake tar:bz2
USE_GCC=	4.8+
MAKE_ARGS+=	CC=${CC}
MAKE_ARGS+=	INSTALLPREFIX=${STAGEDIR}
MAKE_ARGS+=	PREFIX=${STAGEDIR}/${PREFIX}
BUILD_DEPENDS+=	${LOCALBASE}/bin/objdump:${PORTSDIR}/devel/binutils
#MAKE_ARGS+=	LD=${LOCALBASE}/bin/ld

ONLY_FOR_ARCHS=	i386 amd64

.include <bsd.port.options.mk>

LDFLAGS=	
.if ${ARCH} == "amd64"
PLIST_SUB=	GNUARCH="x86_64"
.endif

.if ${ARCH} == "i386"
PLIST_SUB=	GNUARCH="ia32"
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/gnuefi/Makefile
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/inc/Makefile
	@${REINPLACE_CMD} -e "s|apps||" \
		${WRKSRC}/Makefile

.include <bsd.port.mk>
