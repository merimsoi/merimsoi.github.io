program m90_1;
uses crt;
type
week=(sunday,monday,tuesday,wednesday,thursday,friday);
cities=(london,paris,rome,tel_aviv,zurich);
flig=record
          number:integer;
          day:week;
          time:real;
          kind:string[4];
          town_in:cities;
          town_out:cities;
      end;
list=array[1..10]of flig;
var a:list;
i,useransver:integer;
errorday,errortownin,errortownout:boolean;
town_out,town_in:cities;
day:week;
{----------------flight-----------------}
procedure flight(town_out,town_in:cities;day:week);
var
i:integer;
degel:boolean;
begin
  degel:=false;
  for i:=1 to 10 do
  if (town_out=a[i].town_out)and(town_in=a[i].town_in)and(day=a[i].day)
  then begin
       with a[i] do
        begin
         writeln;
         degel:=true;
         writeln('NUMBER OF FLIGHT==>',number);
         write('DAY==>');
         case day of
          sunday:writeln('SUNDAY');
          monday:writeln('MONDAY');
          tuesday:writeln('TUESDAY');
          wednesday:writeln('WEDNESDAY');
          thursday:writeln('THURSDAY');
          friday:writeln('FRIDAY');
         end;
         writeln('TIME==>',time:2:2);
         writeln('KIND OF PLANE==>',kind);
         write('TOWN(IN)==>');
         case town_in of
          london:writeln('LONDON');
          paris:writeln('PARIS');
          rome:writeln('ROMA');
          tel_aviv:writeln('TEL-AVIV');
          zurich:writeln('ZURICH');
         end;
         write('TOWN(OUT)==>');
         case town_out of
          london:writeln('LONDON');
          paris:writeln('PARIS');
          rome:writeln('ROMA');
          tel_aviv:writeln('TEL-AVIV');
          zurich:writeln('ZURICH');
         end;
      end;
    end;
if not degel then writeln('NO THIS FLIGHT');
end;
{--------input----------}
begin
for i:=1 to 10 do
begin
 clrscr;
 writeln('ENTER INFORMATION ABOUT ',i,' FLIGTH');
 with a[i] do
 begin
   writeln('ENTER NUMBER OF FLIGHT');
   read(number);
   repeat
   writeln('ENTER DAY OF FLIGHT');
   errorday:=false;
   write('1-sunday,2-monday,3-tuesday,4-wednesday,5-thursday,6-friday===> ');
   readln(useransver);
   case useransver of
   1:day:=sunday;
   2:day:=monday;
   3:day:=tuesday;
   4:day:=wednesday;
   5:day:=thursday;
   6:day:=friday;
   else errorday:=true;
   end;
   until errorday=false;
   writeln('ENTER KIND OF PLANE');
   readln(kind);
   writeln('ENTER TIME OF FLIGHT');
   read(time);
   repeat
   writeln('ENTER CITY(IN)');
   errortownin:=false;
   write('1-london,2-paris,3-rome,4-tel-aviv,5-zurich==>');
   readln(useransver);
   case useransver of
   1: town_in:=london;
   2:town_in:=paris;
   3:town_in:=rome;
   4:town_in:=tel_aviv;
   5:town_in:=zurich;
   else errortownin:=true;
   end;
   until errortownin=false;
   repeat
   writeln('ENTER CITY(OUT)');
   errortownout:=false;
   write('1-london,2-paris,3-rome,4-tel-aviv,5-zurich==>');
   readln(useransver);
   case useransver of
   1: town_out:=london;
   2:town_out:=paris;
   3:town_out:=rome;
   4:town_out:=tel_aviv;
   5:town_out:=zurich;
   else errortownout:=true;
   end;
   until errortownout=false;
  end;
end;
clrscr;
 repeat
   writeln('ENTER CITY(OUT)');
   errortownout:=false;
   write('1-london,2-paris,3-rome,4-tel-aviv,5-zurich==>');
   readln(useransver);
      case useransver of
       1: town_out:=london;
       2:town_out:=paris;
       3:town_out:=rome;
       4:town_out:=tel_aviv;
       5:town_out:=zurich;
       else errortownout:=true;
      end;
  until errortownout=false;
  repeat
    writeln('ENTER CITY(IN)');
    errortownin:=false;
    write('1-london,2-paris,3-rome,4-tel-aviv,5-zurich==>');
    readln(useransver);
      case useransver of
       1:town_in:=london;
       2:town_in:=paris;
       3:town_in:=rome;
       4:town_in:=tel_aviv;
       5:town_in:=zurich;
       else errortownin:=true;
      end;
  until errortownin=false;
 repeat
   writeln('ENTER DAY OF FLIGHT');
   errorday:=false;
   write('1-sunday,2-monday,3-tuesday,4-wednesday,5-thursday,6-friday===> ');
   readln(useransver);
   case useransver of
    1:day:=sunday;
    2:day:=monday;
    3:day:=tuesday;
    4:day:=wednesday;
    5:day:=thursday;
    6:day:=friday;
    else errorday:=true;
   end;
 until errorday=false;
flight(town_out,town_in,day);
readkey;
end.