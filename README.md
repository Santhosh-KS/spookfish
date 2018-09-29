## About project Spookfish:

If You want to know about the motive behind this project please read [here](https://github.com/Santhosh-KS/spookfish/blob/master/cpp/doc/ProjectReport.md).

Here is the [quick demo](https://youtu.be/fslaO9itYE4) of the project.

## Current Build status:

| Build | Status |
| ------ | ------ |
| Beta |[![Build Status](https://travis-ci.org/Santhosh-KS/spookfish.svg?branch=master)](https://travis-ci.org/Santhosh-KS/spookfish)|


## Install the following dependencies.

If you are trying to run on a system without the prior Opencv or Dlib installation, You can simply run the script `install_dependencies.sh` and take a break and wait for the installations to complete. Or you can do it
manually. If you are trying run on an existing setup, I suggest you to install only the components which you need to install.


Please install the following list of dependencies. These installations are one time job to setup on a new machine.

    sudo apt-get install g++-5 build-essential checkinstall cmake pkg-config yasm git  gfortran
    sudo apt-get install libqt5opengl5 libqt5opengl5-dev libtiff4-dev libjpeg8-dev libjasper-dev libpng12-dev
    sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev 
    sudo apt-get install libv4l-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev 
    sudo apt-get install qt5-default qttools5-dev qttools5-dev-tools libgtk2.0-dev libtbb-dev libatlas-base-dev 
    sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev 
    sudo apt-get install libopencore-amrwb-dev x264 v4l-utils python3.5 python3.5-dev python-dev python-numpy 
    sudo apt-get install libtbb2 libjpeg-dev libpng-dev libtiff-dev libboost-all-dev
    sudo pip3 install pafy youtube-dl 
    
    
 ### Build and Install OpenCv:
    
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
    
 ### Build and Install Wt (Optional):
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
  
### How to build the Spookfish tool:
Once you successfully install the dependencies, you are all set to build the tool.

    git clone https://github.com/Santhosh-KS/spookfish.git
    cd spookfish/cpp
    ./analyser.sh
    ./Spookfish.sh

If you want to change the Wt user configuration like changing the `port number` or `docroot` just edit the following line in `Spookfish.sh` file. 
`./build/NewUiWt --docroot ./ui --http-address 0.0.0.0 --http-port 8080 `


