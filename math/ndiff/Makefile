# Created by: Stefan A. Deutscher (sad@mailaps.org)
# $FreeBSD: math/ndiff/Makefile 340722 2014-01-22 17:00:46Z mat $

PORTNAME=	ndiff
PORTVERSION=	2.00
PORTREVISION=	4
CATEGORIES=	math
MASTER_SITES=	ftp://ftp.math.utah.edu/pub/misc/

MAINTAINER=	luca.pizzammiglio@gmail.com
COMMENT=	Compare putatively similar files, ignoring small numeric differences

#LICENSE=	

GNU_CONFIGURE=	yes
USES=		gmake

OPTIONS_DEFINE=	DOCS GMP

OPTIONS_DEFAULT=	

GMP_LIB_DEPENDS=	libgmp.so:${PORTSDIR}/math/gmp
GMP_CFLAGS=	-I${LOCALBASE}/include
GMP_LDFLAGS=	-L${LOCALBASE}/lib
GMP_CONFIGURE_ON=	--with-gmp

.include <bsd.port.options.mk>

.if ! ${PORT_OPTIONS:MGMP}
.if ${ARCH} == sparc64
CONFIGURE_ARGS+= --with-long-double
.else
CONFIGURE_ARGS+= --with-double
.endif
.endif

post-install:
.if ${PORT_OPTIONS:MDOCS}
	${MKDIR} ${STAGEDIR}${DOCSDIR}
. for f in ${PORTNAME}.html ${PORTNAME}.pdf ${PORTNAME}.ps
	${INSTALL_DATA} ${WRKSRC}/${f}.html ${STAGEDIR}${DOCSDIR}
. endfor
.endif

.include <bsd.port.mk>
