program m89_3;
uses crt;
type list=array[1..15]of char;
var a:list;sof:boolean;
i:integer;
begin
clrscr;
writeln('ENTER LETTERS');
i:=0;sof:=true;
while sof do
begin
inc(i);
read(a[i]);
if a[i]='$' then sof:=false;
end;
end.