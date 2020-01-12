program m95_2;
uses crt;
const n=20;
type list=array[1..n]of integer;
var a,b:list;
i,counter:integer;
begin
clrscr;
counter:=0;
for i:=1 to n do b[i]:=0;
writeln('ENTER NUMBERS');
for i:=1 to n do
begin
read(a[i]);
if a[i]=1  then inc(counter)
else if counter<>0 then
                    begin
                    inc(b[counter]);
                    counter:=0;
                    end;
end;
inc(b[counter]);
for i:=1 to n do
if b[i]<>0 then writeln(b[i],' SEQUENCES OF ',i,' ONES');
readkey;
end.

