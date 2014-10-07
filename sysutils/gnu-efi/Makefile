PORTNAME=	gnu-efi
MAINVERSION=	3.0
PORTVERSION=	${MAINVERSION}w

DISTNAME=	${PORTNAME}_${PORTVERSION}.orig
CATEGORIES=	sysutils
MASTER_SITES=	SF/${PORTNAME}/

WRKSRC=	${WRKDIR}/${PORTNAME}-${MAINVERSION}
USES+=	gmake desthack

USE_GCC=	4.9
#BUILD_DEPENDS+=	${LOCALBASE}/bin/gcc48:${PORTSDIR}/lang/gcc49
MAKE_JOBS_UNSAFE=	yes

post-patch:
	@${REINPLACE_CMD} -e "s|gcc|gcc49|" \
		${WRKSRC}/Make.defaults
	@${REINPLACE_CMD} -e "s|apps||" \
		${WRKSRC}/Makefile
	@${REINPLACE_CMD} -e "s|GNUEFISTAGEDIR|${STAGEDIR}|" \
		${WRKSRC}/Make.defaults


.include <bsd.port.mk>
