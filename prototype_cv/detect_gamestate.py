import cv2
import numpy as np

# Bounds: H 0-180 S 0-255 V 0-255

blue_lower = np.array([100,140, 100])
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



def process_image(mat):
  game_state = None

  return game_state

if __name__=="__main__":
  test1 = cv2.imread("../test_images/test1.jpg")
  test1 = cv2.resize(test1,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_LINEAR)
  cv2.imshow('Test 1', test1)
  cv2.imshow('Filt 1', hsv_filt(test1, blue_lower, blue_upper))
  test2 = cv2.imread("../test_images/test2.jpg")
  test2 = cv2.resize(test2,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_LINEAR)
  cv2.imshow('Test 2', test2)
  cv2.imshow('Filt 2', hsv_filt(test2, blue_lower, blue_upper))
  while cv2.waitKey(0)!=27:
    pass
  cv2.destroyAllWindows()
