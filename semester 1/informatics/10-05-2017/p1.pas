VAR
    a, b : REAL;
BEGIN
    readln(a, b);
    write('c: ', sqrt(a*a + b*b):0:3, ' ');
    write('P: ', a + b + sqrt(a*a + b*b):0:3, ' ');
    writeln('S: ', a*b/2:0:3);
END.

