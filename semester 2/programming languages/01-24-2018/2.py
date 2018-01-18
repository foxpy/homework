def third_angle(first_angle, second_angle):
    if 0 < first_angle < 180 and 0 < second_angle < 180:
        return 180 - (first_angle + second_angle)
    else:
        raise ValueError("Not a triangle.")

