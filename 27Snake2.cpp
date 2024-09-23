#include <bits/stdc++.h>
#include <windows.h> // For MS Windows only
using namespace std;

// Classes declaration
class Board;
class Food;
class Food2;
class Snake;

// Point on screen/board in terms of (x,y)
// 1-based indexing/positioning
struct position {
    int x, y;

    // Constructors
    position() {}
    position(int a, int b) : x(a), y(b) {}
};



// Board class definition
class Board {
private:
    int height, width; // height(along y), width(along x) of Playable Board
    char symbol;
    char** field;      // char 2D-array for storing values present on Board
public:
    // Constructor
    Board(int a, int b) {
        height = a; // initializing height of board
        width = b;  // initializing width of board

        symbol = '*';

        // dynamic memory allocation for board
        field = new char* [height + 2];
        for (int i = 0; i < height + 2; i++)
            field[i] = new char[width + 2];
    }

    // Destructor
    ~Board() {
        // deallocating dynamic memory allocated previously
        for (int i = 0; i < height + 2; i++)
            delete[] field[i];

        delete[] field;
    }

    // print board on screen
    void show_board() {
        for (int i = 0; i < height + 2; i++) {
            for (int j = 0; j < width + 2; j++) {
                cout << field[i][j];
            }
            cout << endl;
        }
    }

    // clean the board
    void clear_board() {
        for (int i = 0; i < height + 2; i++) {
            for (int j = 0; j < width + 2; j++)
                field[i][j] = ' ';
        }

        // set boundary
        for (int i = 0; i < width + 2; i++)
            field[0][i] = symbol;
        for (int i = 0; i < width + 2; i++)
            field[height + 1][i] = symbol;
        for (int i = 0; i < height + 2; i++)
            field[i][0] = symbol;
        for (int i = 0; i < height + 2; i++)
            field[i][width + 1] = symbol;
    }

    // returns board height
    int get_board_height() {
        return height;
    }

    // returns board width
    int get_board_width() {
        return width;
    }

    // set value on board
    void set_on_board(int row, int col, char c) {
        field[row][col] = c;
    }
    char get_board_point(int x, int y){
        return field[x][y];
    }
    


}; // object with name "field" of class "Board"

class Food {
private:
    position food_point,food_point2; // position of food on the board
    char symbol,symbol2;         // character symbol for representing food

public:
    // Constructor
    Food() : symbol('X') {}
    Food(int) : symbol2('$') {}
    

    // set food on board when given food's coordinates
    void set_food_position(int x, int y, Board& field) {
        food_point.x = x;
        food_point.y = y;
    }
    void set_food_position2(int x, int y, Board& field) {
        food_point2.x = x;
        food_point2.y = y;
    }
    friend class Snake;
    

    // randomly allocating food position on board with rand() function
    void reset_food_position(Board& field) {
        food_point.x = rand() % field.get_board_width();
        food_point.y = rand() % field.get_board_height();
        bool valid = false;
        while(!valid){
        char h = field.get_board_point(food_point.x+1,food_point.y+1);
        if (h==' ')
          valid = true;
        
        // Check if the position is outside the boundaries of the board
        if (food_point.x+1 <= 0 || food_point.x+1 > field.get_board_width() || food_point.y+1 <= 0 || food_point.y+1 > field.get_board_height()) {
               valid = false;
       }
         if ((food_point.x==food_point2.x)&&(food_point.y==food_point2.y)){
             valid = false;
        }
       if(valid==false){
           food_point.x = rand() % field.get_board_width();
           food_point.y = rand() % field.get_board_height();
        }
        }
    
    }

    void reset_food_position2(Board& field) {
        food_point2.x = rand() % field.get_board_width();
        food_point2.y = rand() % field.get_board_height();
        bool valid = false;
        while(!valid){
            char h =field.get_board_point(food_point2.x+1,food_point2.y+1);
        if (field.get_board_point(food_point2.x+1,food_point2.y+1)==' ')
          valid = true;
        
        // Check if the position is outside the boundaries of the board
        if (food_point2.x+1 <= 0 || food_point2.x+1 > field.get_board_width() || food_point2.y+1 <= 0 || food_point2.y+1 > field.get_board_height()) {
            valid = false;
        }
         if ((food_point.x==food_point2.x)&&(food_point.y==food_point2.y)){
             valid = false;
        }
    
       
       if(valid==false){
           food_point2.x = rand() % field.get_board_width();
           food_point2.y = rand() % field.get_board_height();
        }
        }
    }

