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

./DetectCarriedObjs --label_images --skip_existing --input_run_folder $1 --track_folder_name track --mask_folder_name mask --now --quiet | tee Log.txt

# ../ is added to make the paths relative to the script. 
cd ./Scripts
./PlotFigs.sh ../$1

exit $?
