program mahat_94_3;
uses crt;
const n=2;
type mat=array[1..n,1..n] of integer;
var a,b,c:mat;
{--------exist------------------------}
function exist(m:mat;element:integer): boolean;
var i,j:integer; sof:boolean;
begin
sof:=false;
i:=1;
while not sof and (i<=n)do
begin
j:=1;
while not sof and (j<=n) do
if m[i,j]=element
   then sof:=true
   else inc(j);
   inc(i);
   end;
exist:= sof;
end;
{---------------check----------------------}
function check(a,b,c:mat):boolean;
var sof:boolean; element,i,j:integer;
begin
sof:=false;
i:=1;
while not sof and (i<=n)do
begin
j:=1;
while not sof and (j<=n) do
   begin
   writeln(a[i,j]:5,exist(b,a[i,j]):10,exist(c,a[i,j]):10);
   if exist(b,a[i,j]) and exist(c,a[i,j])
          then sof:=true
          else inc(j);
   end;
   inc(i);
end;
check:= sof;
end;
{-----------------get_mat------------------}
procedure get_mat(var a:mat);
var i,j:integer;
begin
clrscr;
write('enter matrix ');
for i:=1 to n do
for j:=1 to n do
read(a[i,j]);
end;
{-------------------------------}
procedure print_mat(var a:mat);
var i,j:integer;
begin
for i:=1 to n do
    begin
    for j:=1 to n do
       write(a[i,j]:5);
   writeln;
   end;
writeln('============================================');
end;
{------------------main----------------------}
begin
get_mat(a);
get_mat(b);
get_mat(c);
clrscr;
print_mat(a);
print_mat(b);
print_mat(c);
writeln(exist(b,a[1,1]));
{writeln(check(a,b,c));}
readkey;
end.



