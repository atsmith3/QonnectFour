import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2
import sys
font = cv2.FONT_HERSHEY_SIMPLEX


class Detector:
	def __init__(self):
		self.lower_yellow = np.array([20,130,230])   #good
		self.upper_yellow = np.array([40,255,255])
		self.lower_red = np.array([175,150,100]) # good
		self.upper_red = np.array([185,230,220])
		self.ceneter_location = []

	def region_of_interest(self, img, vertices):
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
	def find_location(self, color, image_name, a = 0., a2 = 1., b = 0., b2 = 1.):
		image = cv2.imread(image_name)
		clean_image = cv2.imread(image_name)
		imshape = image.shape
		hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
		vertices = np.array([[(int(a*imshape[1]),b*imshape[0]),(int(a*imshape[1]), int(b2*imshape[0])), (int(a2*imshape[1]), int(b2*imshape[0])),(int(a2*imshape[1]),b*imshape[0])]], dtype=np.int32)
		kernel = np.ones((17,17),np.uint8)

		if color == 'yellow':
			mask = cv2.inRange(hsv, self.lower_yellow, self.upper_yellow)
			mask_p = cv2.dilate(mask, kernel, iterations = 1)
			block = self.region_of_interest(mask_p,vertices)
		if color == 'red':
			mask = cv2.inRange(hsv, self.lower_red, self.upper_red)
			mask_p = cv2.dilate(mask, kernel,iterations = 1)
			block = self.region_of_interest(mask_p,vertices)
		_, contours, hierarchy = cv2.findContours(block,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
		contour_list = []
		for contour in contours:
			area = cv2.contourArea(contour)
			if area > 5000 :
				contour_list.append(contour)

		for contour in contour_list:
		    tt = cv2.moments(contour)
		    cx_p = int(tt['m10']/tt['m00'])
		    cy_p = int(tt['m01']/tt['m00'])
		    offset = 0
		    edage_vertices = np.array([[(cx_p-offset,cy_p-offset),(cx_p-offset,cy_p+offset),(cx_p+offset,cy_p+offset),(cx_p+offset,cy_p-offset)]], dtype=np.int32)
		    cv2.circle(clean_image, (cx_p,cy_p), 10, (0, 500, 100), -1)
		    self.ceneter_location.append(np.array([cx_p, cy_p]))

		cv2.namedWindow("markedraw",2)
		cv2.imshow('markedraw',clean_image)

	def show_center(self):
		print ('blob locations are : {}'.format(self.ceneter_location))
		


detector = Detector()
detector.find_location('red','test.png', a = 0., a2 = 1., b = 0., b2 = 1.)
detector.show_center()
while True:
			ch = 0xFF & cv2.waitKey(10)
			if ch == 27:
				break
				cv2.destroyAllWindows()
		   

