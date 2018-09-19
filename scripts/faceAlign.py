#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2012, Philipp Wagner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of the author nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import sys, math 
import os
import glob
from argparse import ArgumentParser
from landmark.facialLandmarkDetector import LandMarkDetector


#from PIL.Image import core as Image 

from PIL import Image 
def Distance(p1,p2):
  dx = p2[0] - p1[0]
  dy = p2[1] - p1[1]
  return math.sqrt(dx*dx+dy*dy)

def ScaleRotateTranslate(image, angle, center = None, new_center = None, scale = None, resample=Image.BICUBIC):
  if (scale is None) and (center is None):
    return image.rotate(angle=angle, resample=resample)
  nx,ny = x,y = center
  sx=sy=1.0
  if new_center:
    (nx,ny) = new_center
  if scale:
    (sx,sy) = (scale, scale)
  cosine = math.cos(angle)
  sine = math.sin(angle)
  a = cosine/sx
  b = sine/sx
  c = x-nx*a-ny*b
  d = -sine/sy
  e = cosine/sy
  f = y-nx*d-ny*e
  return image.transform(image.size, Image.AFFINE, (a,b,c,d,e,f), resample=resample)

def CropFace(image, eye_left=(0,0), eye_right=(0,0), offset_pct=(0.2,0.2), dest_sz = (70,70)):
  # calculate offsets in original image
  offset_h = math.floor(float(offset_pct[0])*dest_sz[0])
  offset_v = math.floor(float(offset_pct[1])*dest_sz[1])
  # get the direction
  eye_direction = (eye_right[0] - eye_left[0], eye_right[1] - eye_left[1])
  # calc rotation angle in radians
  rotation = -math.atan2(float(eye_direction[1]),float(eye_direction[0]))
  # distance between them
  dist = Distance(eye_left, eye_right)
  # calculate the reference eye-width
  reference = dest_sz[0] - 2.0*offset_h
  # scale factor
  scale = float(dist)/float(reference)
  # rotate original around the left eye
  image = ScaleRotateTranslate(image, center=eye_left, angle=rotation)
  # crop the rotated image
  crop_xy = (eye_left[0] - scale*offset_h, eye_left[1] - scale*offset_v)
  crop_size = (dest_sz[0]*scale, dest_sz[1]*scale)
  image = image.crop((int(crop_xy[0]), int(crop_xy[1]), int(crop_xy[0]+crop_size[0]), int(crop_xy[1]+crop_size[1])))
  # resize it
  image = image.resize(dest_sz, Image.ANTIALIAS)
  return image

import re

def ProcessImage(imageFile): 
  print(imageFile)
  image =  Image.open(imageFile)
  pos = imageFile.rfind("/");
  path = imageFile[:pos]
  fileName = imageFile[pos+1:]
  pos = fileName.rfind('.')
  timeStamp = fileName[:pos]
  #print('PATH = {} File Name = {} timeStamp = {}'.format(path, fileName, timeStamp))
  filePath = re.findall(r'(.*?).jpg', imageFile)
  #landMarkFile = filePath[0]+'.txt'
  landMarkFile = path + '/landmarks/' + timeStamp +'.txt'
  exists = os.path.isfile(landMarkFile)
  if exists:
    lines = [line.rstrip('\n') for line in open(landMarkFile)]
    #print('1st line: {}'.format(lines[0]))
    #print('2nd line: {}'.format(lines[1]))
    eyeRight = lines[0].split(' ')
    eyeLeft = lines[2].split(' ')
    erx = int(eyeRight[0])
    ery = int(eyeRight[1])
    #print('erx = {} ery = {}'.format(erx,ery))
    elx = int(eyeLeft[0])
    ely = int(eyeLeft[1])
    #print('elx = {} ely = {}'.format(elx,ely))
    ''' 
    CropFace(image, eye_left=(elx,ely),
           eye_right=(erx,ery), offset_pct=(0.1,0.1),
           #dest_sz=(200,200)).save('test_10_10_200_200.jpg')
           dest_sz=(200,200)).save(str(filePath[0])+'_10_10_200_200.jpg')
    '''
    '''
    CropFace(image, eye_left=(elx,ely),
           eye_right=(erx,ery), offset_pct=(0.2,0.2),
           dest_sz=(200,200)).save(str(filePath[0])+'_20_20_200_200.jpg')
    '''
    '''
    CropFace(image, eye_left=(elx,ely),
           eye_right=(erx,ery), offset_pct=(0.3,0.3),
           dest_sz=(200,200)).save(str(filePath[0])+'_30_30_200_200.jpg')
    '''
    CropFace(image, eye_left=(elx,ely),
           eye_right=(erx,ery), offset_pct=(0.3,0.3),
           dest_sz=(200,200)).save(path + '/30/' + fileName)
    '''
    CropFace(image, eye_left=(elx,ely),
           eye_right=(erx,ery),
           #offset_pct=(0.2,0.2)).save('test_20_20_70_70.jpg')
           offset_pct=(0.2,0.2)).save(str(filePath[0])+'_20_20_70_70.jpg')
    '''
  else :
      print('file {} Not found'.format(landMarkFile))

def GetCommandLineArgs():
    parser = ArgumentParser()
    parser.add_argument("-p", "--path", dest="path",
                    help="Path to the image files.",
                    metavar="PATH")
    args = parser.parse_args()

    path =''

    if not args.path:
      print('Invalid Command aruguments.')
      print('Usage:') 
      print('"python path.py -h" for more details')
      exit()
    else:
      path = args.path


    return path

#path,filename = GetCommandLineArgs()

if __name__ == "__main__":
  #imgs = glob.glob('/home/santhosh/course/week9/data/images/faces/ema/*.jpg')
  path = GetCommandLineArgs()
  #imgs = glob.glob('/tmp/images/mPgZMaWFzsT60wat/1/*.jpg')
  imgs = glob.glob(path + '*.jpg')
  predictorPath = '/opt/spookfish/shape_predictor_5_face_landmarks.dat'
  for img in imgs:
    print(img)
    LandMarkDetector(predictorPath, img)
    ProcessImage(img)
