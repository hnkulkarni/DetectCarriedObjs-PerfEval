#!/bin/bash

Apt_Get()
{
sudo apt-get install cmake -y

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen2-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev -y

#Install the GTK dev library
sudo apt-get -y install  libgtk2.0-dev

#Install Video I/O libraries
sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev

#Optional - install support for Firewire video cameras
sudo apt-get -y install libdc1394-22-dev

#Optional - install video streaming libraries?
sudo apt-get -y install libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev

#Optional - install the Python development environment and the Python Numerical library
sudo apt-get -y install python-dev python-numpy

#Optional - install the parallel code processing library (the Intel tbb library)
sudo apt-get -y install libtbb-dev

#Optional - install the Qt dev library
sudo apt-get -y install libqt4-dev

sudo apt-get install build-essential
}

Apt_Get;

Download_OpenCV()
{
wget  http://softlayer-dal.dl.sourceforge.net/project/opencvlibrary/opencv-unix/2.4.6.1/opencv-2.4.6.1.tar.gz .

echo "UnCompressing opencv-2.4.6.1.tar.gz"
tar -xzf  opencv-2.4.6.1.tar.gz
}


Download_OpenCV;

cd ./Installs/opencv-2.4.6.1
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local/OpenCV-2.4.6 -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON .. 

cd ..
make 

sudo make install
