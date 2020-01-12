program m_95_3;
uses crt;
type
    ptr = ^item;
    item = record
           data:integer;
           next:ptr;
           end;
var head1,head2:ptr;sof:boolean;c:integer;
{///////////////////////////////////////////////////////}
function common_max(l1,l2:ptr):integer;
type base_type=1..100;
     set_type=set of base_type;
var p1,p2:ptr;s:set_type; i:integer;
begin
p1:=l1;s:=[];
while (p1<>nil) do
begin
  p2:=l2;sof:=false;
  while(p2<>nil)and not sof do
  if p1^.data=p2^.data then begin s:=s+[p1^.data];
                                  sof:=true;
                            end
  else p2:=p2^.next;
  p1:=p1^.next;
end;
sof:=false;
i:=100;
while not sof and(i>0) do
if i in s then begin
            common_max:=i;
            sof:=true;
            end
else i:=pred(i);
if i=0 then common_max:=0;
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
if num=0  then sof:=false
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
c:=common_max(head1,head2);
if c=0 then writeln('no common')
else writeln(c);
end.