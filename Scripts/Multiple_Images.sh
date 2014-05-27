#!/bin/bash

# -----------------------------------------------------------------------------
# Author	: Hrushikesh N. Kulkarni
# Date		: 
# Description	: This script performs Labelling for the given dataset
# Arguments	: Arg 1: File Path to the given dataset. 
#                        Example: ../../../Datasets/Pets2006/train ../../../Datasets/Pets2006/test 
#                                   ../../../Datasets/DARPA_IMG_SET/train
#             Arg 2: Mode 
#                           Example: pose
#                                    location
# -----------------------------------------------------------------------------

echo "Performing Labelling"
cd ..

NUM_CORES=`nproc`;

CORES_FOR_MAKE=$(echo "$NUM_CORES - 1" | bc)

make -j $CORES_FOR_MAKE;

echo "./DetectCarriedObjs --multiple_images --training_data_path $1 --input_run_folder $2 --track_folder_name track --mask_folder_name mask --mode $3"
./DetectCarriedObjs --multiple_images --training_data_path $1 --input_run_folder $2 --track_folder_name track --mask_folder_name mask --mode $3| tee Log.txt

# ../ is added to make the paths relative to the script. 
cd ./Scripts
./PlotFigs.sh ../$1

exit $?
