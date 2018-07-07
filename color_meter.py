import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2
import sys
#import freenect
font = cv2.FONT_HERSHEY_SIMPLEX


def region_of_interest(img, vertices):
    """
    Applies an image mask.
    
    Only keeps the region of the image defined by the polygon
    formed from `vertices`. The rest of the image is set to black.
    """
    #defining a blank mask to start with
    mask = np.zeros_like(img)   
    
    #defining a 3 channel or 1 channel color to fill the mask with depending on the input image
    if len(img.shape) > 2:
        channel_count = img.shape[2]  # i.e. 3 or 4 depending on your image
        ignore_mask_color = (255,) * channel_count
    else:
        ignore_mask_color = 255
        
    #filling pixels inside the polygon defined by "vertices" with the fill color    
    cv2.fillPoly(mask, vertices, ignore_mask_color)
    #plt.figure()
    #plt.imshow(mask)
    #returning the image only where mask pixels are nonzero
    masked_image = cv2.bitwise_and(img, mask)
    return masked_image


def mouse_callback(event,x,y,flags,param):
	r = img[y][x][2]
	g = img[y][x][1]
	b = img[y][x][0]
	h = hsv[y][x][0]
	s = hsv[y][x][1]
	v = hsv[y][x][2]
	output_rgb = "R:{}, G:{}, B:{} ".format(r, g, b)
	output_hsv = "H:{}, S:{}, V:{}".format (h, s, v)
	tmp = img.copy()
	cv2.putText(tmp,output_rgb, (10,20), font, 0.5, (0,0,0))
	cv2.putText(tmp,output_hsv, (10,40), font, 0.5, (0,0,0))
	cv2.imshow('window', tmp)
	if event == cv2.EVENT_LBUTTONDOWN:
		print ("bgr: ({}, {}, {}) \nhsv: ({}, {}, {})".format(b,g,r,h,s,v))

cv2.namedWindow("window",1)
img = cv2.imread('test.png')
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
cv2.imshow('window', img)
cv2.setMouseCallback("window",mouse_callback)
ch = 0xFF & cv2.waitKey(10)
while True:
	ch = 0xFF & cv2.waitKey(10)
	if ch == 27:
		break
		cv2.destroyAllWindows()
