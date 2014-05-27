#!/bin/bash


sudo apt-get update
sudo apt-get upgrade


#-----------------------------------------------------
# Install Subversion default is 1.6.
#-----------------------------------------------------
sudo apt-get install subversion -y
sudo apt-add-repository ppa:dominik-stadler/subversion-1.7 -y
sudo apt-get update
sudo apt-get upgrade

# Upgrade distribution
sudo apt-get dist-upgrade

# Install again
sudo apt-get install subversion -y

#-----------------------------------------------------
# Install version to have "Open in Terminal" in nautilus
#-----------------------------------------------------
sudo apt-get install nautilus-open-terminal -y

#------------------------------------------------------
# Install g++
#------------------------------------------------------
sudo apt-get install g++ -y

#------------------------------------------------------
# Install Gimp
#------------------------------------------------------
sudo apt-get install gimp -y

#------------------------------------------------------
# Install Inkscape
#------------------------------------------------------
sudo apt-get install inkscape -y

#------------------------------------------------------
# Install Wine
#------------------------------------------------------
sudo apt-get install wine -y

#------------------------------------------------------
# Install GNU_Plot
#------------------------------------------------------
sudo apt-get install gnuplot -y


