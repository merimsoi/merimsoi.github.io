program m93_3;
uses crt;
const max_teams=10;
      max_lengh=20;
type team_type=record
               name:string[max_lengh];
               pointer:integer;
               victories,equals,gols_in,gols_out:integer;
               end;
tavlat_liga=array[1..max_teams]of team_type;
var liga:tavlat_liga;
{-------------input tavla-------------}
procedure klitat_tavla(var liga:tavlat_liga);
var i:integer;
begin
for i:=1 to max_teams do
begin
clrscr;
writeln('GROUP ',i);
with liga[i] do
     begin
     write('NAME==>');
     readln(name);
     write('POINTER==>');
     readln(pointer);
     write('NUMBER OF VICTORIES==>');
     readln(victories);
     write('NUMBER OF EQUAL==>');
     readln(equals);
     write('NUMBER OF GOALS(IN)==>');
     readln(gols_in);
     write('NUMBER OF GOALS(OUT)==>');
     readln(gols_out);
     end;
  end;
end;
{-------------input result and change tavla------------}
procedure klitat_mahzor_idcun(var liga:tavlat_liga);
var teama,teamb:string[max_lengh];
    i,golsa,golsb,placea,placeb:integer;
     {------------search name--------------}
     function search_team(team_name:string;var liga:tavlat_liga):integer;
      var i:integer;found:boolean;
      begin
      i:=1;found:=false;
      while not found and(i<=max_teams)do
      if team_name=liga[i].name then begin
                                      found:=true;
                                      search_team:=i;
                                      end
       else inc(i);
       if not found then search_team:=0;
       end;
begin
clrscr;
writeln('ENTER LAST RESULT');
for i:=1 to max_teams div 2 do
begin
 write('TEAM 1==>');
 readln(teama);
 write('TEAM 2==>');
 readln(teamb);
 writeln('ENTER RESULT');
 readln(golsa);
 readln(golsb);
 placea:=search_team(teama,liga);
 placeb:=search_team(teamb,liga);
 if (placea=0)or(placeb=0) then writeln('ERROR')
 else begin
      if golsa>golsb then begin
                       liga[placea].pointer:=liga[placea].pointer+3;
                       liga[placea].gols_in:=liga[placea].gols_in+golsa;
                       liga[placea].gols_out:=liga[placea].gols_out+golsb;
                       inc(liga[placea].victories);
                       liga[placeb].gols_in:=liga[placeb].gols_in+golsb;
                       liga[placeb].gols_out:=liga[placeb].gols_out+golsa;
                            end
      else if golsa=golsb then begin
                          inc(liga[placea].pointer);
                          inc(liga[placeb].pointer);
                          inc(liga[placea].equals);
                          inc(liga[placeb].equals);
                          liga[placea].gols_in:=liga[placea].gols_in+golsa;
                          liga[placea].gols_out:=liga[placea].gols_out+golsb;
                          liga[placeb].gols_in:=liga[placeb].gols_in+golsb;
                          liga[placeb].gols_out:=liga[placeb].gols_out+golsa;
                                end
            else  begin
                  liga[placeb].pointer:=liga[placeb].pointer+3;
                  liga[placeb].gols_in:=liga[placeb].gols_in+golsb;
                  liga[placeb].gols_out:=liga[placeb].gols_out+golsa;
                  inc(liga[placeb].victories);
                  liga[placea].gols_in:=liga[placea].gols_in+golsa;
                  liga[placea].gols_out:=liga[placea].gols_out+golsb;
                  end;
       end;
    end;
  end;
 {-----------------sort tavla-----------------}
 procedure sort_tavla(var liga:tavlat_liga);
 var i,j,max,evdel1,evdel2:integer;
 temp:team_type;
 begin
 for i:=1 to max_teams-1 do
 begin
 max:=i;
  for j:=i+1 to max_teams do
  begin
  evdel1:=liga[j].gols_in-liga[j].gols_out;
  evdel2:=liga[max].gols_in-liga[max].gols_out;
  if (liga[j].pointer>liga[max].pointer)
     or((liga[j].pointer=liga[max].pointer)and(evdel1>evdel2))
     or((liga[j].pointer=liga[max].pointer)and(evdel1=evdel2)and(liga[j].victories>liga[max].victories))
     then max:=j;
  end;
    temp:=liga[i];
    liga[i]:=liga[max];
    liga[max]:=temp;
 end;
 end;
 {-----------print tavla-------------}
 procedure print_tavla(var liga:tavlat_liga);
 var i,place,evdel1,evdel2:integer;
 begin
 clrscr;
 place:=1;
 writeln(' PLACE   NAME    GOALS(IN)    GOALS(OUT)  VICTORY  POINTERS');
 for i:=1 to max_teams do
 begin
 writeln(place:4,liga[i].name:9,liga[i].gols_in:10,liga[i].gols_out:12,liga[i].victories:12,liga[i].pointer:10);
 evdel1:=liga[i].gols_in-liga[i].gols_out;
 evdel2:=liga[i+1].gols_in-liga[i+1].gols_out;
 if ((liga[i].pointer=liga[i+1].pointer) and (evdel1=evdel2)
 and(liga[i].victories=liga[i+1].victories)) then place:=place
 else inc(place);
 end;
 end;
{----------------main---------------}
begin
klitat_tavla(liga);
klitat_mahzor_idcun(liga);
sort_tavla(liga);
print_tavla(liga);
readkey;
end.