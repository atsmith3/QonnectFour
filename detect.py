import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import cv2
import sys
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


def canny(img, low_threshold, high_threshold):
    """Applies the Canny transform"""
    return cv2.Canny(img, low_threshold, high_threshold)
def gaussian_blur(img, kernel_size):
    """Applies a Gaussian Noise kernel"""
    return cv2.GaussianBlur(img, (kernel_size, kernel_size), 0)
def hough_lines(img, rho, theta, threshold, min_line_len, max_line_gap):
    
    lines = cv2.HoughLinesP(img, rho, theta, threshold, np.array([]), minLineLength=min_line_len, maxLineGap=max_line_gap)
        
    return lines

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

if len(sys.argv) == 2:
	print("Opening " + str(sys.argv[1]))
	img = cv2.imread(sys.argv[1])
	hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	cv2.namedWindow("window",1)
	cv2.imshow('window', img)
	cv2.setMouseCallback("window",mouse_callback)
	while True:
		ch = 0xFF & cv2.waitKey(10)
		if ch == 27:
			break
			cv2.destroyAllWindows()
else:
	print("Expected filename as argument")



#####################################################################################

image = cv2.imread('test.png')
clean_image = cv2.imread('test.png')
#image2 = cv2.imread('ex0_bgr.png')
#image = cv2.imread('test_images/frame2.png')
#image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)


gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
kernal_size = 5
blured_gray = gaussian_blur(gray,kernal_size)
low_threshold = 100
high_threshold = 250
edges = canny(blured_gray,low_threshold,high_threshold)


lower_yellow = np.array([20,130,230])   #good
upper_yellow = np.array([40,255,255])


lower_orrange = np.array([0,160,170]) # good
upper_orrange = np.array([15,255,255])

lower_pink = np.array([165,85,175])  #good
upper_pink = np.array([175,205,255])

lower_red = np.array([175,150,100]) # good
upper_red = np.array([185,230,220])

lower_blue = np.array([110,100,125]) # good
upper_blue = np.array([120,200,200])

lower_green = np.array([50,40,90])  #good
upper_green = np.array([70,110,160])

lower_purple = np.array([150,95,85]) #good
upper_purple = np.array([165,150,140])

lower_black = np.array([0,0,0])
upper_black = np.array([180,255,85])

lower_black_2 = np.array([0,0,60])
upper_black_2 = np.array([180,255,90])

imshape = image.shape

a = 0.0
a2 = 1.
b = 1.
b2 = 0.
vertices = np.array([[(int(a*imshape[1]),b*imshape[0]),(int(a*imshape[1]), int(b2*imshape[0])), (int(a2*imshape[1]), int(b2*imshape[0])),(int(a2*imshape[1]),b*imshape[0])]], dtype=np.int32)
   

kernel = np.ones((17,17),np.uint8)

mask_yellow = cv2.inRange(hsv, lower_yellow, upper_yellow)
mask_yellow_p = cv2.dilate(mask_yellow, kernel,iterations = 1)
mask_yellow_s = cv2.GaussianBlur(mask_yellow_p,(15,15),0)
yellow_block = region_of_interest(mask_yellow_p,vertices)



mask_red = cv2.inRange(hsv, lower_red, upper_red)
#cv2.dilate(img,kernel,iterations = 1)
#mask_red_p = cv2.morphologyEx(mask_red, cv2.MORPH_CLOSE, kernel)
mask_red_p = cv2.dilate(mask_red, kernel,iterations = 1)
mask_red_s = cv2.GaussianBlur(mask_red_p,(7,7),0)
red_block = region_of_interest(mask_red_p,vertices)


cv2.namedWindow("red",2)
cv2.imshow('red', red_block)


yellow_centers = []
red_centers = []


contour_list_yellow = []
_, contours_yellow, hierarchy = cv2.findContours(yellow_block,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
for contour in contours_yellow:
	area = cv2.contourArea(contour)
	if area > 5000 :
		contour_list_yellow.append(contour)


contour_list_red = []
_, contours_red, hierarchy = cv2.findContours(red_block,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
for contour in contours_red:
	area = cv2.contourArea(contour)
	if area > 5000 :
		contour_list_red.append(contour)

cv2.drawContours(image, contour_list_red,  -1, (255,0,0), 2)
rho = 2 # distance resolution in pixels of the Hough grid
theta = np.pi/180 # angular resolution in radians of the Hough grid
threshold = 50     # minimum number of votes (intersections in Hough grid cell)
min_line_len = 20   #minimum number of pixels making up a line
max_line_gap = 45    # maximum gap in pixels between connectable line segments
   
print ('Found {} yellow blobs'.format(len(contour_list_red)))
for contour in contour_list_red:
	#print(p)
    tt = cv2.moments(contour)
    #print(tt['m01'],tt['m00'])
    cx_p = int(tt['m10']/tt['m00'])
    cy_p = int(tt['m01']/tt['m00'])
    offset = 0
    print(cx_p)
    print(cy_p)
    edage_vertices = np.array([[(cx_p-offset,cy_p-offset),(cx_p-offset,cy_p+offset),(cx_p+offset,cy_p+offset),(cx_p+offset,cy_p-offset)]], dtype=np.int32)
    masked_edges = region_of_interest(edges, edage_vertices)
    #print(cy_p)
    cv2.circle(clean_image, (cx_p,cy_p), 10, (0, 500, 100), -1)
    cv2.circle(clean_image, (cx_p,cy_p), 10, (0, 500, 100), -1)

    

cv2.namedWindow("markedraw",2)
cv2.imshow('markedraw',clean_image)


while True:
		ch = 0xFF & cv2.waitKey(10)
		if ch == 27:
			break
			cv2.destroyAllWindows()


