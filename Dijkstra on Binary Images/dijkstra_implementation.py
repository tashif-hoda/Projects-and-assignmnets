# -*- coding: utf-8 -*-
"""
Created on Thu Apr 23 19:59:26 2020

@author: tashif
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt
import heapq
import sys
#my own dijkstra implenetation might have been right!!!
path = "binary_image_sample_1.png"
img = cv2.imread(path, 0)
#---Sample numpy array for testing---
# img = np.array([[255, 255, 255, 255, 255],
#                 [255, 255, 255, 255, 255],
#                 [255,   0,   0,   0, 255],
#                 [255, 255, 255, 255, 255],
#                 [255, 255, 255, 255, 255]], np.uint8)
# scale = 50 # times original size
# width = int(img.shape[1] * scale)
# height = int(img.shape[0] * scale)
# dim = (width, height)
# resize image
# img = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
#---Actual Logic below---

#Inverting image, adding 1 and converting to float 64 to increase weight
img_inv = np.invert(img)
img_inv[img_inv==0]+=1
img_inv = np.array(img_inv, np.float64)
img_inv[img_inv==255] = float('inf')

#Add mouse click input for start and target
start = (467, 67)
target = (66, 369)

height, width = img.shape

#utility function to verify if an index is valid
def inBounds(i, j):
    return (i >= 0 and i<height and j>=0 and j<width)

#utility function to trace and draw the shortest path on the image
def drawPath(dis, start, target):
    # dx = [-1, 0, 1, 0]
    # dy = [0, 1, 0, -1]
    
    dx = [-1, 0, 1, 0, -1, 1, 1, -1]
    dy = [0, -1, 0, 1, -1, -1, 1, 1]
    
    md = float('inf')
    # next_node=[target]
    while start!=target:
        p, q = target
        for i in range(len(dx)):
            x = p+dx[i]
            y = q+dy[i]
            if dis[x, y] < md:
                md = dis[x,y]
                target = (x,y)
        img[target[0], target[1]]=127
        print(target, dis[target[0], target[1]])
        
#dijkstra's algorithm
def dijkstra(inv, start, target):
    dist = np.zeros(inv.shape)#distance array
    dist[dist==0]=float('inf')
    i,j = start
    dist[i, j]=1
    
    dx = [-1, -1, 0, 1, 1, 1, 0, -1]
    dy = [0, 1, 1, 1, 0, -1, -1, -1]
    
    heap = [[0,i,j]]
    
    dist[i,j] = inv[i,j]
    
    while heap:
        temp = heapq.heappop(heap)
        for i in range(8):
            x = temp[1]+dx[i]
            y = temp[2]+dy[i]
            
            if not inBounds(x,y): continue
            
            if dist[temp[1], temp[2]] + inv[x,y] < dist[x, y]:
                if dist[x,y]!= float('inf'):
                    idx = heap.index([dist[x,y], x, y])
                    heap[idx] = heap[-1]
                    heap.pop()
                    heapq.heapify(heap)
                    
                dist[x,y] = dist[temp[1], temp[2]] + inv[x, y]
                heapq.heappush(heap, [dist[x, y], x, y])
    drawPath(dist, start, target)
    return dist[target[0], target[1]]

print(dijkstra(img_inv, start, target))

cv2.imshow("binary image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()