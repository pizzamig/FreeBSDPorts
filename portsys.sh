#!/usr/local/bin/bash

CAT="AUDIO DEVEL"
AUDIO="ctronome timidity++ timidity++-emacs"
DEVEL="gdb"

SVNURL="https://svn0.eu.FreeBSD.org/ports/head"
PORTS="${AUDIO} ${DEVEL}"

SVNBSDDIR=svnports
SVNREDPORT=redports

usage()
{
  echo 'portsys.sh [-hl] [-i portname]'
  echo '	-h print this help'
  echo '	-l list available ports'
  echo '	-s prepare the svn '
  echo '	-i install the git port to the svn'
}

list()
{
  echo "Ports available:"
  for p in ${PORTS}; do
    echo "    * $p"
  done
}

getCat()
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
  echo $CATEGORY
}

svn_up()
{
  [ ! -d ${SVNBSDDIR} ] && mkdir ${SVNBSDDIR}
  pushd ${SVNBSDDIR}
  for p in $PORTS; do
    if [ -d $p ]; then
      (cd $p; svn up)
    else
      svn co $SVNURL/$(getCat $p)/$p $p
    fi
  done
  popd
}

git2svn()
{
  local CATEGORY
  CATEGORY=$(getCat $1)
  rsync -v -r --delete --exclude=.svn --exclude=.git $CATEGORY/$1 svnports
}

args=$(getopt hsli: $*)

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
  -i) # install
    git2svn $2 
    shift; shift;
    ;;
  -s)
    svn_up
    shift;
    ;;
  --)
    shift; break
    ;;
  esac
done

