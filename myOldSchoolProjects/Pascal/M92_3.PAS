program m92_3;
uses crt;
const n=3;
type matrix=array[1..n,1..n]of integer;
var a:matrix;
{-----------input matrix---------}
procedure get_matrix(var a:matrix);
var i,j:integer;
begin
writeln('ENTER MATRIX');
for i:=1 to n do
for j:=1 to n do
read(a[i,j]);
end;
{-----------magic square----------}
function magic_square(var a:matrix):boolean;
type vector=array[1..n]of integer;
var sum_rows,sum_cols:vector;
row,col,diag1,diag2:integer;
magic:boolean;
begin
diag1:=0;diag2:=0;
for row:=1 to n do
begin
   sum_rows[row]:=0;
   sum_cols[row]:=0;
end;
for row:=1 to n do
for col:=1 to n do
begin
sum_rows[row]:=sum_rows[row]+a[row,col];
sum_cols[col]:=sum_cols[col]+a[row,col];
if row=col then diag1:=diag1+a[row,col];
if row+col=n+1 then diag2:=diag2+a[row,col];
end;
magic:=false;
if diag1=diag2 then begin
                    row:=1;magic:=true;
                    while (row<=n)and magic do
                    if(sum_rows[row]=sum_cols[row])and(sum_rows[row]=diag1)
                    then inc(row)
                    else magic:=false;
                    end;
magic_square:=magic;
end;
{----------------main--------------}
begin
clrscr;
get_matrix(a);
if magic_square(a) then writeln('TRUE')
else writeln('FALSE');
readkey;
end.