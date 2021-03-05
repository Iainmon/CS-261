f = open('large.txt', 'w')
for i in range(10000):
    f.write(f'{i} ')
f.close()