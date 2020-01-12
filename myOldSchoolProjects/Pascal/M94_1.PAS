program totto;
const max=100;
type guess_type=array[1..6]of 1..46;
player_type=record
            name:string[20];
            id:string[9];
            guess:guess_type;
            price:0..3;
            end;
vector=array[1..max]of player_type;
var a:vector;
week_guess:guess_type;
begin
get_players;
get_week_guess;
check_player;
print;
end.