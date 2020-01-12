program m92_1;
uses crt;
const n=2;m=4;
type elem=record
          num:real;
          i,j:integer;
          end;
     mat=array[1..n,1..m] of real;
     vector=array[1..n*m]of elem;
var a:mat;
b:vector;
{-----------copy------------}
procedure copy(a:mat;var b:vector);
var k,i,j:integer;
begin k:=1;
for i:=1 to n do
for j:=1 to m do
 begin
  b[k].num:=a[i,j];
  b[k].i:=i;
  b[k].j:=j;
  inc(k);
 end;
end;
{--------------sort-------------}
procedure sort(var b:vector);
var i,j,min:integer;
    temp:elem;
begin
for i:=1 to n*m-1 do
  begin
  min:=i;
  for j:=i+1 to n*m do
  if b[j].num<b[min].num then min:=j;
  if i<>min then begin
                 temp:=b[i];
                 b[i]:=b[min];
                 b[min]:=temp;
                 end;
  end;
 end;
 {-----------check-------------}
 function check(b:vector;a:mat):boolean;
 var i,j,k,coun:integer;
 begin
  coun:=1;
  for k:=1 to n*m-1 do
  if (abs(b[k].i-b[k+1].i)<=1)and(abs(b[k].j-b[k+1].j)<=1)
  then inc(coun);
  if (coun=m*n)then check:=true
  else check:=false;
  end;
  {----------input matrix------------}
   procedure  read_mat(var a:mat);
   var i,j:integer;
   begin
   writeln('ENTER MATRIX');
   for i:=1 to n do
   for j:=1 to m do
  read(a[i,j]);
end;
{------main-----}
begin
clrscr;
read_mat(a);
copy(a,b);
sort(b);
writeln(check(b,a));
readkey;
end.