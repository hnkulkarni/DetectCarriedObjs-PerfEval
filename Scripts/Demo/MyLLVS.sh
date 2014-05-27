#!/bin/bash

VideoFldr="/s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/temp"

for VideoFile in $VideoFldr/*
do
    echo "Running LLVS for $VideoFile"

    ParentDir=`dirname  $VideoFile`
    DataFldr=$ParentDir/data
    mkdir $DataFldr

    LLVS="/s/parsons/h/proj/vision/usr/hrushi/MindsEye/svn/LLVS2/trunk/src/LLVS"
    $LLVS -m training $VideoFile $DataFldr

    mkdir $DataFldr/mask
    mv $DataFldr/mask* $DataFldr/mask
    mv $DataFldr/mask $ParentDir

    mkdir $DataFldr/track
    mv $DataFldr/t* $DataFldr/track
    mv $DataFldr/track $ParentDir	
done
