#!/bin/bash

# Copies the mask file from Som's Folder to the destination folder. The mask chip
# has the same name as that of the track, but with a 'mask_' at the begining. 

#*********************************************************************
# Function Name	: Main Bash Scrip
# Date 		: Feb 11, 2013
# Author	: hrushi
# Comments	: This is the main script which does all the legwork
# Args		: None
#**********************************************************************/
DatasetFolder="/s/chopin/l/grad/hrushi/MyCodes/Research/Datasets/Test/"
ScriptPath=`pwd`
cd $DatasetFolder

#For Pos or Neg folder, which contians positive and negative samples
for DataSetType in $DatasetFolder*; do 
  if [ -d "${DataSetType}" ]; then
    	cd $DataSetType
	
	#For all the Folders corresponding to Video Files
	for VideoFolderPath in $DataSetType/*; do
	    if [ -d "${VideoFolderPath}" ]; then
		cd $VideoFolderPath;
		VideoFolderName=`basename $VideoFolderPath`

		   for TM in $VideoFolderPath/*; do
		      if [ -d "${TM}" ]; then			  
                      TMName=`basename $TM`
                      CMPName="track" 
		         if [ $TMName = $CMPName ]; then
                           echo "TM" $TM
			   echo "VideoFolderName " $VideoFolderName
			   $ScriptPath/CopyMask.sh $TM $VideoFolderName
		         fi
		      fi
		   done
	    fi	
	done
  fi
done


