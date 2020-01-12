program m91_1;
uses crt;
type matrix=array[1..10,1..10]of integer;
var
g:matrix;ch:char;
i,j,n:integer;
{-----------path2---------------}
function path2(n:integer;g:matrix;i,j:integer):integer;
var d:integer;degel:boolean;
begin
if g[i,j]=1 then path2:=1
else begin
      d:=1;degel:=false;
       while (d<=n)and not degel do
        if (g[i,d]=1)and(g[d,j]=1)and(d<>i)and(d<>j) then  degel:=true
        else inc(d);
      if degel then path2:=1
      else path2:=0;
     end;
end;
{--------------path4-----------}
function path4(n:integer;g:matrix;i,j:integer):integer;
var d:integer;degel:boolean;
begin
if path2(n,g,i,j)=1 then path4:=1
else begin
      d:=1;degel:=false;
      while (d<=n) and not degel do
      if (path2(n,g,i,d)=1)and(path2(n,g,d,j)=1)and(d<>i)and(d<>j) then degel:=true
      else inc(d);
      if degel then path4:=1
      else path4:=0;
  end;
end;
{-----------main-------------}
begin
 clrscr;
 writeln('ENTER N');
 readln(n);
 i:=1;
 writeln('ENTER MEMBERS OF MATRIX SIMETRIT(1/0)');
 while i<=n-1 do
 begin  j:=i+1;
        while j<=n do
          begin repeat
                write(i,'/',j,'==>');
                readln(g[i,j]);
                until (g[i,j]=1)or(g[i,j]=0);
                inc(j);
          end;
        inc(i);
 end;
 j:=1;
 while j<=n-1 do
  begin  i:=j+1;
         while i<=n do
          begin g[i,j]:=g[j,i];
                inc(i);
          end;
         inc(j);
   end;
 repeat
  writeln('ENTER I,J');
  readln(i);readln(j);
  if i=j then writeln('ERROR')
  else writeln(path4(n,g,i,j));
  writeln('ESC to exit,any key to continue');
  ch:=readkey;
 until ord(ch)=27;
end.