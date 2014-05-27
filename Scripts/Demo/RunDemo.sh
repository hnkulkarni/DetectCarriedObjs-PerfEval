#!/bin/bash

#Run.sh
# Created on: Dec 8, 2013 
#     Author: hrushi
#       Args: Runs the demo


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
	
ssh hrushi@eggs.cs.colostate.edu 'bash -s' < MyLLVS.sh
			
}



DisplayArgs $@
VISION_TEMP="/s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/temp"
VIDEO_FILE_PATH=$1

ParentDir=`dirname  $VIDEO_FILE_PATH`

scp $VIDEO_FILE_PATH hrushi@yam.cs.colostate.edu:$VISION_TEMP

vidName=`basename $VIDEO_FILE_PATH`;
VidStemName="${vidName%%.*}"

echo "RunLLVS $VISION_TEMP/$vidName "
RunLLVS 

rsync --recursive --progress --quiet hrushi@yam.cs.colostate.edu:$VISION_TEMP/track $ParentDir
rsync --recursive --progress --quiet hrushi@yam.cs.colostate.edu:$VISION_TEMP/mask $ParentDir

ssh hrushi@eggs.cs.colostate.edu << 'ENDSSH'
cd /s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/temp
cd ..
rm -rf temp
mkdir temp
ENDSSH
 
cd ../../

make -j 4

./DetectCarriedObjs  --demo  --training_data_path /home/hrushi/Videos/Demo/train  --input_run_folder $ParentDir  --track_folder_name track --mask_folder_name mask --mode $2


