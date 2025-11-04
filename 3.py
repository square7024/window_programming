edges = [
    (0, 3, 288), (0, 16, 390), (0, 21, 346), (1, 4, 449), (1, 7, 346),
    (1, 13, 325), (2, 21, 335), (3, 6, 231), (3, 11, 437), (3, 17, 140),
    (3, 18, 325), (3, 19, 362), (3, 20, 323), (4, 7, 457), (4, 10, 234),
    (4, 15, 399), (5, 7, 101), (5, 10, 445), (5, 12, 261), (5, 13, 234),
    (5, 21, 364), (6, 19, 304), (6, 20, 461), (7, 12, 362), (7, 13, 288),
    (7, 21, 445), (8, 9, 230), (8, 22, 365), (9, 18, 154), (9, 22, 191),
    (10, 21, 433), (11, 15, 381), (11, 17, 400), (11, 20, 113), (12, 15, 402),
    (12, 21, 260), (14, 15, 320), (14, 19, 454), (14, 20, 326), (15, 17, 453),
    (15, 19, 243), (15, 20, 394), (16, 17, 308), (16, 18, 214), (17, 21, 430),
    (18, 22, 262), (19, 20, 318), (19, 21, 391)
]
num_vertex = 23

g = {i: dict() for i in range(num_vertex)}
for u, v, w in edges:
    g[u][v] = w
    g[v][u] = w

mst = []


def append(s, e, w):
    if s <= e:
        mst.append((s, e, w))
    else:
        mst.append((e, s, w))
    mst.sort(key=lambda e: e[0] * 1000 + e[1])


from heapdict import heapdict


def dijkstra(start):
    D = heapdict()
    D[start] = (0, start)  # D[출발점] = (가중치, 출발점), origins가 있기 때문에 가중치만 저장해도 상관X(다만 그에따른 코드수정 필요)
    completed = set()
    global origins
    origins = dict() # 어디서 왔는지 저장할 dict

    while D:
        index_to, (weight, index_from) = D.popitem()
        completed.add(index_to)
        origins[index_to] = index_from

        if index_from != index_to:
            append(index_from, index_to, weight)

        for adj_index, adj_weight in g[index_to].items():
            if adj_index in completed: continue
            w = weight + adj_weight
            if not adj_index in D or D[adj_index][0] > w: # or 앞뒤 순서 주의!(앞이 참이면 뒤가 넘어감)
                D[adj_index] = (w, index_to)


dijkstra(12)


def path_to(index):
    o = origins[index]
    if o == index: return str(o), 0
    path, cost = path_to(o)
    return f'{path}-{index}', cost + g[index][o]

for index_to in range(num_vertex):
    path, cost = path_to(index_to)
    print(f'{path} ({cost})')

# print(mst)
