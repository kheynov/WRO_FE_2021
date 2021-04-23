import cv2
import numpy as np

# im = cv2.imread('res/example.png')

# def nop(x):
#     pass

# def mouse_event(event, x, y, flags, params):
#     if event == cv2.EVENT_LBUTTONDBLCLK:
#         print(f'({x}, {y}) = {hsv[y][x]}')

# cv2.namedWindow('controls')
# cv2.createTrackbar('red_h_min', 'controls', 0, 255, nop)
# cv2.createTrackbar('red_h_max', 'controls', 0, 255, nop)
# cv2.createTrackbar('red_s_min', 'controls', 0, 255, nop)
# cv2.createTrackbar('red_s_max', 'controls', 0, 255, nop)
# cv2.createTrackbar('red_v_min', 'controls', 0, 255, nop)
# cv2.createTrackbar('red_v_max', 'controls', 0, 255, nop)
# cv2.setMouseCallback('im', mouse_event)

cap = cv2.VideoCapture(0)

def find_objects():
    _, im = cap.read()

    blurred = cv2.GaussianBlur(im, (9, 9), 0)
    hsv = cv2.cvtColor(im, cv2.COLOR_BGR2HSV)

    # red_mask_min = (cv2.getTrackbarPos('red_h_min', 'controls'), cv2.getTrackbarPos('red_s_min', 'controls'), cv2.getTrackbarPos('red_v_min', 'controls'))
    # red_mask_max = (cv2.getTrackbarPos('red_h_max', 'controls'), cv2.getTrackbarPos('red_s_max', 'controls'), cv2.getTrackbarPos('red_v_max', 'controls'))
    red_mask_min = (179-10, 0, 0)
    red_mask_max = (179+10, 255, 255)

    # green_mask_min = (69-10, 0, 0)
    # green_mask_max = (69+10, 255, 255)

    thresholded_red = cv2.inRange(hsv, red_mask_min, red_mask_max)
    # thresholded_green = cv2.inRange(hsv, green_mask_min, green_mask_max)

    resulting = im.copy()

    # contours_red, hierarchy_red = cv2.findContours(thresholded_red, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    # cv2.drawContours(resulting, contours_red, -1, (0,255,0), 3)
    # print(contours_red)

    # for cnt in contours_red:
    #     rect = cv2.minAreaRect(cnt)
    #     box = cv2.boxPoints(rect)
    #     box = np.int0(box)
    #     area = int(rect[1][0]*rect[1][1])
    #     if area > 100:
    #         cv2.drawContours(resulting,[box],0,(255,0,0),2)
    #         x1 = (box[1][0] + box[0][0]) / 2
    #         x2 = (box[2][0] + box[3][0]) / 2
    #         # y1 = (box[1][1] + box[2][1]) / 2
    #         # y2 = (box[0][1] + box[3][1]) / 2
    #         x = int((x1 + x2) / 2)
    #         # y = int((y1 + y2) / 2)
    #         cv2.line(resulting, (x, 0), (x, 500), (255, 0, 0), 2)

    # cv2.imshow('im', im)
    # cv2.imshow('blurred', blurred)
    cv2.imshow('red_mask', thresholded_red)
    # cv2.imshow('green_mask', thresholded_green)
    # cv2.imshow('resulting', resulting)


if __name__ == '__main__':
    while True:
        find_objects()

        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break
        cv2.destroyAllWindows()