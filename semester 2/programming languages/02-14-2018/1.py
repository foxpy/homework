def string_reiteration(s):
    for i in range(len(s)):
        if (s[:i+1] * (len(s)//len(s[:i+1])) == s):
            return len(s)//len(s[:i+1]), s[:i+1]

