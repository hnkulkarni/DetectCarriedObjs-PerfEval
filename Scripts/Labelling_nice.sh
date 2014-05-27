#!/bin/bash

# -----------------------------------------------------------------------------
# Author	: Hrushikesh N. Kulkarni
# Date		: 
# Description	: This script performs Labelling for the given dataset
# Arguments	: Arg 1: File Path to the given dataset. 
#                        Example: ../../../Datasets/Pets2006/train
#                                   ../../../Datasets/DARPA_IMG_SET/train
# -----------------------------------------------------------------------------

echo "Performing Labelling"
cd ..

NUM_CORES=`nproc`;

CORES_FOR_MAKE=$(echo "$NUM_CORES - 1" | bc)

make -j $CORES_FOR_MAKE;

#./DetectCarriedObjs --label_images --skip_existing --input_run_folder $1 --track_folder_name track --mask_folder_name mask --now --quiet | tee Log.txt

THISHOST=$(hostname)
COMPUTEHOST="eggs"

if [[ "$THISHOST" == "$COMPUTEHOST" ]]
then
    echo "This is a compute host"
    ./DetectCarriedObjs --label_images --skip_existing --input_run_folder $1 --track_folder_name track --mask_folder_name mask --now --quiet | tee Log.txt
    
else
    echo "This is not a comute host"
    nice -n 19 ./DetectCarriedObjs --label_images --skip_existing --input_run_folder $1 --track_folder_name track --mask_folder_name mask --now --quiet | tee Log.txt
fi


exit $?
