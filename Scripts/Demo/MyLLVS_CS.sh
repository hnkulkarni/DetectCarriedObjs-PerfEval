#!/bin/bash

VideoFldrMain="/s/parsons/h/proj/vision/usr/hrushi/DataSets/CS425"

LLVS="/s/parsons/h/proj/vision/usr/hrushi/MindsEye/svn/LLVS2/trunk/src/LLVS"

for VideoFldr in $VideoFldrMain/*
do
    echo "In $VideoFldr"
    
    DataDir=$VideoFldr/data
    ./MakeDir.sh $DataDir
    
    VideoFileName=$VideoFldr/*.MOV
    echo $VideoFileName
    
    $LLVS -m training $VideoFileName $DataDir
    
    ./MakeDir.sh $DataDir/mask
    mv $DataDir/mask_* $DataDir/mask
    mv $DataDir/mask $VideoFldr

    ./MakeDir.sh $DataDir/track
    mv $DataDir/t* $DataDir/track
    mv $DataDir/track $VideoFldr
    
    
    
done
