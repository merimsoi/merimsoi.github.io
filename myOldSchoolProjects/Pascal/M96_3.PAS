program m_96_3;
uses crt;
type
    ptr = ^item;
    item = record
           data:integer;
           next:ptr;
           end;
var head1,head2:ptr;sof:boolean;
{///////////////////////////////////////////////////////}
function common(l1,l2:ptr):real;
var p1,p2:ptr;sum:real;
begin
p1:=l1; p2:=l2;sum:=0;
while (p1<>nil)and(p2<>nil) do
if p1^.data=p2^.data
  then begin sum:=sum+sqrt(p1^.data);
             p1:=p1^.next;
             p2:=p2^.next;
       end
   else if p1^.data<p2^.data
           then p1:=p1^.next
           else p2:=p2^.next;
common:=sum;
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
 end;
 end;
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
end;
end;
end;
begin
clrscr;
writeln('enter numbers');
read_into_tail(head1);
writeln('enter numbers');
read_into_tail(head2);
writeln(common(head1,head2):3:2);
end.