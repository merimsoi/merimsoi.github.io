program lab14_11;
uses crt;
const max = 10;
type  base_type_1 = (art, music, sport, theater, books, e);
      hobbies_type = set of base_type_1;
      client = record
                  name    : string [20];
                  hobbies : hobbies_type;
                  preff    : set of 1..max;
               end;
      arr = array [1..max] of client;
var   males, females:arr; L,N,i:integer;
procedure names(var a:arr; var k:integer);
   begin{procedure}

      write('enter males\females '); readln(k);
      writeln('enter names ');
      for i:=1 to k do
            readln(a[k].name);
   end;
procedure read_sheelon;
var c_hobbies:hobbies_type; c_pref: set of 1..max;
    home, i:integer;  sex, ch:char; number,place:integer;
{******************************}
    procedure jump_spaces;
    var sof:boolean;
    begin
       sof:=false;
       while not sof do
          begin
            read(ch);
            if ch<> ' ' then sof:=true;
          end;
    end;
{*******************************}
begin{read_sheelon}
   for i:=1 to n+1 do
      begin
         c_hobbies:=[]; c_pref:=[];
         read(place);
         jump_spaces;
         {   read sex   }
         sex:=ch;
         jump_spaces;
         while ch<>' ' do {  input hobbies  }
           begin
             case ch of
               'a','A': c_hobbies:=c_hobbies+[art];
               'm','M': c_hobbies:=c_hobbies+[music];
               's','S': c_hobbies:=c_hobbies+[sport];
               't','T': c_hobbies:=c_hobbies+[theater];
               'b','b': c_hobbies:=c_hobbies+[books];
             end;
             read(ch);
           end; { end of hobbies input }
         while not eoln do
            begin
              read(number);
              c_pref:=c_pref+[number];
            end;
      { end of input line}
      case sex of
        'm','M': begin
                   males[place].hobbies:=c_hobbies;
                   males[place].preff:=c_pref;
                 end;
        'f','F': begin
                   females[place].hobbies:=c_hobbies;
                   females[place].preff:=c_pref;
                 end;
      end;
      end;{for}
end;{sheelon}
begin{1}
clrscr;
{--receiving names for men array--}
names(males,n);
{--receiving names for women array--}
names(females,l);
{-----------------------------------}
read_sheelon;
end.{1}