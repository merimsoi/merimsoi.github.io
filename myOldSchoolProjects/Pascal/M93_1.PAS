program m93_1;
uses crt;
var money,price:real;
 procedure odef(price,money:real);
  var common_odef,odef_5,odef_1,odef_50,odef_10:integer;
   begin
   price:=price*100;
   money:=money*100;
   common_odef:=trunc(money-price);
   if common_odef=0 then writeln('DELIVERY IS 0')
   else if common_odef<0 then writeln('NO ENOUGH MONEY')
        else
          begin
           odef_5:=common_odef div 500;
           odef_1:=(common_odef-odef_5*500) div 100;
           odef_50:=(common_odef-odef_5*500-odef_1*100) div 50;
           odef_10:=(common_odef-odef_5*500-odef_1*100-odef_50*50) div 10;
           if odef_5>0 then writeln('5 SHEKEL IS ',odef_5);
           if odef_1>0 then writeln('1 SHEKEL IS ',odef_1);
           if odef_50>0 then writeln('50 OGOROD IS ',odef_50);
           if odef_10>0 then writeln('10 OGOROD IS ',odef_10);
          end;
   end;
begin
clrscr;
writeln('ENTER PRICE');
readln(price);
writeln('ENTER QUANTITY OF MONEY');
readln(money);
odef(price,money);
readkey;
end.