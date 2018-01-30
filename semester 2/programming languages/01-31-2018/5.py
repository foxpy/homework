def second_maximum(values):
    # discard duplicates
    values = set(values)

    # discard first maximum as well
    values.discard(max(values))

    if len(values) < 2:
        # it has no second maximum
        return "No"

    return max(values)

