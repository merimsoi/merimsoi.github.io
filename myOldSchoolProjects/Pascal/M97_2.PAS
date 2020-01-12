program m_97_2;
uses crt;
const max=100;
type
    ptr = ^item;
    item = record
           number:integer;
           name:string[25];
           year:integer;
           maskoret:real;
           next:ptr;
           end;
var head1,head2:ptr;
procedure read_into_tail(var head:ptr);
var newnode,last:ptr;num:integer;sof:boolean;
{///////////////////////////////////////////////////////}
procedure insertafter(var head:ptr;newnode,afterthis:ptr);
begin
if head=nil then head:=newnode
else
 begin
 newnode^.next:=afterthis^.next;
 afterthis^.next:=newnode;
 end; end;
begin
head:=nil;sof:=true;
while sof do
begin
read(num);
if num=0 then sof:=false
else begin
 new(newnode);
 newnode^.number:=num;
 read(newnode^.year);
 read(newnode^.maskoret);
 read(newnode^.name);
 newnode^.next:=nil;
 insertafter(head,newnode,last);
 last:=newnode;
end;end;end;
{---------------------------------------------------------}
procedure gil(head1,head2:ptr);
var p1,p2:ptr;coun_mesh,min,this_year:integer;found:boolean;
begin
coun_mesh:=0;
p1:=head1;
while p1<>nil do
  begin
    found:=false;p2:=head2;
     while (p2<>nil) and not found do
     if p1^.year=p2^.year then found:=true
     else p2:=p2^.next;
    if found then
             begin
             inc(coun_mesh);
             if coun_mesh=1 then min:=p1^.year
             else if p1^.year<min then min:=p1^.year;
             end;
    p1:=p1^.next;
   end;
if coun_mesh=0 then writeln('no common age')
else begin
     writeln('enter this year');
     readln(this_year);
     writeln(this_year-min);
     end;
end;
begin
clrscr;
writeln('enter group1');
read_into_tail(head1);
writeln('enter group2');
read_into_tail(head2);
gil(head1,head2);
end.