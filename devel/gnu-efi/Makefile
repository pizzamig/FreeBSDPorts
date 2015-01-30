# Created by: Edward Tomasz Napierala <trasz@FreeBSD.org>
# $FreeBSD: head/devel/gnu-efi/Makefile 377600 2015-01-21 13:20:22Z trasz $

PORTNAME=	gnu-efi
PORTVERSION=	3.0.1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE}
MASTER_SITE_SUBDIR=	gnu-efi

MAINTAINER=	trasz@FreeBSD.org
COMMENT=	SDK for EFI applications

LICENSE=	GPLv2

USES=		gmake tar:bz2
# The version of GCC is also hard-coded in files/patch-Make.defaults.
USE_GCC=	4.8
MAKE_JOBS_UNSAFE=	yes
CFLAGS+=	"-fPIC"
ONLY_FOR_ARCHS=	amd64

post-patch:
	@${REINPLACE_CMD} -e 's|%%CC%%|${CC}|g' ${WRKSRC}/Make.defaults

.include <bsd.port.mk>
