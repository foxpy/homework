def beautify(input_str, punctuation_marks=['.', ',', '!', '?']):
    def parse_punctuation(s):
        r = ""
        for i in s:
            r += (i + " ") if i in punctuation_marks else i
        print(r)
        return r

    output_str = ""
    for i in input_str.split():
        output_str += i if i in punctuation_marks else parse_punctuation(i)
    return output_str.strip()

