VAR
    x1, y1, x2, y2, x3, y3,
    a, b, c, s : INTEGER;
BEGIN
    readln(x1, y1, x2, y2, x3, y3);
    a := sqrt(sqr(x2-x1) + sqr(y2-y1));
    b := sqrt(sqr(x3-x2) + sqr(y3-y2));
    c := sqrt(sqr(x1-x3) + sqr(y1-y3));
    s := (a + b + c) / 2;

    write('a: ', a, ' b: ', b, 'c: ', c, ' ');
    write('P: ', a+b+c, ' ');
    writeln('S: ' sqrt(s * (s-a) * (s-b) * (s-c)));
END.

