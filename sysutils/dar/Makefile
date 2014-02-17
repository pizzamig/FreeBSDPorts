# Created by: Edson Brandi <ebrandi@fugspbr.org>
# $FreeBSD: head/sysutils/dar/Makefile 343635 2014-02-10 13:58:28Z ehaupt $

PORTNAME=	dar
PORTVERSION=	2.3.11
CATEGORIES=	sysutils archivers
MASTER_SITES=	SF

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	A full featured command-line backup tool, aimed for disks

USE_AUTOTOOLS=	libtool

#USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=	--disable-build-html --datadir=${DATADIR} --disable-upx

CPPFLAGS+=	-DHAVE_DECL_GETOPT=0

OPTIONS_DEFINE=	DOCS NLS

OPTIONS_SUB=	yes

NLS_USES=	gettext
NLS_CONFIGURE_ON=	--with-libintl-prefix=${STAGEDIR}${PREFIX}
NLS_CONFIGURE_OFF=	--disable-nls
NLS_CPPFLAGS=	-I${LOCALBASE}/include
NLS_LDFLAGS=	-L${LOCALBASE}/lib

.include <bsd.port.options.mk>

post-install:
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC}/doc && ${INSTALL_DATA} *.html *.dtd *.txt *.jpg [CR]* \
	${STAGEDIR}${DOCSDIR}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}/samples
	cd ${WRKSRC}/doc/samples && ${INSTALL_DATA} [JR]* [a-z]* \
	${STAGEDIR}${DOCSDIR}/samples
	@${MKDIR} ${STAGEDIR}${DOCSDIR}/mini-howto
	cd ${WRKSRC}/doc/mini-howto && ${INSTALL_DATA} \
	*.html README ${STAGEDIR}${DOCSDIR}/mini-howto
.endif

.include <bsd.port.mk>
