# Created by: Heiner Eichmann <h.eichmann@gmx.de>
# $FreeBSD: textproc/kdiff3/Makefile 339314 2014-01-10 04:48:02Z tabthorpe $

PORTNAME=	kdiff3
PORTVERSION=	0.9.98
#PORTREVISION=	0
CATEGORIES=	textproc kde
MASTER_SITES=	SF

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	A KDE4 graphical frontend for diff

LICENSE=	GPLv2

USE_KDE4=	kdelibs libkonq kdeprefix kdehier automoc4
USE_QT4=	moc_build qmake_build rcc_build uic_build
USES=		cmake

OPTIONS_DEFINE=	NLS DOCS
OPTIONS_DEFAULT=	NLS

OPTIONS_SUB=	yes

NLS_USES=	gettext
NLS_CMAKE_OFF=	-DBUILD_po:BOOL=FALSE
NLS_CMAKE_ON=	-DBUILD_po:BOOL=TRUE
DOCS_CMAKE_OFF=	-DBUILD_doc:BOOL=FALSE
DOCS_CMAKE_ON=	-DBUILD_doc:BOOL=TRUE

post-patch:
#Fix build with kdelibs>=4.5.0
	${REINPLACE_CMD} -e 's,V4.1.2-Based,V4.2-Based,g' \
		${WRKSRC}/doc/*/index.docbook

.include <bsd.port.mk>
