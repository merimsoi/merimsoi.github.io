program m91_3;
uses crt;
const n=5;
type haal=record
          name:string[20];
          height:integer;
          end;
list=array[1..n]of haal;
var a:list;
i:integer;
begin
clrscr;
for i:=1 to n do
with a[i] do
begin
write('ENTER ',i,' NAME==>');
readln(a[i].name);
write('ENTER ',i,' HEIGHT==>');
readln(a[i].height);
end;
if a[1].height<a[2].height then writeln(a[1].name);
if a[n].height<a[n-1].height then writeln(a[n].name);
for i:=2 to n-1 do
if (a[i].height<a[i-1].height)and(a[i].height<a[i+1].height)
then writeln(a[i].name);
readkey;
end.