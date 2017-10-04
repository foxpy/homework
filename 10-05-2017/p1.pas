VAR
    a, b : REAL;
BEGIN
    readln(a, b);
    write('c: ', sqrt(a*a + b*b):3:5, ' ');
    write('P: ', a + b + sqrt(a*a + b*b):3:5, ' ');
    writeln('S: ', a*b/2:3:5);
END.

