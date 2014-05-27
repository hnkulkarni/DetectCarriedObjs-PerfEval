#!/bin/bash

# -------------------------------------------------
# Author	    : Hrushikesh N. Kulkarni
# Date		    : Aug 19, 2013
# Description	: Builds a Test and Train set from the 'track' images in the folder
# Arguments	    : 1. Source Folder Name

# Sample Call	: ./MakeSets.sh ../../../../Datasets/MindsEye ../../../../Datasets/DARPA_IMG_SET
# -------------------------------------------------

ListArgs()
{
echo "Arg: 1/$# : Src  Folder: $1"
echo "Arg: 2/$# : Dest Folder: $2"
}


MakeDirectory()
{
    Path=$1;
    echo "MakeDir: $Path";

    if [ ! -d "${Path}" ]; then
        mkdir $Path
    fi
}

CopyFiles()
{
	
	echo "In Copy Files";
	
    TrainPath_track=$2/track;
    MakeDirectory $TrainPath_track;
    
    TestPath_track=$3/track;
    MakeDirectory $TestPath_track;
    
    TrainPath_mask=$2/mask;
    MakeDirectory $TrainPath_mask;
    
    TestPath_mask=$3/mask;
    MakeDirectory $TestPath_mask;
    
    count=0;
    
    for Imgs in `find $1/track/ -maxdepth 1 -mindepth 1 -type f`; do

    rem=$(( $count % 2 ))
    ImageName=`basename $Imgs`;
    MaskImgName=$1/mask/mask_$ImageName;
 
    if [ $rem -eq 0 ]; then #Semicolon is most important for Executing if-else
        echo "$Imgs => $TrainPath_track"
        cp $Imgs $TrainPath_track
        cp $MaskImgName $TrainPath_mask
        
    else
        echo "$Imgs => $TestPath_track"
        cp $Imgs $TestPath_track
		cp $MaskImgName $TestPath_mask
    fi

    count=$((count+1))
        
    done

}


CopyFolder()
{
	
	echo "In CopyFolder: $1";
	
    for VideoFolderPath in `find $1 -maxdepth 1 -mindepth 1 -type d` ; do
      
        echo $VideoFolderPath
        VideoName=`basename $VideoFolderPath`
        
        DestTrain=$2/$VideoName;
        MakeDirectory $DestTrain;
        
        DestTest=$3/$VideoName;
        MakeDirectory $DestTest;
        
        CopyFiles $VideoFolderPath  $DestTrain $DestTest
    done
}


DestRootFolderPath=$2
MakeDirectory $DestRootFolderPath;
    
DestTrainPath=$DestRootFolderPath/train;
MakeDirectory $DestTrainPath

DestTestPath=$DestRootFolderPath/test;
MakeDirectory $DestTestPath;

for Fldr in `find $1 -maxdepth 1 -mindepth 1 -type d` ; do

    FolderName=`basename $Fldr`;    
    echo $FolderName;
    
    DestTrainFolderPath=$DestTrainPath/$FolderName
    MakeDirectory $DestTrainFolderPath;
    
    DestTestFolderPath=$DestTestPath/$FolderName
    MakeDirectory $DestTestFolderPath;    
    
    CopyFolder $Fldr $DestTrainFolderPath $DestTestFolderPath;
    
done


exit $?

