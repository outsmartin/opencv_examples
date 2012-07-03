#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2.cv as cv
from cv import *
import os

def cut(disparity, image, threshold):
    for i in range(0, image.height):
        for j in range(0, image.width):
        # keep closer object
            if cv.GetReal2D(disparity,i,j) > threshold:
                cv.Set2D(disparity,i,j,cv.Get2D(image,i,j))

if __name__ == '__main__':
    import sys

    # loading the stereo pair
    left  = cv.LoadImage('Raum10-2.bmp',cv.CV_LOAD_IMAGE_GRAYSCALE)
    right = cv.LoadImage('Raum10-1.bmp',cv.CV_LOAD_IMAGE_GRAYSCALE)
    #left  = cv.LoadImage('Raum01-2.bmp',cv.CV_LOAD_IMAGE_GRAYSCALE)
    #right = cv.LoadImage('Raum01-1.bmp',cv.CV_LOAD_IMAGE_GRAYSCALE)

    disparity_left  = cv.CreateMat(left.height, left.width, cv.CV_16S)
    disparity_right = cv.CreateMat(left.height, left.width, cv.CV_16S)

    # data structure initialization
    state = cv.CreateStereoGCState(16,2)
    # running the graph-cut algorithm
    print "finding"
    cv.FindStereoCorrespondenceGC(left,right,disparity_left,disparity_right,state)
    print "found"

    disp_left_visual = cv.CreateMat(left.height, left.width, cv.CV_8U)
    cv.ConvertScale( disparity_left, disp_left_visual, -16 );
    cv.Save( "disparity.pgm", disp_left_visual ); # save the map

    # cutting the object farthest of a threshold (120)
    print "cutting"
    cut(disp_left_visual,left,120)

    cv.NamedWindow('Disparity map', cv.CV_WINDOW_AUTOSIZE)
    cv.ShowImage('Disparity map', disp_left_visual)
    cv.WaitKey()
