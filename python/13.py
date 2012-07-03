#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2.cv as cv
from cv import *
import sys

if __name__ == '__main__':
    image = LoadImage(sys.argv[1])
    #for fname in ("Blatt1.JPG",  "Blatt2.JPG",  "Blatt3.JPG",  "Blatt4.JPG",  "Blatt5.JPG",  "Blatt6.JPG",  "Blatt7.JPG",  "Blatt8.JPG",  "Blatt9.JPG"):
    for fname in ("Blatt10.bmp",  "Blatt11.bmp",  "Blatt12.bmp",  "Blatt13.bmp",  "Blatt14.bmp", "Blatt16.JPG", "Blatt17.JPG", "Blatt18.JPG", "Blatt19.JPG"):
        template = LoadImage(fname)
        W, H = GetSize(image)
        w, h = GetSize(template)

        width = W - w + 1
        height = H - h + 1

        result = CreateImage((width, height), 32, 1)

        method = CV_TM_SQDIFF_NORMED

        MatchTemplate(image, template, result, method)

        (minVal, maxVal, minLoc, maxloc) = MinMaxLoc(result)
        (x, y) = minLoc

        if method  == CV_TM_SQDIFF or method == CV_TM_SQDIFF_NORMED:
            matchLoc = minLoc
        else:
            matchLoc = maxLoc

        print result
        print "x=", x
        print "y=", y
        print "minVal=", minVal
        print "maxVal=", maxVal
        print "minLoc=", minLoc
        print "maxloc=", maxloc
        NamedWindow('image', cv.CV_WINDOW_AUTOSIZE)
        Rectangle(image, (matchLoc[0], matchLoc[1]), (matchLoc[0] + w, matchLoc[1] + h), cv.CV_RGB(255, 0, 0), 1)
    ShowImage('image', image)
    WaitKey()