    // returns x-coordinate of food
    int get_food_x() {
        return  food_point.x+1;
    }
    int get_food_x2() {
        return  food_point2.x+1;
    }

    // returns y-coordinate of food
    int get_food_y() {
        return  food_point.y+1;
    }
    int get_food_y2() {
        return  food_point2.y+1;
    }

    // return food symbol
    char get_food_symbol() {
        return symbol;
    }
    char get_food_symbol2() {
        return symbol2;
    }
    
};
Food eatable;
Food eatable2(2);



// Snake class definition
class Snake {
private:
    char body_head_symbol, body_part_symbol,body_head_symbol2,body_part_symbol2; // symbols for head and body(except) head of snake
    vector<position> body; 
    vector<position> body2;                  // storing body of snake body[0]->head, body[size-1]->tail
    int body_size,body_size2;                           // size of snake's body
    position head,head2; 
    int stay = 0;                          // position of snake's head on board
    enum direction { UP, DOWN, LEFT, RIGHT}; // directions of motion(w.r.t player in front of screen)
    direction dir;
    int dir2,previous2;                           // current direction of motion of snake's head
public:
    // Constructor
    Snake(int x = 3, int y = 3) : body_head_symbol('@'), body_part_symbol('o'), dir(DOWN), body_size(1) {
        // set position of head
        position tmp(x + 1, y + 1);
        body.push_back(tmp);

        head = body[0];
    }
    Snake(int x , int y ,int) : body_head_symbol2('%'), body_part_symbol2('='), dir2(0),previous2(0), body_size2(1) {
        // set position of head
        position tmp(x + 1, y + 1);
        body2.push_back(tmp);

        head2 = body2[0];
    }
    friend class Food;

    // gets player input for direction of head and store in dir
    // windows.h --> GetAsyncKeyState --> checks if key was pressed after a previous call
    // VK_[key_name] refers to virtual key code
    void get_input() {
        if (GetAsyncKeyState(VK_UP) && dir != DOWN){
            dir = UP;
            stay = 0;
        }
        else if (GetAsyncKeyState(VK_DOWN) && dir != UP){
            dir = DOWN;
            stay = 0;
        }
        else if (GetAsyncKeyState(VK_LEFT) && dir != RIGHT){
            dir = LEFT;
            stay = 0;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && dir != LEFT){
            dir = RIGHT;
            stay = 0;
        }
        else if(GetAsyncKeyState(VK_RCONTROL)){
            stay = 1;
        }
             
    }

    // movement of snake
    void move(Board& field) {
    
    if(stay == 1){
        return ;
    }
    // Calculate new head position
    position head_modify = {0, 0};
    if (dir == UP) {
        head_modify.y = -1;
    } else if (dir == DOWN) {
        head_modify.y = 1;
    } else if (dir == RIGHT) {
        head_modify.x = 1;
    } else if (dir == LEFT) {
        head_modify.x = -1;
    }

    position new_head = {head.x + head_modify.x, head.y + head_modify.y};
    // Update snake position
    for (int i = body_size - 1; i > 0; i--) {
        if (i < body.size()) { // Bounds check
            body[i] = body[i - 1];
        }
    }
    head = new_head;
    if (!body.empty()) {
        body[0] = head;
    }

    // Check collision with walls
    if (head.x <= 0 || head.y <= 0 || head.x >= 1 + field.get_board_width() || head.y >= 1 + field.get_board_height()) {
        throw string("SNAKE DEAD.....!!!!");
    }

    }

