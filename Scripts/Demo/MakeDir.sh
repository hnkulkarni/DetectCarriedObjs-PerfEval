#!/bin/bash

#MakeDir.sh
# Created on: Nov 23, 2013 12:57:37 PM
#     Author: hrushi
#       Args: 

MakeDirectory()
{
    Path=$1;
    echo "MakeDir: $Path";

    if [ ! -d "${Path}" ]; then
        mkdir $Path
    fi
}

MakeDirectory $@