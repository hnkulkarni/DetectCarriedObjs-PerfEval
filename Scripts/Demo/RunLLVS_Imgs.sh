#!/bin/bash

#RunImgs.sh
# Created on: Nov 23, 2013 12:45:24 PM
#     Author: hrushi
#       Args: 1. Folder containing all the videos
# Runs the sorts the images in to different folder and then runs LLVS on them.
#./RunImgs.sh /s/parsons/h/proj/vision/usr/hrushi/DataSets/AI_Lab/



#----------------------------------------------
# Write all the functions over here
#----------------------------------------------


#Display Args:  1 2 '3 4', group arguments by single quotes
DisplayArgs()
{
	echo "Args Passed are"
	if [ $# -eq 1 ]; then
	    echo "Argument are passed to shell script"
	    	for arg in "$@"
			do
				echo "$arg"
			done
	else
	    echo "No arguments are passed to shell script"
	fi
	
}


RunLLVS()
{
		
VideoFile=$1
echo "Running LLVS for $VideoFile"

ParentDir=`dirname  $VideoFile`
DataFldr=$ParentDir/data
LLVS="/s/parsons/h/proj/vision/usr/hrushi/MindsEye/svn/LLVS2/trunk/src/LLVS"
$LLVS -m training $VideoFile $DataFldr

./MakeDir.sh $DataFldr/mask
mv $DataFldr/mask* $DataFldr/mask
mv $DataFldr/mask $ParentDir

./MakeDir.sh $DataFldr/track
mv $DataFldr/t* $DataFldr/track
mv $DataFldr/track $ParentDir	
			
}

Move()
{
	$vidPath=$1
	CarryType=$2
	
	vidName=`basename $vidPath`;
	VidBaseName="${vidName%%.*}"
	
	ParentPath=`dirname $vidPath`
	
	# Make folder for each video
	FldrName="$2_$VidBaseName"
	./MakeDir.sh $ParentPath/$FldrName
	./MakeDir.sh $ParentPath/$FldrName/data
	
	FromPath=$vidPath
	echo "From: $FromPath"
	
	ToPath=$ParentPath/$FldrName/$2_$VidBaseName$EXT
	echo "To: $ToPath"
		
	mv $FromPath $ToPath
	
	RunLLVS $ToPath
	
}

MoveNRun()
{
	echo "Copy videos in the folders"
	echo "Work Folder: $1"
	
	EXT=".MOV"
	$CarryMode=$2
	
	for vidPath in $1/*
	do
		echo $vidPath
		
		if [ -f $vidPath ]; then
    	Move $vidPath $CarryMode
		else
			
			#Run if the Data folder is present
			if [ -d $vidPath/data ]; then
		    	echo "Its a directory" 	    	
    		   	RunLLVS $vidPath/*$EXT													
			fi
		fi
	done;
}




#----------------------------------------------
# Code starts Here
#----------------------------------------------

#Make folders for every file in the base name.
DisplayArgs $@

for SetFolder in $1/*
do
	echo "Sorting on $SetFolder"		
	CarryMode=`basename $SetFolder`;
	MoveNRun $SetFolder $CarryMode
done



