program m95_1;
uses crt;
const n=5;
m=5;
type matrix=array[1..n,1..m]of integer;
var
a:matrix;
{------------input matrix------------}
procedure get_matrix(var a:matrix);
var i,j:integer;
begin
writeln('ENTER MATRIX');
for i:=1 to n do
for j:=1 to m do
read(a[i,j]);
end;
{-----------procedure dlil----------}
procedure dlil(var a:matrix);
type list=array[1..n]of integer;
     list1=array[1..m]of integer;
var counter,i,row,col:integer;
sum_rows:list;
sum_cols:list1;
sof1,sof2:boolean;
begin
counter:=0;
for i:=1 to n do sum_rows[i]:=0;
for i:=1 to m do sum_cols[i]:=0;
for row:=1 to n do
for col:=1 to m do
if a[row,col]<>0 then begin
                      inc(counter);
                      inc(sum_rows[row]);
                      inc(sum_cols[col]);
                      end;
sof1:=true;row:=1;
while sof1 and (row<=n) do
if sum_rows[row]>=2 then sof1:=false
else inc(row);
sof2:=true;col:=1;
while sof2 and (col<=m) do
if sum_cols[col]>=2 then sof2:=false
else inc(col);
if (counter<=(m*n)/10)and sof1 and sof2 then writeln('TRUE')
else writeln('FALSE');
end;
{--------------main--------------}
begin
clrscr;
get_matrix(a);
dlil(a);
readkey;
end.