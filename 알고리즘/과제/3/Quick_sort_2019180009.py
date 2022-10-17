import random

words = [
  'jingo', 'lf', 'log', 'non', 'lj', 'goo', 'hmg', 'joe', 'knell', 'minim',
  '2019180009', '김선빈',
  'infilling', 'liege', 'mo', 'o', 'goon', 'hg', 'legging', 'holm', 'enjoin', 'e',
  'mini', 'logging', 'kin', 'hen', 'logo', 'flee', 'inf', 'fog', 'knee', 'limn',
  'jingo', 'lf', 'log', 'non', 'lj', 'goo', 'hmg', 'joe', 'knell', 'minim',
  'menfolk', 'feel', 'mlle', 'ken', 'home', 'if', 'linen', 'ne', 'lo', 'knoll',
  'mime', 'ooh', 'nomen', 'hill', 'kohl', 'efl', 'offline', 'lee', 'king', 'legion',
  'one', 'hike', 'genome', 'neigh', 'lifelong', 'him', 'gigolo', 'fo', 'fe', 'ego',
  'mom', 'hi', 'fine', 'ni', 'ongoing', 'ho', 'noh', 'jog', 'lion', 'loin',
  'fill', 'm', 'nee', 'join', 'noggin', 'neon', 'none', 'hm', 'gi', 'hook',
  'ion', 'in', 'gen', 'mono', 'feign', 'look', 'hinge', 'moonie', 'nil', 'ginkgo',
  'kilo', 'fief', 'ikon', 'moon', 'long', 'hf', 'lifeline', 'lingo', 'mink', 'nigh',
  'k', 'killing', 'hoi', 'mongol', 'nikkei', 'ime', 'hoof', 'me', 'floe', 'omen',
  'jiff', 'mike', 'foe', 'ingoing', 'leg', 'kiln', 'fin', 'noel', 'niff', 'minion',
]

def insertionSort(start,end):
  for i in range(start + 1, end + 1):
    v = array[i] # i 위치의 v값이 주인공
    j = i -1 # v와 비교를 시작할 위치
    while start <= j and array[j] > v :
      array[j + 1] = array[j] # 오른쪽으로 밀어준다
      j -= 1
    array[j + 1] = v

from random import  *


def partition(start, end):
  ri = randint(start, end)
  array[start], array[ri] = array[ri], array[start]
  pv = array[start]

  p, q = start, end + 1
  while True:
    while True:
      p += 1
      if p > end or array[p] >= pv: break
      pass

    while True:
      q -= 1
      if q < start or array[q] <= pv: break
      pass

    if p >= q: break

    array[p], array[q] = array[q], array[p]

  array[start], array[q] = array[q], array[start]
  return q


def quickSort(start,end): #end = inclusive
  if end - start < 1: return
  if end <= 10: # size of this array <= 10
    insertionSort(start,end)
  else:
    pi = partition(start,end)
    quickSort(start,pi - 1)
    quickSort(pi + 1,end)



array = words

quickSort(0,len(array) - 1)
print(array)