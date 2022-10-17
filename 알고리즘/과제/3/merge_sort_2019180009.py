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

def mergeSort(start = 0,end = None): # end=Inclusive
  if end == None: end = len(words) - 1
  if end  - start < 1: return
  mid = (start + end) // 2 # mid is included in left part
  mergeSort(start, mid) #왼쪽
  mergeSort(mid + 1,end) #오른쪽
  merge(start,mid,end)


def merge(start, mid, end): #mid is in left, end = inclusive
  global words
  # 공간복잡도 = O(n)
  merged = []
  l, r = start, mid + 1 # 양 merge의 시작점을 넣어줌
  while (l <= mid and r <= end): # 모두 선수가 있을때까지
    if words[l] <= words[r]:
        merged += [words[l]]
        # merged.append(words[l])
        l += 1
    else:
        merged += [words[r]]
        r += 1
  if l <= mid:
    merged += words[l:mid + 1]
  elif r <= end:
    merged += words[r:end + 1]
  # print(merged,len(merged),start,mid,end)
  words[start:end + 1] = merged
  # merged가 완성되었음 -> words에 채워넣어야 한다.



print(words)
mergeSort(0,len(words) - 1)
print(words,len(words))