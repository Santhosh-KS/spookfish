#!/bin/sh

sudo mkdir -p /opt/spookfish/
cd /opt/spookfish/
#sudo git clone https://github.com/Santhosh-KS/ImageStorage.git
sudo cp -r /tmp/images/* /opt/spookfish/ImageStorage

cd /opt/spookfish/ImageStorage
sudo git add *
sudo git commit -m "Images committed"
sudo git push origin master

#git config --global credential.helper cache

