f = open('large.txt', 'w')
for i in range(10000000):
    f.write(f'{i} ')
f.close()