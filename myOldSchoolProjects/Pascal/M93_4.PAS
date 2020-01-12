program m93_4;
uses crt;
const n=5;
var i:integer;
a,b:array[1..n] of integer;
begin
clrscr;
 writeln('ENTER ',n,' NUMBERS');
 for i:=1 to n do
  begin
  read(a[i]);
  b[a[i]]:=i;
  end;
 for i:=1 to n do
 write(b[i]);
 readkey;
 end.
