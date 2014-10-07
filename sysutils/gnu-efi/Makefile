PORTNAME=	gnu-efi
MAINVERSION=	3.0
PORTVERSION=	${MAINVERSION}w

DISTNAME=	${PORTNAME}_${PORTVERSION}.orig
CATEGORIES=	sysutils
MASTER_SITES=	SF/${PORTNAME}/

WRKSRC=	${WRKDIR}/${PORTNAME}-${MAINVERSION}
USES+=	gmake desthack

USE_GCC=	4.8
MAKE_JOBS_UNSAFE=	yes

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
