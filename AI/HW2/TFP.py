import numpy as np 
from sklearn.metrics.pairwise import euclidean_distances
import math
import random
from random import shuffle
import matplotlib.pyplot as plt
from tqdm.notebook import tqdm
from itertools import permutations


#Count total distance
def TtotalDistance(Route0):
    distance = sum([distmap[Route0[i],Route0[i+1]] for i in range(len(Route0)-1)])
    return distance
    
#Method of Exhaustive
def exhaustive(Route0):
    Route1 = Route0
    special_start = []
    permutDis = []
    eveans = list(permutations(Route1, 11))
    for i in range(len(eveans)):
        if eveans[i][0] == Route0[0] and eveans[i][-1] == Route0[-1]:
            special_start.append(eveans[i])
    for i in range(len(special_start)):
        dis = TtotalDistance(special_start[i])
        permutDis.append(dis)
    smallest_distance = min(permutDis)
    arr = permutDis.index(smallest_distance)
    smallest_route = special_start[arr]
    return smallest_route, smallest_distance

def Inversion(Route0,time):
    Copy = Route0.copy()
    place  = random.sample([1,2,3,4,5,6,7,8,9],2)
    Copy[place[0]],Copy[place[1]] = Copy[place[1]],Copy[place[0]]
    return Copy

#Random generate a route
Route0 = random.sample(range(0, 10), 10)
Route0.append(Route0[0]) 
total_distance = TtotalDistance(Route0)
print('Initial Route: ', Route0)
print('Initial distance: ', total_distance)
print('===============================================')
print('By using method of exhustive, can get the min distance below: ')
print("Smallest num by exhaustive: ",exhaustive(Route0))

#Parameter
t0 = 500    #Initial temperature
tmin = 0.1  #End of iteration, which means minimum temperature
k = 40      #Iteration in every temperature steps
N = 10.     #Number of cities
coolnum = 0.98

distmap = np.zeros((N,N))
for i in range(N):
    for j in range(i,N):
        if i<j:
            distmap[i][j] = random.randint(10,50)
            distmap[j][i] = distmap[i][j]

evetime_distance = []
evetime_route = []

t = t0

while True:
    if t <= tmin:
        break
    for times in range(k):
        new_Route = Inversion(Route0,i)
        new_distance = TtotalDistance(new_Route)
        diff = new_distance - total_distance
        if diff <= 0:
            Route0 = new_Route
            total_distance = new_distance
        else:
            prob = math.exp(-diff/t)
            randnum = random.uniform(0,1)
            if randnum < prob:
                Route0 = new_Route
                total_distance = new_distance
            else:
                Route0 = Route0
                total_distance = total_distance
    evetime_route.append(Route0)
    evetime_distance.append(total_distance)
    t = t * coolnum

print('Final Route: ',evetime_route[-1])
print('Final Distance: ',evetime_distance[-1])

plt.figure(figsize = (15,8))
plt.xlabel("Iteration",fontsize = 15)
plt.ylabel("Distance",fontsize = 15)

plt.plot(evetime_distance,linewidth = 2.5, label = "Everytime smallest distance", color = 'r')
plt.legend()
plt.show()