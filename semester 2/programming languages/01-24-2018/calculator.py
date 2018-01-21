from math import log


def addition(a, b):
    return a + b

def subtraction(a, b):
    return a - b

def multiplication(a, b):
    return a * b

def division(a, b, division_type=""):
    if division_type == "float":
        return a / b
    elif division_type == "remainder":
        return a % b
    else:
        return a // b

def logarithm(a, b):
    return log(a, b)

def power(a, b):
    return a ** b

def root(a, b=2):
    return a ** (1 / b)

