program m93_6;
uses crt;
type range=0..1;
var
a:array[1..10]of range;
i,j,k:integer;
found:boolean;
begin
clrscr;
for i:=1 to 10 do
readln(a[i]);
i:=1;
j:=10;
while((i<11)and(i<j))do
begin
if a[i]=1 then
begin
 found:=false;
 while((j>=i)and(not found))do
 begin
 k:=j;
 if a[k]=1 then
    begin
     found:=true;
     j:=k-1;
    end
 else j:=j-1;
  end;
  end;
  i:=i+1;
  end;
  writeln(k);
  readkey;
  end.

