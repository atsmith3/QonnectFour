import cv2
import numpy as np
import pdb

# Bounds: H 0-180 S 0-255 V 0-255

blue_lower = np.array([100,130, 100])
blue_upper = np.array([110,255, 255])

def hsv_filt(frame, lower_bounds, upper_bounds, wrap_bounds=False):
  hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

  if wrap_bounds:
    # Wrap the bounds around the 180 HSV discontinuity
    lowside = cv2.inRange(hsv,
                    np.array([0,lower_bounds[1],lower_bounds[2]]),
                    np.array([lower_bounds[0],upper_bounds[1],upper_bounds[2]]))
    highside = cv2.inRange(hsv, 
                    np.array([upper_bounds[0],lower_bounds[1],lower_bounds[2]]),
                    np.array([180, upper_bounds[1], upper_bounds[2]]))
    binframe = cv2.bitwise_or(lowside, highside)
  else:
    binframe = cv2.inRange(hsv, lower_bounds, upper_bounds)
  return binframe

def drawLines(image, lines, thickness=1):
  for line in lines:
    # print("line="+str(line))
    cv2.line(image, (line[0], line[1]), (line[2], line[3]),
             (0, 0, 255), thickness)

def split_hierarchy(hierarchy):
  level2_idxs = np.where(hierarchy[:,:,3]!=-1)[1]
  level1_idxs = np.where(hierarchy[:,:,3]==-1)[1]
  return level1_idxs, level2_idxs

def process_image(mat, image_id=1):
  #cv2.imshow('Test '+str(image_id), mat)
  frame_regions = hsv_filt(mat, blue_lower, blue_upper)
  frame_regions = cv2.morphologyEx(frame_regions, cv2.MORPH_OPEN, cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5)))
  cv2.imshow('Filt '+str(image_id), frame_regions)
  contours, hierarchy = cv2.findContours(frame_regions, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE)
  l1, l2 = split_hierarchy(hierarchy)
  cnt_img = mat.copy()
  # Find all the contours that define the spaces where a piece can be
  spaces_contours = [contours[i] for i in l2]
  # Filter out noisy contours
  filtered_contours = []
  filtered_centers = []
  for i in xrange(len(spaces_contours)):
    ((x,y),(w,h),ang) = cv2.minAreaRect(spaces_contours[i])
    (x,y),radius = cv2.minEnclosingCircle(spaces_contours[i])
    if max(w,h)/min(w,h) < 1.6 and 600<=cv2.contourArea(spaces_contours[i])<=1800:
      filtered_contours.append(spaces_contours[i])
      filtered_centers.append((x,y))
    
  # Build up the grid of contour centers
  centers = np.zeros((6,7,2))
  row_sorted = sorted(filtered_centers, key=lambda pt: pt[1])
  for row in xrange(5):
    column_sorted = sorted(row_sorted[row*7:(row+1)*7], key=lambda pt: pt[0])
    for col in xrange(7):
      centers[row,col,0] = column_sorted[col][0]
      centers[row,col,1] = column_sorted[col][1]
  # Add the bottom row
  for col in xrange(7):
    centers[5,col,0] = (2*centers[4,col,0])-centers[3,col,0]
    centers[5,col,1] = (2*centers[4,col,1])-centers[3,col,1]  
  
  # Draw the contours
  cv2.drawContours(cnt_img, filtered_contours, -1, (0,255,0), 3)
  # Show the grid centers
  for row in xrange(6):
    for col in xrange(7):
      cv2.circle(cnt_img, (int(centers[row,col,0]),int(centers[row,col,1])), 5, (255,0,0), 3)
  cv2.imshow('Contours '+str(image_id), cnt_img)
  game_state = None
  return game_state

if __name__=="__main__":
  test1 = cv2.imread("../test_images/test1.jpg")
  test1 = cv2.resize(test1,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_LINEAR)
  test2 = cv2.imread("../test_images/test2.jpg")
  test2 = cv2.resize(test2,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_LINEAR)
  process_image(test1,1)
  process_image(test2,2)
  while cv2.waitKey(0)!=27:
    pass
  cv2.destroyAllWindows()