    void move2(Board& field) {

     bool backward = true;


     position head_modify2 = {0, 0};
     while(backward){
     dir2 = rand() % 4;
    // Calculate new head position
    

    if ((dir2 == 0)&&(previous2!=1)) {
        head_modify2.y = -1;
        head_modify2.x=0;
        if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2 == 0)){
            head_modify2.y=0;
            head_modify2.x = 1;
            previous2=2;
            if(head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height()){
                head_modify2.x= -1;
            }

        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==2)){
            head_modify2.y = 1;
            head_modify2.x = 0;
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==3)){
            head_modify2.y = 1;
            head_modify2.x = 0;
        }
        backward = false;
    }

    else if(dir2==0){
        backward=true;
    }
     if ((dir2 == 1)&&(previous2!=0)) {
        head_modify2.y = 1;
        head_modify2.x=0;
        if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==1)){
            head_modify2.y=0;
            head_modify2.x = 1;
            if(head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height()){
                head_modify2.x= -1;
            }
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==2)){
            head_modify2.y = -1;
            head_modify2.x = 0;
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==3)){
            head_modify2.y = -1;
            head_modify2.x = 0;
        }
        backward=false;
        
    }
    else if(dir2==1){
        backward=true;
    }
     if ((dir2 == 2)&&(previous2!=3)) {
        head_modify2.x = 1;
        head_modify2.y=0;
        if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==2)){
            head_modify2.y=1;
            head_modify2.x = 0;
            if(head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height()){
                head_modify2.y= -1;
            }
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==0)){
            head_modify2.x = -1;
            head_modify2.y=0;
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==1)){
            head_modify2.x = -1;
            head_modify2.y=0;
        }
        backward=false;
        
    }
    else if((dir2==2)){
        backward=true;
    }

     if ((dir2 == 3)&&(previous2!=2)) {
        head_modify2.x = -1;
        head_modify2.y=0;
        if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==3)){
            head_modify2.y=1;
            head_modify2.x = 0;
            if(head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height()){
                head_modify2.y= -1;
            }}
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==0)){
            head_modify2.x = 1;
            head_modify2.y=0;
        }
        else if((head2.x+head_modify2.x <= 0 || head2.y+head_modify2.y <= 0 || head2.x+head_modify2.x >= 1 + field.get_board_width() || head2.y+head_modify2.y >= 1 + field.get_board_height())&&(previous2==1)){
            head_modify2.x = 1;
            head_modify2.y=0;
        }// the logic of last 2 if is the snake moves to center rather than walls
        backward = false;
    
    }
    else if((dir2 == 3)){
        backward = true;
    }
     }

    if((head_modify2.x==1)&&(head_modify2.y==0)){
        previous2=2;
    }
    else if((head_modify2.x==0)&&(head_modify2.y==1)){
        previous2=1;
    }
    else if((head_modify2.x==0)&&(head_modify2.y==-1)){
        previous2=0;
    }
    else if((head_modify2.x==-1)&&(head_modify2.y==0)){
        previous2=3;
    }
    else{
        cout<< "the logic went wrong " << endl;
        throw string("logican error.....!!!!");
    }
    
    
    position new_head2 = {head2.x + head_modify2.x, head2.y + head_modify2.y};

    
    for (int i = body_size2 - 1; i > 0; i--) {
        if (i < body2.size()) { // Bounds check
            body2[i] = body2[i - 1];
        }
    }
    head2 = new_head2;
    if (!body2.empty()) {
        body2[0] = head2;
    }
    //cout << " your head : " << get_head_x() << " " <<get_head_y()<<" enemy head2 : "<<head2.x<<" "<<head2.y << endl;

    }

    // returns x-coordinate of head
    int get_head_x() {
        return head.x;
    }
    int get_head_x2() {
        return head2.x;
    }

    // returns y-coordinate of head
    int get_head_y() {
        return head.y;
    }
    int get_head_y2() {
        return head2.y;
    }

    // returns symbol of snake's head
    char get_head_symbol() {
        return body_head_symbol;
    }
    char get_head_symbol2() {
        return body_head_symbol2;
    }
    
    // returns symbol of snake's non-head
    char get_nonhead_symbol() {
        return body_part_symbol;
    }
    char get_nonhead_symbol2() {
        return body_part_symbol2;
    }


    

    // tells if snake(head) has reached food
    bool food_found(Food& foodie) {
        if (foodie.get_food_x() == head.x && foodie.get_food_y() == head.y) {
            // size increment
            body_size += 1;

            // adds a temporary position at end which is helpful while movement of snake(move method) after eating
            position tmp(-1, 0);
            body.push_back(tmp);
            return true;
        }
        return false;
    }
    bool food_found_2(Food& foodie) {
        if (foodie.get_food_x() == head2.x && foodie.get_food_y() == head2.y) {
            // size increment
            body_size2 += 1;

            // adds a temporary position at end which is helpful while movement of snake(move method) after eating
            position tmp(-2, 0);
            body2.push_back(tmp);
            return true;
        }
        return false;
    }


    bool food_found2(Food& foodie) {
        if (foodie.get_food_x2() == head.x && foodie.get_food_y2() == head.y) {
            // size increment
            body_size += 3;

            // adds a temporary position at end which is helpful while movement of snake(move method) after eating
            position tmp(-1, 0);
            body.push_back(tmp);
            body.push_back(tmp);
            body.push_back(tmp);
            return true;
        }
        return false;
    }
    bool food_found2_2(Food& foodie) {
        if (foodie.get_food_x2() == head2.x && foodie.get_food_y2() == head2.y) {
            // size increment
            body_size2 += 3;

            // adds a temporary position at end which is helpful while movement of snake(move method) after eating
            position tmp(-2, 0);
            body2.push_back(tmp);
            body2.push_back(tmp);
            body2.push_back(tmp);
            return true;
        }
        return false;
    }

    // set the snake's symbols on board at its position
    void set_snake_onboard(Board& field) {
        field.set_on_board(head.y, head.x, body_head_symbol);

        for (int i = 1; i < body.size(); i++)
            field.set_on_board(body[i].y, body[i].x, body_part_symbol);
    }
    void set_snake_onboard2(Board& field) {
        field.set_on_board(head2.y, head2.x, body_head_symbol2);

        for (int i = 1; i < body2.size(); i++)
            field.set_on_board(body2[i].y, body2[i].x, body_part_symbol2);

    }

    

    vector <position> give_body(){
        return body;
    }
    vector <position> give_body2(){
        return body2;
    }
    void head_collision(vector <position> temp_body,vector <position> temp_body2){
        if((temp_body.empty())||(temp_body2.empty())){
            return ;
        }
           if((temp_body[0].x==temp_body2[0].x)&&(temp_body[0].y==temp_body2[0].y)){
                //cout << " your head : " << head.x << " " <<head.y<<" enemy head : "<<head2.x<<" "<<head2.y;
                cout<< "you died :( head collision ! " << endl;
                 throw string("death.....!!!!");
             }
     }
     int head_body_collision(vector <position> temp_body,vector <position> temp_body2){
        cout << " your head : " << temp_body[0].x << " " <<temp_body[0].y<<" enemy head : "<<temp_body2[0].x<<" "<<temp_body2[0].y << endl;
        if((temp_body.size()<1)||(temp_body2.size()<1)){
            return 0;
        }
        for(int i = 1; i < temp_body.size();i++){
            //cout << "second  func" << endl;
            if((temp_body2[0].x == temp_body[i].x)&&(temp_body2[0].y == temp_body[i].y)){
                //cout << " your head : " << temp_body[0].x << " " <<temp_body[0].y<<" enemy head 2: "<<temp_body2[0].x<<" "<<temp_body2[0].y;
                if(temp_body2.size()>=temp_body.size()){
                cout<< "you died :( bots ate you ! " << endl;
                throw string("death.....!!!!");
                }
                else{
                    cout << " you won";
                    return 1;
                }
            }
        }
        return 2;
     }
     int eat_bot(vector <position> temp_body,vector <position> temp_body2){
        if((temp_body.empty())||(temp_body2.empty())){
            return 0;
        }
        for(int i = 1;i<temp_body2.size();i++){
            if((temp_body[0].x == temp_body2[i].x)&&(temp_body[0].y == temp_body2[i].y)){
                for(int j = 0;j<temp_body2.size();j++){
                    position tempo(-3,0);
                    body.push_back(tempo);
                }
                return 2;
            }
          }
          return 3;
        }
    void kill_bot(){
        if((body2.empty())){
            return ;
        }
        position temp(-199,0);
                for (int i = 0;i<body2.size();i++){
                   body2[i]=temp;
                }
                head2 = temp;
     }
    

};
Snake player;
Snake bot(8,3,2); // object "player" and "bot" of class "Snake"



