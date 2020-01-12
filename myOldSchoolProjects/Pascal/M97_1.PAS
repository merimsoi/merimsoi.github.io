program m97_1;
uses crt;
const m=5;
      n=5;
type matrix=array[1..m,1..n] of integer;
var a:matrix;
counter_zero,counter_one,counter_free,row,col:integer;
mone_col,mone_row:array[1..100] of integer;
sof,sof1:boolean;
begin
clrscr;
{-----------------get matrix---------------}
writeln('ENTER MATRIX');
for row:=1 to m do
for col:=1 to n do
read(a[row,col]);
{--------------CHECK-----------}
counter_zero:=0;counter_one:=0;counter_free:=0;
for row:=1 to m do
for col:=1 to n do
begin if a[row,col]=0 then inc(counter_zero)
      else if a[row,col]=1 then inc(counter_one)
           else inc(counter_free);
end;
if ((counter_zero>=0.4*m*n)and(counter_one>=0.4*m*n))
then begin
     sof:=true;row:=1;
     while not sof and (row<=m) do
     if mone_row[row]>2 then sof:=false
     else inc(row);
     sof1 :=true; col:=1;
     while not sof1 and (col<=n) do
     if mone_col[col]>=2  then sof:=false
     else inc(col);
end;
if sof and sof1 then writeln('TRUE')
else writeln('FALSE');
readkey;
end.




