VAR
    a, b : REAL;
BEGIN
    readln(a, b);
    write('c: ', sqrt(a*a + b*b):10:3, ' ');
    write('P: ', a + b + sqrt(a*a + b*b):10:3, ' ');
    writeln('S: ', a*b/2:10:3);
END.

