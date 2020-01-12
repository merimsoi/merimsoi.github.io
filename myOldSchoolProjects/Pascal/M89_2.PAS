program m89_2;
uses crt;
const n=4;
type special=array[1..n,1..n]of integer;
     vector=array[1..n]of integer;
var a,b:special;counter:vector;
{------------get_matrix-----------}
procedure get_matrix(var a:special);
var i,j:integer;
begin
writeln('ENTER MATRIX');
for i:=1 to n do
for j:=1 to n do
read(a[i,j]);
end;
{-----------row_col---------------}
procedure row_col(var a,b:special);
var i,j,max,max1,equal:integer;sof:boolean;
  {-----------row and col------------}
   procedure row_and_col(k,c:integer);
   var i:integer;degel:boolean;
    begin
     degel:=true;
     for i:=1 to n do
     if a[k,i]<>b[i,c] then degel:=false;
     if degel then
              begin
              writeln('ROW ',k,' IS COLOMN ',c);
              sof:=false;
              inc(counter[k]);
              end;
     end;
begin
for i:=1 to n do counter[i]:=0;
sof:=true;
for i:=1 to n do
for j:=1 to n do
row_and_col(i,j);
if sof then writeln('NO ROWS THAT APPEAR AS COLOMN')
else begin
     max:=counter[1];
     max1:=1;
     equal:=0;
     for i:=2 to n do
     if counter[i]>max then begin
                             max:=counter[i];
                             max1:=i;
                             equal:=0;
                             end
     else if counter[i]=max then inc(equal);
     if equal=0 then writeln('ROW ',max1,' APPEAR MAXIMUM TIMES,AS COLOMN')
     else writeln('NO ROW THAT APPEAR MAXIMUM TIMES,AS COLOMN');
     end;
 end;
{------------------max_min---------------}
procedure max_min(var a:special);
var i,j:integer;
degel1,degel2,degel3:boolean;
  {-----------max---------}
  function max(maxi,i:integer):boolean;
  var j:integer;degel:boolean;
  begin
  degel:=true;
  for j:=1 to n do
  if a[i,j]>maxi then degel:=false;
  max:=degel;
  end;
  {-----------min---------}
  function min(mini,j:integer):boolean;
  var i:integer;degel:boolean;
  begin
  degel:=true;
  for i:=1 to n do
  if a[i,j]<mini then degel:=false;
  min:=degel;
  end;
begin
degel3:=true;
for i:=1 to n do
for j:=1 to n do
begin
degel1:=max(a[i,j],i);
degel2:=min(a[i,j],j);
if degel1 and degel2 then
                     begin
                     writeln('VARIABLE ',a[i,j],' IN ROW ',i,' COLOMN ',j);
                     degel3:=false;
                     end;
end;
if degel3 then writeln('NO NUMBER THAT MAX IN ROW AND MIN IN COL');
end;
{----------main-------------}
begin
clrscr;
get_matrix(a);
get_matrix(b);
row_col(a,b);
readkey;
get_matrix(a);
max_min(a);
readkey;
end.