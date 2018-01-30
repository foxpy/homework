def hop_across(stones): 
    return distance(stones) + distance(stones[::-1])


def distance(stones):
    steps, stone = 0, 0
    while stone < len(stones):
        stone += stones[stone]
        steps += 1
    return steps

