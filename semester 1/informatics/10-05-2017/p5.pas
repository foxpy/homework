USES
    MATH;
VAR
    a, b, al : REAL;
BEGIN
    read(a, b, al);
    writeln('S: ', tan(al*pi/180)*(sqr(a) - sqr(b))/2:0:3);
END.

