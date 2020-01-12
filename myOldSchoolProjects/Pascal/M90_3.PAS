program m90_3;
uses crt;
type years=1975..1990;
     colors=(white,blue,green,red,black);
     manuf=(volkswagen,volvo,fiat,renault);
     parking_type=array[manuf,colors,years] of integer;
var migrash:parking_type;
year:years;color:colors;car:manuf;
userfinished,errorcolor,errorcar:boolean;
useransver:char;
{---------------print_color--------------}
procedure print_color(var migrash:parking_type;year:years;mun:manuf);
var
i:years;j:manuf;k:colors;
begin
for i:=1975 to 1990 do
for j:=volkswagen to renault do
for k:=white to black do
if (year=i)and(mun=j)and(migrash[j,k,i]<>0) then begin
                                          case k of
                                          white:writeln('WHITE');
                                          blue:writeln('BLUE');
                                          green:writeln('GREEN');
                                          red:writeln('RED');
                                          black:writeln('BLACK');
                                         end;
                       end;
 end;
 {---------------print_color1--------------}
procedure print_color1(var migrash:parking_type;color:colors);
var
i:years;j:manuf;k:colors;
begin
for i:=1975 to 1990 do
for j:=volkswagen to renault do
for k:=white to black do
if (color=k)and(migrash[j,k,i]<>0) then begin
                                          writeln;
                                          writeln(i);
                                          case j of
                                          volkswagen:writeln('VOLKSWAGEN');
                                          volvo:writeln('VOLVO');
                                          fiat:writeln('FIAT');
                                          renault:writeln('RENAULT');
                                         end;
                       end;
 end;
{-------------input--------------------}
begin
clrscr;
userfinished:=false;
while not userfinished do
begin
   errorcar:=false;
   writeln('CHOOSE THE CAR');
   write('W-volkswagen,V-volvo,F-fiat,R-renault===> ');
   readln(useransver);
   case useransver of
  'w','W':car:=volkswagen;
  'v','V':car:=volvo;
  'f','F':car:=fiat;
  'r','R':car:=renault;
  else errorcar:=true;
 end;
 if errorcar then writeln('invalid car')
 else
     begin
     errorcolor:=false;
     WRITELN('CHOOSE THE COLOR');
     write('W-white,B-blue,G-green,R-red,V-black===>');
     readln(useransver);
     case useransver of
     'r','R':color:=red;
     'w','W':color:=white;
     'g','G':color:=green;
     'b','B':color:=blue;
     'v','V':color:=black;
      else errorcolor:=true;
      end;
      if errorcolor then writeln('invalid color')
      else begin
           write('WHAT IS YEAR===>');
           readln(year);
           if(year<1975)or(year>1990)then writeln('invalid year')
           else begin
                     writeln('ENTER NUMBER OF THIS CARS');
                     readln(migrash[car,color,year]);
                 end;
            end;
   end;
 writeln('PRESS "ESC" TO EXIT,ANY KEY TO CONTINUE');
 useransver:=readkey;
 userfinished:=useransver=chr(27);
end;
clrscr;
writeln('ENTER YEAR');
readln(year);
repeat
writeln('CHOOSE THE CAR');
errorcar:=false;
 write('W-volkswagen,V-volvo,F-fiat,R-renault===> ');
 readln(useransver);
  case useransver of
  'w','W':car:=volkswagen;
  'v','V':car:=volvo;
  'f','F':car:=fiat;
  'r','R':car:=renault;
  else errorcar:=true;
  end;
until errorcar=false;
print_color(migrash,year,car);
readkey;
writeln;
repeat
writeln('CHOOSE THE COLOR');
errorcolor:=false;
write('W-white,B-blue,G-green,R-red,V-black===>');
readln(useransver);
 case useransver of
  'r','R':color:=red;
  'w','W':color:=white;
  'g','G':color:=green;
  'b','B':color:=blue;
  'v','V':color:=black;
  else errorcolor:=true;
 end;
 until errorcolor=false;
print_color1(migrash,color);
readkey;
end.
