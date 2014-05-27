#!/bin/bash

# -------------------------------------------------
# Author	: Hrushikesh N. Kulkarni
# Date		: Sept 9, 2013
# Description	: This file plots all the EM information
# Arguments	: Arg 1: Directory containing all the EM Files
#                        Example: ../../../../Datasets/Pets2006/train
#                                   ../../../../Datasets/DARPA_IMG_SET/train

# -------------------------------------------------

MakePlot()
{
ARM_NAME=$1;
FILE_PATH=$2;

PLOT_FILE_PATH="$FILE_PATH/$ARM_NAME.eps";
echo $PLOT_FILE_PATH;

CARRY="Carry_EM";
NOCARRY="NoCarry_EM";
gnuplot << EOF
set terminal postscript eps color enhanced
set output "$PLOT_FILE_PATH"
set xlabel "Cosine of Carry Angle"
set ylabel "Carry Dist in Pixels"
set grid xtics ytics
plot	"$FILE_PATH/$ARM_NAME$CARRY.dat" using 1:2 title '$ARM_NAME - $CARRY' with points ,\
		"$FILE_PATH/$ARM_NAME$CARRY.dat" using 1:2:3 w labels offset 1 notitle, \
		"$FILE_PATH/$ARM_NAME$NOCARRY.dat" using 1:2 title "$ARM_NAME - $NOCARRY" with points,\
		"$FILE_PATH/$ARM_NAME$NOCARRY.dat" using 1:2:3 w labels offset 1 notitle

EOF
}

for ARM in Right Left; do

MakePlot $ARM $1;

done;





