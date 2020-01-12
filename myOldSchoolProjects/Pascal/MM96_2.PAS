program m_96_3;
uses crt;
const max=100;
type
    small_int=1..max;
    ptr = ^item;
    item = record
           data:small_int;
           next:ptr;
           end;
var head1,head2:ptr;sof:boolean;
{///////////////////////////////////////////////////////}
procedure no_common(l1,l2:ptr);
var p1,p2:ptr;s1,s2,s:set of small_int;
i:integer;
begin
p1:=l1; p2:=l2;s1:=[];s2:=[];
while p1<>nil do
      begin
      s1:=s1+[p1^.data];
      p1:=p1^.next;
      end;
while p2<>nil do
      begin
      s2:=s2+[p2^.data];
      p2:=p2^.next;
      end;
s:=s1-s1*s2;
for i:=1 to max do if i in s then write(i:4);
end;
{///////////////////////////////////////////////////////}
procedure read_into_tail(var head:ptr);
var newnode,last:ptr;num:integer;
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
head:=nil;
sof:=true;
while sof do
begin
read(num);
if num=0 then sof:=false
else begin
 new(newnode);
 newnode^.data:=num;
 newnode^.next:=nil;
 insertafter(head,newnode,last);
 last:=newnode;
end;end;end;
begin
clrscr;
writeln('enter numbers');
read_into_tail(head1);
writeln('enter numbers');
read_into_tail(head2);
no_common(head1,head2);
end.