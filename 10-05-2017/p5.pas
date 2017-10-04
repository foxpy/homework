USES math;

VAR
    a, b, al : REAL;
BEGIN
    read(a, b, al);
    writeln('S: ', tan(al)*(a-b)/2*(a + b)/2);
END.

