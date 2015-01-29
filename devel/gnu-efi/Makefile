# Created by: Luca Pizzamiglio <luca.pizzamiglio@gmail.com>
# $FreeBSD$

PORTNAME=	gnu-efi
PORTVERSION=	3.0.1
CATEGORIES=	devel
MASTER_SITES=	SF/${PORTNAME}/

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	Library gnu-efi, useful for several efi tools

LICENSE=	BSD

USES+=	gmake tar:bz2
USE_GCC=	4.8+
MAKE_ARGS+=	CC=${CC} INSTALLPREFIX=${STAGEDIR} PREFIX=${STAGEDIR}/${PREFIX}

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
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/gnuefi/Makefile
	@${REINPLACE_CMD} -e 's|$$$$(dir $$$$@)|$$$$(@D)|' \
		${WRKSRC}/inc/Makefile
	@${REINPLACE_CMD} -e "s|apps||" \
		${WRKSRC}/Makefile

.include <bsd.port.mk>
