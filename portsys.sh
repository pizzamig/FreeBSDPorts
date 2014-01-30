#!/usr/bin/env bash

CAT="AUDIO DEVEL TEXTPROC"
AUDIO="ctronome" # ksmp3play # timidity++ timidity++-emacs timidity++-motif timidity++-slang timidity++-tcltk timidity++-xaw timidity++-xskin
BENCHMARK="" # nbench unixbench sysbench libmicro
DATABASES="" # akonadi-googledata
DEVEL="gdb" # cross-gdb bcpp
GAMES="" # xlife doom conquest
MATH="ndiff"
MULTIMEDIA="" # oggvideotools
SYSUTILS="" # kdirstat backupme
TEXTPROC="kdiff3"

SVNURL="https://svn0.eu.FreeBSD.org/ports/head"
REDURL="https://svn.redports.org/pizzamig"
PORTS="${AUDIO} ${DEVEL} ${MATH} ${TEXTPROC}"

SVNBSDDIR=svnports
SVNREDPORT=redports

_getCat()
{
  local CATEGORY
  CATEGORY=""
  for p in $AUDIO; do
    if [ $p = $1 ]; then
      CATEGORY="audio"
    fi
  done
  for p in $DEVEL; do
    if [ $p = $1 ]; then
      CATEGORY="devel"
    fi
  done
  for p in $MATH; do
    if [ $p = $1 ]; then
      CATEGORY="math"
    fi
  done
  for p in $TEXTPROC; do
    if [ $p = $1 ]; then
      CATEGORY="textproc"
    fi
  done
  echo $CATEGORY
}

usage()
{
  echo 'portsys.sh [-hlsRc] [-i portname] [-I portname] [-p portname]'
  echo '	-h print this help'
  echo '	-l list available ports'
  echo '	-s prepare/co/update the freebsd svn repository for all ports'
  echo '	-R prepare/co/update the redports svn repository for all ports'
  echo '	-i install the git port to the freebsd svn'
  echo '	-I install the git port to the redports svn'
  echo '	-p create the patch/diff file to submit a PR'
  echo '	-c clean! remove svn local directories'
}

list()
{
  echo "Ports available:"
  for p in ${PORTS}; do
    echo "    * $p"
  done
}

_svn_up()
{
  local SVNDIR=${1:-$SVNBSDDIR}
  local URL=${2:-$SVNURL}
  [ ! -d ${SVNDIR} ] && mkdir ${SVNDIR}
  pushd ${SVNDIR}
  if [ "$3" = "root" ]; then
    svn co $URL/ .
  else
    for p in $PORTS; do
      local CAT=$(_getCat $p)
      if [ -d $CAT ]; then
	mkdir -p $CAT
      fi
      if [ -d $CAT/$p ]; then
	(cd $CAT/$p; svn up)
      else
	svn co $URL/$CAT/$p $CAT/$p
      fi
    done
  fi
  popd > /dev/null
}

cleansvn()
{
  [ -d ${SVNBSDDIR} ] && rm -rf ${SVNBSDDIR}
  [ -d ${SVNREDPORT} ] && rm -rf ${SVNREDPORT}
}

_git2svn()
{
  local CATEGORY
  CATEGORY=$(_getCat $1)

  [ -z ${CATEGORY} ] && echo "No category found for $1" && return
  [ ! -d $CATEGORY ] && echo "Directory ${CATEGORY} not found" && return
  [ ! -d $CATEGORY/$1 ] && echo "Directory $CATEGORY/$1 not found" && return
  [ ! -d ${2} ] && echo "Directory $2 not found" && return
  [ ! -d ${2}/$CATEGORY ] && echo "Directory ${2}/$CATEGORY not found" && return

  rsync -v -r --delete --exclude=.svn --exclude=.git $CATEGORY/$1 ${2}/$CATEGORY
}

_make_patch()
{
  local _PORT=${1}
  local _CATEGORY=$(_getCat ${_PORT})
  [ -z ${_PORT} ] && echo "No port" && return
  [ -z ${_CATEGORY} ] && echo "No category found for ${_PORT}" && return
  $( cd ${SVNBSDDIR}/${_CATEGORY}/${_PORT}; svn diff > ../../../port.diff )
}

args=$(getopt hlcsRi:I:p: $*)

if [ $? -ne 0 ]; then
  usage
  exit 2
fi
set -- $args

while true; do
  case "$1" in
  -h)
    usage
    exit 0;
    ;;
  -l)
    list
    shift
    ;;
  -i) # install to FreeBSD svn
    _git2svn $2 ${SVNBSDDIR}
    shift; shift;
    ;;
  -I) # install to Redports svn
    _git2svn $2 ${SVNREDPORT}
    shift; shift;
    ;;
  -s)
    _svn_up ${SVNBSDDIR} ${SVNURL}
    shift;
    ;;
  -R)
    _svn_up ${SVNREDPORT} ${REDURL} root
    shift;
    ;;
  -c)
    cleansvn
    shift;
    ;;
  -p)
    _make_patch $2
    shift; shift;
    ;;
  --)
    shift; break
    ;;
  esac
done

