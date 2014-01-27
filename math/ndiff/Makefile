# Created by: Stefan A. Deutscher (sad@mailaps.org)
# $FreeBSD: math/ndiff/Makefile 340722 2014-01-22 17:00:46Z mat $

PORTNAME=	ndiff
PORTVERSION=	2.00
PORTREVISION=	4
CATEGORIES=	math
MASTER_SITES=	ftp://ftp.math.utah.edu/pub/misc/
#PKGNAMEPREFIX=

MAINTAINER=	luca.pizzammiglio@gmail.com
COMMENT=	Compare putatively similar files, ignoring small numeric differences

#LICENSE=	

GNU_CONFIGURE=	yes

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

ALL_TARGET=	all check-runs

MAN1=		ndiff.1
.if !defined(NOPORTDOCS)
PORTDOCS=	*
.endif

post-patch:
	@${REINPLACE_CMD} -e "s:%%DATADIR%%:${DATADIR}:g" ${WRKSRC}/Makefile.in

post-build:
	@${ECHO_MSG} "If there were no errors in the above checks then type"
	@${ECHO_MSG}
	@${ECHO_MSG} "	${MAKE} install"
	@${ECHO_MSG}
	@${ECHO_MSG} "to install ${PORTNAME}-${PORTVERSION}"

post-install:
.if !defined(NOPORTDOCS)
	${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/${PORTNAME}.pdf  ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/${PORTNAME}.ps   ${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/${PORTNAME}.html ${DOCSDIR}
.endif

.include <bsd.port.mk>
