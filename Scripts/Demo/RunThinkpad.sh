#!/bin/bash

#Run.sh
# Created on: Nov 25, 2013 9:17:21 AM
#     Author: hrushi
#       Args: Folder containing all the mov files.



rsync --verbose --update --recursive --progress /home/hrushi/Videos/Demo/ hrushi@kelp.cs.colostate.edu:/s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/

ssh hrushi@kelp.cs.colostate.edu << 'ENDSSH'
cd /s/chopin/l/grad/hrushi/Work/Research/Codes/Cpp/DetectCarriedObjs/Scripts/Demo

`pwd`

./Run.sh /s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/train
./Run.sh /s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/test
ENDSSH

rsync --verbose --recursive --progress --update hrushi@kelp.cs.colostate.edu:/s/parsons/h/proj/vision/usr/hrushi/DataSets/Demo/ /home/hrushi/Videos/Demo



