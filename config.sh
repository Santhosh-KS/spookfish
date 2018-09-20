#!/bin/sh

sudo mkdir -p /opt/spookfish
sudo mkdir -p /opt/spookfish/scripts
sudo cp ./data/shape_predictor_68_face_landmarks.dat /opt/spookfish
sudo cp ./data/shape_predictor_5_face_landmarks.dat  /opt/spookfish
sudo cp ./data/dlib_face_recognition_resnet_model_v1.dat /opt/spookfish
sudo cp -r ../scripts/* /opt/spookfish/scripts

mkdir -p /tmp/images/

sudo mkdir -p /opt/spookfish/ImageStorage
sudo git clone https://github.com/Santhosh-KS/ImageStorage.git /opt/spookfish/ImageStorage
