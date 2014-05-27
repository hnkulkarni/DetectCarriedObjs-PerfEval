#!/bin/bash

# -------------------------------------------------
# Author	    : Hrushikesh N. Kulkarni
# Date		    : Aug 19, 2013
# Description	: Updates SVN in all the folders. The advantage is that it does not touch the .project folder. So all the eclipse dependencies are happy.
# Arguments	    : 1. Source Folder Name

# Sample Call	: ./SVN_Update.sh ../
# -------------------------------------------------

cd ../

CURRENT_FOLDER=`pwd`

echo "`pwd`"
for Folder in `find . -maxdepth 1 -mindepth 1 -not -name ".s*"  -type d`; do
	
	cd $Folder;
	
	#Remove Temp Files
	rm -rf *~
	
	svn -q update;
	
	SVN_REVISION=`svn info | grep Revision`	
	
	echo "Updated $Folder , current $SVN_REVISION";
	
	cd $CURRENT_FOLDER
    
done

svn update Makefile;

make clean
make

exit $?

