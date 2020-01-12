program m96_2;
uses crt;
const n=5;
type range=1..n;
mat=array[range,range] of char;
var
m:mat;i,j:integer;
function f(m:mat):integer;
var deg1,deg2,sof:boolean;
c,d,counter:integer;
begin
i:=1;j:=n;sof:=false;counter:=0;
while (i<=n)and not sof do
if (i=1)and(j=n)and(m[i,j]='b')then begin inc(i);dec(j);inc(counter);end
else if m[i,j]='b' then begin
                         deg1:=true;c:=i-1;
                         while (c>=1)and deg1 do
                         if m[c,j]='a' then dec(c)
                         else deg1:=false;
                         deg2:=true;d:=j+1;
                         while (d<=n)and deg2 do
                         if m[i,d]='a' then inc(d)
                         else deg2:=false;
                         if deg1 and deg2 then
                                          begin
                                          inc(counter);
                                          inc(i);dec(j);
                                          end
                         else sof:=true;
                       end
     else sof:=true;
 f:=counter;
 end;
begin
clrscr;
writeln('ENTER MATRIX 5*5');
for i:=1 to n do
begin
 for j:=1 to n do
 read(m[i,j]);
 readln;
end;
 writeln(f(m));
readkey;
end.

