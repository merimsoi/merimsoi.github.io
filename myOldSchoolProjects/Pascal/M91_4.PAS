program m91_4;
uses crt;
type matrix=array[1..10,1..10]of integer;
var
a:matrix;
i,j,m,n:integer;
{----------bdika-------------------}
procedure bdika(n,m:integer;var a:matrix);
var i,c,k:integer;degel:boolean;
begin
i:=1;degel:=false;
while (i<=m)and not degel do
 begin
   c:=i+1;
   while (c<=m)and not degel do
     begin
      k:=0;
      for j:=1 to n do
      k:=k+(a[i,j]*a[c,j]);
      if k=0 then inc(c)
      else degel:=true;
     end;
   inc(i);
 end;
 if not degel then writeln('TRUE')
 else writeln('FALSE');
end;
{------------main------------------}
begin
clrscr;
writeln('ENTER NUMBER OF VECTORS');
readln(m);
writeln('ENTER LENGTH OF VECTORS');
readln(n);
for i:=1 to m do
begin
  writeln('ENTER ',i,' VECTOR');
  for j:=1 to n do
   read(a[i,j]);
end;
bdika(n,m,a);
readkey;
end.