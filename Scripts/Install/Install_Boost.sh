#!/bin/bash

Apt_Get()
{
 echo "In Apt_Get();"

sudo apt-get update
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev

}

Download_Boost()
{

BOOST_PATH="./Installs/Boost/"
mkdir $BOOST_PATH;
cd $BOOST_PATH;
#wget  http://softlayer-dal.dl.sourceforge.net/project/boost/boost/1.54.0/boost_1_54_0.tar.gz .

echo "UnCompressing boost_1_54_0.tar.gz"
#tar -xzf  boost_1_54_0.tar.gz

cd boost_1_54_0
}

Make_Install()
{
./bootstrap.sh --prefix=/usr/local/Boost-1.54.0
sudo ./b2 --with=all install
sudo ldconfig


}

Apt_Get;
Download_Boost;
Make_Install;


