program m89_3;
uses crt;
type list=array[1..15]of char;
var a,b:list;sof:boolean;
i,j,n,c:integer;
k:char;
begin
clrscr;
writeln('ENTER LETTERS');
i:=0;sof:=true;
while sof do
begin
inc(i);
read(a[i]);
if a[i]='$' then sof:=false;
end;
n:=i-1;
for i:=1 to n do
 begin
  b:=a;
   for j:=1 to n do
    begin
     if i<>j then begin
                   k:=b[i];
                   b[i]:=b[j];
                   b[j]:=k;
                   for c:=1 to 4  do
                   write(b[c]);
                   writeln;
                   end;
            end;
end;
readkey;
end.