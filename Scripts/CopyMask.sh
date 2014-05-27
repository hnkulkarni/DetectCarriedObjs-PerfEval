#!/bin/bash
# Copies the mask file from Som's Folder to the destination folder. The mask chip
# has the same name as that of the track, but with a 'mask_' at the begining. 

#./CopyMask.sh ../../../../Datasets/MindsEye/neg /s/parsons/h/proj/vision/usr/som/MaskChips

echo $1
echo $2

for Fldr in `find $1 -maxdepth 1 -mindepth 1 -type d` ; do
    
    FldrName=`basename $Fldr`;
    TrackFldrPath=$1/$FldrName/track;
    MaskFldrPath=$1/$FldrName/mask;   

    SrcFolderName=$2/$FldrName;
    
    if [ ! -d "${MaskFldrPath}" ]; then
    mkdir $MaskFldrPath
    fi
    
    for FilePath in `ls $TrackFldrPath/*.png`; do
 	
 	FileName=`basename $FilePath`;
	MaskFileName="mask_$FileName";

	SourcePath=$SrcFolderName/$MaskFileName;
	cp $SourcePath $MaskFldrPath
		    
    done
    
done


