edges=[
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

g = { i: dict() for i in range(num_vertex)}
for u,v,w in edges:
    g[u][v] =
    g[v][u] =

mst = []
def append(s, e, w):
    if s <= e:
        mst.append((s,e,w))
    else:
        mst.append((e,s,w))
    mst.sort(key=lambda e:e[0]*1000+e[1])

from heapdict import heapdict

def prim(start):
    D = heapdict()
    D[start] = (0, start) # D[출발점] = (가중치, 출발점)
    while D:
        index_to, (weight, index_from) = D.popitem()
        if index_from != index_to:
            append(index_from, index_to, weight)
        for adj_index, adj_weight in g[index_to].items()


prim(8)

print(mst)

