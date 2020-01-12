program m90_2;
uses crt;
type list=array[15..30]of integer;
var
a,b,c:list;
i:integer;
ch:char;
sof,degel:boolean;
begin
clrscr;
for i:=15 to 30 do a[i]:=0;
for i:=15 to 30 do b[i]:=0;
for i:=15 to 30 do c[i]:=0;
sof:=false;
while not sof do
begin
 writeln('ENTER CATEGORIA OF PLACE');
 readln(ch);
 if (ch<>'a')and(ch<>'A')and(ch<>'b')and(ch<>'B')and(ch<>'c')and(ch<>'C')and(ch<>'?')
 then writeln('ERROR IN CATEGORIA')
 else if ch='?' then sof:=true
      else
       begin
       if (ch='a')or(ch='A')
       then  begin
             i:=15;degel:=false;
             while (i<=30) and not degel do
             if a[i]=0 then begin
                             a[i]:=1;
                             degel:=true;
                             writeln('YOUR PLACE IS ',i);
                            end
              else inc(i);
            if degel=false then writeln('NO PLACES FREE IN THIS CATEGORIA');
            end
       else if (ch='b')or(ch='B')
            then begin
                  i:=15;degel:=false;
                  while (i<=30) and not degel do
                  if b[i]=0 then begin
                                  b[i]:=1;
                                  degel:=true;
                                  writeln('YOUR PLACE IS ',i);
                                 end
                    else inc(i);
                  if degel=false then writeln('NO PLACES FREE IN THIS CATEGORIA');
                 end
            else if (ch='c')or(ch='C')
                 then begin
                       i:=15;degel:=false;
                       while (i<=30) and not degel do
                       if c[i]=0 then begin
                                       c[i]:=1;
                                       degel:=true;
                                       writeln('YOUR PLACE IS ',i);
                                      end
                        else inc(i);
                      if degel=false then writeln('NO PLACES FREE IN THIS CATEGORIA');
                     end;
          end;
 end;
readkey;
end.