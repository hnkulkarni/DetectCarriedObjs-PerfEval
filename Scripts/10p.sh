#!/bin/bash

# -------------------------------------------------
# Author	: Hrushikesh N. Kulkarni
# Date		: 
# Description	: Copies 10 percent of the folder to the destination
# Arguments	: 
# Arg1: Source Folder
# Arg2: Destination Folder
# -------------------------------------------------

function Copy()
{
    SrcFldr=$1
    DestFldr=$2
    
    for Cpy in $(find $SrcFldr -maxdepth 1 -type f | sort | head -n 50 ); do
   
    echo "Listing files $Cpy "
        if [[ ! -d $Cpy ]]; then
            echo "Copying $Cpy --> $DestFldr"
            cp $Cpy $DestFldr      
        fi
    done
}


function traverse() 
{   
    for file in $(ls "$1")
    do
        #current=${1}{$file}
        if [[ -d ${1}/${file} ]]; then
            RecFldr=${1}/${file}
            FromRoot=`echo $RecFldr | cut -d '/' -f3-`
            ToFldr=$FromRoot
            
            echo "entering recursion with: $RecFldr $ToFldr"
            
            MakeDir.sh $ToFldr
            
            Copy $RecFldr $ToFldr
            
            traverse "$RecFldr" 
        fi
    done
}

function main() {
    traverse "$1" 
}

#SrcFldr=../MyPETS
#main $SrcFldr "./"

main $1 $2
