#!/usr/bin/python
# Copyright 2017 BIG VISION LLC ALL RIGHTS RESERVED
#
# This code is made available to the students of
# the online course titled "Computer Vision for Faces"
# by Satya Mallick for personal non-commercial use.
#
# Sharing this code is strictly prohibited without written
# permission from Big Vision LLC.
#
# For licensing and other inquiries, please email
# spmallick@bigvisionllc.com
#

import dlib,cv2
import os 
import re
#from renderFace import renderFace
#from renderFace import renderFace2

def writeLandmarksToFile(landmarks, landmarksFileName):
    #os.remove(landmarksFileName)
    with open(landmarksFileName, 'w') as f:
        for p in landmarks.parts():
            f.write("%s %s\n" %(int(p.x),int(p.y)))

    f.close()

def LandMarkDetector(predictorPath,  imageFilename):
    # Landmark model location
    # Get the face detector
    faceDetector = dlib.get_frontal_face_detector()
    # The landmark detector is implemented in the shape_predictor class
    landmarkDetector = dlib.shape_predictor(predictorPath)

    # Read image
    im= cv2.imread(imageFilename)
    # landmarks will be stored in results/family_i.txt
    landmarksBasename = re.findall(r'(.*?).jpg',imageFilename)
    pos = imageFilename.rfind('/');
    path = imageFilename[:pos]
    fileName = imageFilename[pos+1:]
    pos = fileName.rfind('.')
    timeStamp = fileName[:pos]
    #print('Landmark Path = {} file Name = {}'.format(path, fileName))

    # Detect faces in the image
    faceRects = faceDetector(im, 0)
    print("Number of faces detected: ",len(faceRects))
    
    # Process only the images with 1 face.
    if len(faceRects) != 1:
        return
   
    # List to store landmarks of all detected faces
    landmarksAll = []

    # Loop over all detected face rectangles
    i = 0
    newRect = dlib.rectangle(int(faceRects[i].left()),int(faceRects[i].top()), int(faceRects[i].right()),int(faceRects[i].bottom()))

    # For every face rectangle, run landmarkDetector
    landmarks = landmarkDetector(im, newRect)
    # Print number of landmarks
    if i==0:
        print("Number of landmarks",len(landmarks.parts()))

    # Store landmarks for current face
    landmarksAll.append(landmarks)

    #landmarksFileName = landmarksBasename[0] +".txt"
    landmarksFileName = path + '/landmarks/' + timeStamp +".txt" 
    #print("Saving landmarks to", landmarksFileName)
    writeLandmarksToFile(landmarks, landmarksFileName)
    return 
