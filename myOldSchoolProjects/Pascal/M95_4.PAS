program m95_4;
uses crt;
const len=12;
type line=array[1..len]of char;
var a:line;
   function check(var a:line;n:integer):boolean;
     var i:integer;sof:boolean;
       begin
         if len mod n<>0 then check:=false
         else begin
              i:=1 ;sof:=false;
              while not sof and (i<=len-n) do
              if a[i]=a[i+n] then inc(i)
              else sof:=true;
              check:=not sof;
              end;
      end;

   procedure print(var a:line);
    var i,n:integer;sof:boolean;
     begin
      n:=1;sof:=false;
      while not sof and(n<=len)do
      if check(a,n)then begin
                        sof:=true;
                        writeln(n);
                        for i:=1 to n do
                        write(a[i]);
                        end
      else inc(n);
    end;

 procedure get_vector(var a:line);
  var i:integer;
   begin
   writeln('ENTER LETTERS');
   for i:=1 to len do
   read(a[i]);
   end;
begin
clrscr;
get_vector(a);
print(a);
readkey;
end.