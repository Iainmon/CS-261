def parallel(rlis):
    inv_sum = 0
    for r in rlis:
        inv_sum += r ** -1
    return inv_sum ** -1

