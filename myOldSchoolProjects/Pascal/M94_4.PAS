program m94_4;
uses crt;
const n=11;
type vector=array[1..n]of 'a'..'z';
var vec1,vec2:vector;
    i,j:integer;ch:char;
  {---------------polindrom------------}
  procedure polindrom(var vec1,vec2:vector);
   type counter_letters=array['a'..'z'] of integer;
   var   counter:counter_letters;
        {------------check------------}
        function check:boolean;
        var mone:integer;
          begin
           for ch:='a' to 'z' do counter[ch]:=0;
           for i:=1 to n do inc(counter[vec1[i]]);
           mone:=0;
           for ch:='a' to 'z' do
           if counter[ch]mod 2=1 then inc(mone);
           check:=(mone=0)or(mone=1)
          end;
          {----------------build--------------}
          procedure build;
          var middle:char;x1,x2:integer;
          begin
          x1:=1;x2:=n;
          for ch:='a' to 'z' do
          if counter[ch]>0 then
          begin for j:=1 to counter[ch] div 2 do
                 begin
                  vec2[x1]:=ch;
                  vec2[x2]:=ch;
                  inc(x1);dec(x2);
                 end;
                if counter[ch]mod 2=1 then middle:=ch;
         end;
         if n mod 2 =1 then vec2[n div 2+1]:=middle;
        for i:=1 to n do write(vec2[i]);
       end;
   begin
     if check then begin writeln('EXIST POLINDROM');
                         build;
                   end
     else writeln('NOT EXIST POLINDROM');
     end;
     {----------input--------}
     procedure get_vector(var vec1:vector);
     begin
     clrscr;
     writeln('ENTER POLINDROM');
     for i:=1 to n do read(vec1[i]);
     end;
  {---------main---------}
  begin
  get_vector(vec1);
  polindrom(vec1,vec2);
  readkey;
  end.