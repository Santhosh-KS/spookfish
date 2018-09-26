
| Build | Status |
| ------ | ------ |
| Beta |[![Build Status](https://travis-ci.org/Santhosh-KS/spookfish.svg?branch=master)](https://travis-ci.org/Santhosh-KS/spookfish)|

## Install the following dependencies.

Please install the following list dependencies. 

    sudo apt-get install g++-5 build-essential checkinstall cmake pkg-config yasm git  gfortran
    sudo apt-get install libqt5opengl5 libqt5opengl5-dev libtiff4-dev libjpeg8-dev libjasper-dev libpng12-dev
    sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev 
    sudo apt-get install libv4l-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev 
    sudo apt-get install qt5-default qttools5-dev qttools5-dev-tools libgtk2.0-dev libtbb-dev libatlas-base-dev 
    sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev 
    sudo apt-get install libopencore-amrwb-dev x264 v4l-utils python3.5 python3.5-dev python-dev python-numpy 
    sudo apt-get install libtbb2 libjpeg-dev libpng-dev libtiff-dev 
    
    
 ### Build OpenCv
    
    mkdir -p /opt
    cd /opt
    git clone https://github.com/opencv/opencv.git
    git clone https://github.com/opencv/opencv_contrib.git
    cd opencv_contrib
    git checkout 3.3.1
    cd /opt/opencv
    git checkout 3.3.1
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON  -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
    make -j4
    sudo make install
    sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
    sudo ldconfig
    source ~/.bashrc
 
 
 ### Install Dlib:
    cd /opt
    git clone https://github.com/davisking/dlib.git dlib
  
 ### Install RapidJson:
    cd /opt
    git clone https://github.com/Tencent/rapidjson.git
    
 ### Install Wt (Optional):
 Wt is optional. If you want to re-use the UI then this step is mandatory.
 
    cd /opt
    wget https://github.com/emweb/wt/archive/4.0.4.tar.gz
    tar -xvzf 4.0.4.tar.gz
    cd /opt/wt-4.0.4
    mkdir -p /opt/wt-4.0.4/build
    cd /opt/wt-4.0.4/build
    cmake ..
    make -j4
    sudo make install
  
