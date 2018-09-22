#!/bin/sh

#sudo mkdir -p /opt/spookfish/
cd /tmp
git clone https://github.com/Santhosh-KS/ImageStorage.git ImageStorage
cp -r /tmp/images/* /tmp/ImageStorage

cd /tmp/ImageStorage
git add *
git commit -m "Images committed"
git push origin master

#git config --global credential.helper cache

