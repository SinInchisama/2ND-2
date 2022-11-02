class City:
  def __init__(self, name, x, y, index=0):
    self.name = name
    self.x, self.y = x, y
    self.index = index
  def __repr__(self):
    return f'{self.name}({self.index}:{self.x:3d},{self.y:3d})'

cities = [
  City("Swing", 1113, 156, 21),
  City("Merry", 1002, 231, 22),
  City("Brine", 431, 53, 23),
  City("Miter", 126, 609, 24),
  City("Withy", 936, 432, 25),
  City("Brink", 1336, 404, 26),
  City("Madly", 1487, 104, 27),
  City("Spicy", 130, 498, 28),
  City("Cleft", 425, 506, 29),
  City("Cheep", 1511, 604, 30),
  City("Grief", 659, 683, 31),
  City("Links", 529, 850, 32),
  City("Write", 1345, 271, 33),
  City("Fixed", 434, 772, 34),
  City("Yobbo", 920, 848, 35),
  City("Grave", 868, 577, 36),
  City("Cress", 869, 678, 37),
  City("Ensue", 1209, 877, 38),
  City("Imply", 1544, 390, 39),
  City("Datum", 796, 235, 40),
  City("Quoit", 1281, 379, 41),
]

import math

def distance(c1,c2):
   return math.sqrt((c1.x - c2.x) ** 2 + (c1.y - c2.y) **2)

def closest_of_three(array,start,end):   #end = inclusive
    d1 = distance(array[start],array[start + 1])    # 첫번째 도시 두번째 도시를 넘겨주고
    d2 = distance(array[start],array[start + 2])
    d3 = distance(array[start + 1],array[start + 2])

    if d1 <= d2 and d1 <= d3:
        return start,start + 1,d1
    if d2 < d3:
        return start,start + 2, d2
    return start + 1,start + 2, d3

def closest_pair(array,start,end):      #end = inclusive
    size = end - start + 1
    if size <= 1:
        print(f'Bug? Size is <= 1: {size}')
        exit(0)
    if size == 2:
        return start,end,distance(array[start],array[end])
    if size == 3:
        return closest_of_three(array,start,end)

    last_left = (start + end) // 2

    ls,le,ld = closest_pair(array,start,last_left)
    rs,re,rd = closest_pair(array,  last_left, end)

    s,e,d = (ls,le,ld) if ld<= rd else rs,re,rd

    x1 = array[last_left].x - d
    x2 = array[last_left].x + d

    # strip = []
    # for i in range(start,end + 1):
    #     c = cities[i]
    #     if x1 <= c.x <= x2:
    #         strip.append(c)
    # strip.sort(key = lambda  c:c.y)

    #2nd
    # strip = [c for c in cities[start:end + 1]if x1 <= c.x and c.x<=x2]
    # strip.sort(key=lambda c: c.y)

    #3nd
    # strip = [c for c in cities if x1 <= c.x and c.x <= x2 and c.index >= start and c.index<=end]
    # strip.sort(key = lambda c:c.y)

    # 4th
    i1 = min(c.index for c in cities if x1 <= c.x and start <= c.index)
    i2 = max(c.index for c in cities if c.x <= x2 and c.index<= end)
    # strip = cities[i1:i2+1]
    # strip.sort(key = lambda  c: c.y)

    strip = [c for c in cities_y if i1 <= c.index and c.index <= i2]

    n_strip = len(strip)
    for i1 in range(n_strip):
        c1 = strip[i1]
        for i2 in range(i1 + 1,n_strip):
            c2 = strip[i2]
            dy = c2.y - c1.y
            if dy > d:
                break;
            dd = math.sqrt((c1.x - c2.x) ** 2 + dy ** 2)
            if dd < d:
                s,e,d = c1.index,c2.index,dd

    return s,e,d

print(cities)
cities.sort(key=lambda c:c.x)
for i in range(len(cities)):
    cities[i].index = i

cities_y = sorted(cities,key=lambda c: c.y)

s, e, d = closest_pair(cities,0,len(cities) - 1)     # 끝을 포함하기로 했으니 -1
# s, e, d = closest_of_three(cities,0,len(cities) - 1)     # 끝을 포함하기로 했으니 -1
print(f'{cities[s]} ~ {cities[e]} : {d:.1f}')