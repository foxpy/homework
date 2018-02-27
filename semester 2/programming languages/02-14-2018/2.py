def beautify(input_str, punctuation_marks=['.', ',', '!', '?']):
    output_str = ""
    for i in input_str.split():
        output_str += (" " + i) if i not in punctuation_marks else i
    return output_str.strip()

