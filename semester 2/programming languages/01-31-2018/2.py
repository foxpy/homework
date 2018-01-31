def age(x, y):
    if y != 1: return x+x/(y-1)
    raise ValueError("Their age shouldn't be equal.")

