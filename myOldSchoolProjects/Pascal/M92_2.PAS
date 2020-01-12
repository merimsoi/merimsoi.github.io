program m92_2;
uses crt;
type
colors=(white,black,none);
kinds=(bishop,rook,king,queen,pawn);
square=record
        color:colors;
        kind:kinds;
        end;
chess_board=array['a'..'h',1..8]of square;
var board:chess_board;
userfinished,errorkind,errorcolor:boolean;
col:integer;
useransver,row:char;
{----------------PRINT-----------------------------}
procedure print(a:kinds;rows:char;colomn:integer);
begin
write(colomn,rows,' ');
case a of
bishop:writeln('BISHOP');
rook:writeln('ROOK');
king:writeln('KING');
queen:writeln('QUEEN');
pawn:writeln('PAWN');
end;
end;
{----------------LOOK_AT---------------------------}
procedure look_at(var board:chess_board;row:char;colomn:integer);
var found:boolean;r:char;c:integer;
begin
found:=false;r:=row;c:=colomn;
while (r<='h')and not found do
if board[r,c].color=white
then begin
     print(board[r,c].kind,r,c);
     found:=true;
     end
else inc(r);

found:=false;r:=row;c:=colomn;
while (r>='a')and not found do
if board[r,c].color=white
then begin
     print(board[r,c].kind,r,c);
     found:=true;
     end
else dec(r);

found:=false;r:=row;c:=colomn;
while (c<=8) and not found do
if board[r,c].color=white
then begin
     print(board[r,c].kind,r,c);
     found:=true;
     end
else inc(c);

found:=false; r:=row;c:=colomn;
while (c>=1) and not found do
if board[r,c].color=white
then begin
     print(board[r,c].kind,r,c);
     found:=true;
     end
else dec(c);
end;

{----------MAIN-----------------------}
begin
   for row:='a' to 'h' do
   for col:=1 to 8 do
   board[row,col].color:=none;
  clrscr;
  userfinished:=false;
  while not userfinished do
      begin
       repeat
       writeln('ENTER ROW(A..H)');
       readln(row);
       until (row>='a')and(row<='h');
       repeat
       writeln('ENTER COLOMN(1..8)');
       readln(col);
       until (col>=1)and(col<=8);
       errorkind:=false;
       writeln('CHOOSE THE KIND');
       write('B-bishop,R-rook,K-king,Q-queen,P-pawn===> ');
       readln(useransver);
       case useransver of
       'b','B':board[row,col].kind:=bishop;
       'r','R':board[row,col].kind:=rook;
       'k','K':board[row,col].kind:=king;
       'q','Q':board[row,col].kind:=queen;
       'p','P':board[row,col].kind:=pawn;
        else errorkind:=true;
        end;
        if errorkind then writeln('invalid kind')
        else
           begin
           errorcolor:=false;
           writeln('CHOOSE THE COLOR');
           write('W-white,B-black,N-none===>');
           readln(useransver);
           case useransver of
           'w','W':board[row,col].color:=white;
           'b','B':board[row,col].color:=black;
           'n','N':board[row,col].color:=none;
           else errorcolor:=true;
           end;
          if errorcolor then writeln('invalid color')
        end;
 writeln('PRESS "ESC" TO EXIT,ANY KEY TO CONTINUE');
 useransver:=readkey;
 userfinished:=useransver=chr(27);
end;
repeat
writeln('ENTER ROW OF BLACK ROOK(A..H)');
readln(row);
until (row>='a')and(row<='h');
repeat
writeln('ENTER COL OF BLACK ROOK(1..8)');
readln(col);
until(col>=1)and(col<=8);
look_at(board,row,col);
readkey;
end.
