VAR
    x1, y1, x2, y2, x3, y3,
    a, b, c, s : REAL;
BEGIN
    readln(x1, y1, x2, y2, x3, y3);
    a := sqrt(sqr(x2-x1) + sqr(y2-y1));
    b := sqrt(sqr(x3-x2) + sqr(y3-y2));
    c := sqrt(sqr(x1-x3) + sqr(y1-y3));
    s := (a + b + c) / 2;

    write('a: ', a:10:3, ' b: ', b:10:3, ' c: ', c:10:3, ' ');
    write('P: ', a+b+c:10:3, ' ');
    writeln('S: ', sqrt(s * (s-a) * (s-b) * (s-c)):10:3);
END.

