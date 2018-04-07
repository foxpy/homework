def bubble_sort(array):
    for i in range(len(array)):
        for j in range(len(array)-i-1):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
    return array


def insertion_sort(array):
    for i in range(1, len(array)):
        j = i
        while j > 0 and array[j] < array[j-1]:
            array[j], array[j-1] = array[j-1], array[j]
            j -= 1
    return array


def selection_sort(array):
    for i in range(len(array)-1):
        selection = i
        for j in range(i+1, len(array)):
            if array[j] < array[selection]:
                selection = j
        array[i], array[selection] = array[selection], array[i]
    return array




###########################################################
# These functions are not really related to homework task #
###########################################################


def quick_sort(array):
    if len(array) > 1:
        index = len(array) // 2
        large = []
        small = []

        for i in range(len(array)):
            if i != index:
                if array[i] > array[index]:
                    large.append(array[i])
                else:
                    small.append(array[i])

        quick_sort(small)
        quick_sort(large)
        array[:] = small + [array[index]] + large
        return array


def really_quick_sort(array):
    array.sort()
    return array
