program m92_4;
uses crt;
type ptr=^node;
     node=record
     data:char;
     next:ptr;
     end;
var head:ptr;
procedure read_into_tail(var head:ptr);
var newnode,last:ptr;sof:boolean;data:char;
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
head:=nil;sof:=true;
while sof do
begin
 read(data);
 if data='$' then sof:=false
 else begin
      new(newnode);
      newnode^.data:=data;
      newnode^.next:=nil;
      insertafter(head,newnode,last);
      last:=newnode;
end;end;end;
{----------------DELETE DUPLICATE-------------}
procedure delete_duplicate(head:ptr);
var a:array[1..26]of char;
    b:array['a'..'z'] of integer;
i,n:integer;p,q,oneback:ptr;k:char;found:boolean;
begin
for k:='a' to 'z' do b[k]:=0;
p:=head;i:=0;
while p<>nil do
begin
inc(i);
a[i]:=p^.data;
p:=p^.next;
end;
n:=i;
if n<>0 then begin
               p:=head;oneback:=nil;
               while p<>nil do
                 begin
                 i:=1;found:=false;
                 while (i<=n)and not found do
                   begin
                   if a[i]=p^.data then
                                   begin
                                   if b[a[i]]<1 then
                                                 begin
                                                 inc(b[a[i]]);
                                                 found:=true;
                                                 end
                                  else begin
                                       oneback^.next:=p^.next;
                                       dispose(p);
                                       p:=oneback^.next;
                                       end;
                                   end
                   else inc(i);
                   end;
                 oneback:=p;
                 p:=p^.next;
             end;
            end;
p:=head;
while p<>nil do
begin
write(p^.data);p:=p^.next;
end;
end;
begin
clrscr;
read_into_tail(head);
delete_duplicate(head);
readkey;
end.