import math

fi = open('p067_triangle.txt', 'r')
raw_rows = fi.readlines()

class Node:
    __init__(self, value, right = None, left = None, parent = None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

h = 0
rows = []
for row in raw_rows:
    nums = row.rstrip().split(' ')
    rows.append(([int(n) for n in nums], h))
    h += 1

connected_rows = []

# for i in range(len(rows)-1):
#     # if i > 5:
#     #     break
#     ns, h   = rows[i]
#     cns, ch = rows[i+1]
#     k = 0
#     tripples = []
#     for j in range(len(ns)):
#         if k+1 >= len(cns)-1: break
#         tripple = [k, k+1, ns[j], (i,j)] # (left location, right location, parent, parent index)
#         tripples.append(tripple)
#         k += 2
#     print(tripples)
#     connected_rows.append(tripples)


# for i in range(len(connected_rows)):
#     idx = len(connected_rows) - i - 1
#     for j in range(len(connected_rows[idx])):
#         lhs_k, rhs_k, par, (pari,parj) = connected_rows[idx][j] # starts at child
#         print(i, j, pari, lhs_k, rhs_k)
#         _, _, lhs, _ = connected_rows[pari][lhs_k]
#         _, _, rhs, _ = connected_rows[pari][rhs_k]
#         max_sum = max(lhs, rhs) + par # node's max sum
#         connected_rows[pari][parj] = [lhs_k, lhs_k, max_sum, (pari,parj)]

# use connected node list to construct tree

for i in range(len(rows)-1):
    # if i > 5:
    #     break
    ns, h   = rows[i]
    cns, ch = rows[i+1]
    k = 0
    nodes = []
    for j in range(len(ns)):
        if k+1 >= len(cns)-1: break
        node = Node(cns[k], cns[k+1], connected_rows[i][j], (i,j)) # (left location, right location, parent, parent index)
        nodes.append(node)
        k += 2
    print(tripples)
    connected_rows.append(nodes)


for i in range(len(connected_rows)):
    idx = len(connected_rows) - i - 1
    for j in range(len(connected_rows[idx])):
        lhs_k, rhs_k, par, (pari,parj) = connected_rows[idx][j] # starts at child
        print(i, j, pari, lhs_k, rhs_k)
        _, _, lhs, _ = connected_rows[pari][lhs_k]
        _, _, rhs, _ = connected_rows[pari][rhs_k]
        max_sum = max(lhs, rhs) + par # node's max sum
        connected_rows[pari][parj] = [lhs_k, lhs_k, max_sum, (pari,parj)]
