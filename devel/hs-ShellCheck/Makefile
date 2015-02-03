# $FreeBSD$

PORTNAME=	ShellCheck
PORTVERSION=	0.3.5
CATEGORIES=	devel haskell

MAINTAINER=	luca.pizzamiglio@gmail.com
COMMENT=	Shell scripts static analyzer

LICENSE=	AGPLv3

USE_GITHUB=	yes
GH_ACCOUNT=	koalaman
GH_TAGNAME=	v0.3.5
GH_COMMIT=	c5479b8
GH_PROJECT=	shellcheck

WRKSRC=	${WRKDIR}/${PORTNAME}-${PORTVERSION}

USE_CABAL=	cabal-install json>=0.7 regex-posix>=0.95.2 \
		regex-compat>=0.95.1 tf-random>=0.5 QuickCheck>=2.6

EXECUTABLE=	shellcheck

.include "${.CURDIR}/../../lang/ghc/bsd.cabal.mk"
.include <bsd.port.mk>
