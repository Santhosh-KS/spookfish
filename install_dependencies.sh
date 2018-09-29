#!/bin/sh
#   MIT License
#
#   Copyright (c) 2018 santhoshachar08@gmail.com
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.


sudo apt-get install g++-5 build-essential checkinstall cmake pkg-config yasm git  gfortran
sudo apt-get install libqt5opengl5 libqt5opengl5-dev libtiff4-dev libjpeg8-dev libjasper-dev libpng12-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev 
sudo apt-get install libv4l-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev 
sudo apt-get install qt5-default qttools5-dev qttools5-dev-tools libgtk2.0-dev libtbb-dev libatlas-base-dev 
sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev 
sudo apt-get install libopencore-amrwb-dev x264 v4l-utils python3.5 python3.5-dev python-dev python-numpy 
sudo apt-get install libtbb2 libjpeg-dev libpng-dev libtiff-dev libboost-all-dev

sudo pip3 install pafy youtube-dl


#build and install Opencv

mkdir -p /opt
cd /opt
sudo git clone https://github.com/opencv/opencv.git
sudo git clone https://github.com/opencv/opencv_contrib.git
sudo cd opencv_contrib
sudo git checkout 3.3.1
sudo cd /opt/opencv
sudo git checkout 3.3.1
sudo mkdir build
cd build
sudo cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON  -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
sudo make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
source ~/.bashrc

# Install Dlib
cd /opt
sudo git clone https://github.com/davisking/dlib.git dlib

# Install Rapid Json.
cd /opt
git clone https://github.com/Tencent/rapidjson.git

# Build and Install Wt
cd /opt
sudo wget https://github.com/emweb/wt/archive/4.0.4.tar.gz
sudo tar -xvzf 4.0.4.tar.gz
cd /opt/wt-4.0.4
sudo mkdir -p /opt/wt-4.0.4/build
cd /opt/wt-4.0.4/build
sudo cmake ..
sudo make -j4
sudo make install