// hide cursor function only in windowed mode (i.e not full screen)
// Reference : https://superuser.com/questions/1496322/how-do-i-remove-hide-the-cursor-the-blinking-underscore-character-in-cmd-exe

void hide_cursor() {
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}


// main function
int main() {
    bool u = true;
    int a, b;
    while (u) {
        cout << "enter height (10-100) width=height : " << endl;
        cin >> a;
        b = a;
        if ((a >= 10) && (a <= 32)) {
            u = false;
        }
    }
    Board field(a, b);
    // hides cursor
    hide_cursor();

    // current unix time in seconds as seed for rand function
    srand(time(0));

    // sets initial food position
    eatable.set_food_position(6, 6, field);
    eatable2.set_food_position2(8,8, field);
    // loop until the player kills snake
    bool bot_alive = true;
    while (1) {
       // cout << "hi"<<endl;
        field.clear_board(); // clears board
        player.get_input();  // finds if user has pressed any key until previous execution of loop

        
        //cout << "after collision"<<endl;
        //bot.head_body_collision2();

        // moves snake
        try {
            player.move(field);
        }
        catch (string err) {
            field.clear_board();
            cout << err << endl;
            system("pause"); // pause system and wait for key press, MS Windows (NOT Linux)
            return 0;
        }
        if(bot_alive){
        try {
            bot.move2(field);
        }
        catch (string err) {
            field.clear_board();
            cout << err << endl;
            system("pause"); // pause system and wait for key press, MS Windows (NOT Linux)
            return 0;
        }
        }
        //cout << " we reached here sir "<< endl;
        

        field.set_on_board(eatable.get_food_y(), eatable.get_food_x(), eatable.get_food_symbol()); // set food on board
        field.set_on_board(eatable2.get_food_y2(), eatable2.get_food_x2(), eatable2.get_food_symbol2());
        //cout << "we reached here sir 2" << endl;
        player.set_snake_onboard(field);
        if(bot_alive){
        bot.set_snake_onboard2(field);// set snake on board
        }
        
        
        
        // if snake(head) has found food resets food randomly
        if (player.food_found(eatable)) {
            eatable.reset_food_position(field);
            //cout << "reset1 successful"<<endl;
        }
        else if (player.food_found2(eatable2)) {
            eatable2.reset_food_position2(field);
            //cout << "reset 2 succesful "<< endl;
        }
        if(bot_alive){
        if (bot.food_found_2(eatable)) {
            eatable.reset_food_position(field);
    
        }
        else if (bot.food_found2_2(eatable2)) {
            eatable2.reset_food_position2(field);
            //cout << "reset 2 succesful "<< endl;
        }
        }
        //cout << "before collision"<<endl;
        if(bot_alive){
        vector<position> temp_body = player.give_body();
        vector<position> temp_body2 = bot.give_body2();

        bot.head_collision(temp_body,temp_body2);
        //cout << "between collision"<<endl;
        int hb_result = player.head_body_collision(temp_body,temp_body2);
        //cout << " yo" << endl;
        int col_result = player.eat_bot(temp_body,temp_body2);
        //cout << "we reached here sir 3" << endl;
        if((col_result==2)||hb_result == 1){
            bot.kill_bot();
            bot_alive=false;
        }
        }

        field.show_board(); // prints board

        Sleep(400);        // Windows.h --> milliseconds for which to stop execution
        system("cls"); // clear screen
    }

    return 0;
}
