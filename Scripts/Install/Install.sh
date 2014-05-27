#!/bin/bash

sudo apt-get install eclipse -y
sudo apt-get install texlive-full -y

#install dropbox
cd ~ && wget -O - "https://www.dropbox.com/download?plat=lnx.x86_64" | tar xzf -

~/.dropbox-dist/dropboxd

./Install_Editors.sh
./Install_Utils.sh
./Install_OpenCV.sh
