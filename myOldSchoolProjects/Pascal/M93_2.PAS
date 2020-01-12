program m93_2;
uses crt;
type ptr=^node;
node=record
     info:integer;
     next:ptr;
     end;
var  head,k:ptr;
{///////////////////////////////////////////////////////}
procedure build_ring(var head:ptr);
var last:ptr;
begin
head:=nil;
while not eoln do
if head=nil then begin
                 new(head);
                 last:=head;
                 read(head^.info);
                 end
else begin
     new(last^.next);
     last:=last^.next;
     read(last^.info);
     end;
     last^.next:=head;
     end;
{------------------------------------------------}
function find_last(head:ptr):ptr;
var p:ptr;
begin
p:=head;
while p^.next<>head do p:=p^.next;
find_last:=p;
end;
{--------------------------------------------------}
function last(head:ptr;n:integer):ptr;
var p,q,this:ptr;coun:integer;
begin
if head=head^.next then last:=head
else  begin
      coun:=0;this:=head;
      while head<>head^.next do
      begin
      inc(coun);
      if coun=n then begin
                     p:=find_last(this);
                     q:=this^.next;
                     p^.next:=q;
                     dispose(this);
                     head:=q;
                     this:=head;
                     coun:=0;
                     end
       else  this:=this^.next;
      end;
     last:=head;
  end;
end;
begin
clrscr;
build_ring(head);
k:=last(head,4);
writeln(k^.info);
readkey;
end.