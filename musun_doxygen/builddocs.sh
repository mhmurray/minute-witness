#!/bin/bash

basedir=/home/michael/minute-witness/musun_doxygen
cd $basedir

echo "Skipping update of cvs"
#thisdir=`pwd`
#cd sourcecode
#cvs -d /home/cvs/musun/cvsroot update -d || exit 1
#cd $thisdir

echo "Removing old html directory"
if [ -d html ]; then
  rm -rf html
fi

echo "Running doxygen. See output in doxygen.log"
doxygen MuSunAnalysisCode.cfg 2>&1 > doxygen.log

status=$?

if [ ! $status ]; then
  echo "Doxygen build failed!"
  exit 1
fi

echo "Skipping Copying to web directory"
#rm -rf /var/www/exp/MuSun/doxygen/*
#cp -r html/* /var/www/exp/MuSun/doxygen/

echo "opening in browser"
xdg-open html/index.html
