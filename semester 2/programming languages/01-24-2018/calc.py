def calc(a, b, action):
    if action == "add":
        return a + b
    elif action == "subtract":
        return a - b
    elif action == "multiply":
        return a * b
    elif action == "divide":
        return int(round(a / b, 0))
    elif action == "divide_float":
        return round(a / b, 2)
    elif action == "remainder":
        return a % b
    elif action == "logarithm":
        return round(__import__('math').log(a, b), 2)
    elif action == "power":
        return a ** b
    elif action == "root":
        return round(a ** (1 / b), 2)
    else:
        raise ValueError("Unsupported action.")

