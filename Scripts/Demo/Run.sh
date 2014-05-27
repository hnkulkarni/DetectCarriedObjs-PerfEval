#!/bin/bash

#Run.sh
# Created on: Nov 25, 2013 9:17:21 AM
#     Author: hrushi
#       Args: Folder containing all the mov files.

SCRIPT_PATH="`pwd`"


for fldr in $1
do

echo "Working on: $fldr"
#Run LLVS
./RunLLVS_Imgs.sh $fldr

#Run Matlab Pose Code

#ssh hrushi@eggs.cs.colostate.edu << 'ENDSSH'

#cd /s/chopin/l/grad/hrushi/Work/Research/Codes/Cpp/DetectCarriedObjs/Pose/PoseValidation/Scripts/

#`pwd`
#./RunMMJ2 $fldr .png
#ENDSSH


done






