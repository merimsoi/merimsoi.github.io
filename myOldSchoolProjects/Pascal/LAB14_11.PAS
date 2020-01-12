program hh;
uses crt;
const max=100;
type base_type_1=(art,music,sport,theater,books,e);
     hobbies_type=set of base_type_1;
     client=record
                  name:string[20];
                  hobbies:hobbies_type;
                  pref:set of 1..max;
            end;
     arr=array[1..max] of client;
var females,males:arr;n,l:integer;
{-----------------------------}
procedure read_names(var a:arr;var m:integer);
var I:integer;
begin
     writeln('how many males,females ');
     readln(m);
     for i:=1 to m do begin write('enter name ');readln(a[i].name);end;
end;
{-----------------------------------}
procedure read_sheelon;
var c_hobbies:hobbies_type;  c_pref:set of 1..max;
    i:integer;place:integer;      sex,ch:char;  number:integer;
     {************************}
     procedure jump_spaces;
     var sof:boolean;
     begin
          sof:=false;
          while not sof do
                begin
                read(ch);
                if ch<>' ' then sof:=true;
                end;
    end;
    {*************************}

begin  {read_sheelon }
writeln('sheelon');
for i:=1 to n+l do
    begin
       c_hobbies:=[];   c_pref:=[];
       read(place);
       jump_spaces;
       {  read sex  }
       sex:=ch;
       jump_spaces;
       while ch<>' ' do   { input hobbies  }
          begin
          case ch of
          'a','A':c_hobbies:=c_hobbies+[art];
          'm','M':c_hobbies:=c_hobbies+[music];
          's','S':c_hobbies:=c_hobbies+[sport];
          't','T':c_hobbies:=c_hobbies+[theater];
          'B','b':c_hobbies:=c_hobbies+[books];
          end;
          read(ch);
          end;
       { end of hobbies input }
       while not eoln do
         begin
         read(number);
         c_pref:=c_pref+[number];
         end;
   { end of input line  }
   case sex of
   'm','M':begin
                males[place].hobbies:=c_hobbies;
                males[place].pref:=c_pref;
           end;
    'f','F':begin
                females[place].hobbies:=c_hobbies;
                females[place].pref:=c_pref;
           end;
   end; {case }
   end; { for }
end;  {read_sheelon }

{-------------------------------}
begin { main }
      clrscr;
      read_names(females,l);
      read_names(males,n);
      read_sheelon;
      {compatibles;}
end.
