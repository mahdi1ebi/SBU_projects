#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;


//start is the first point of the shape move to game
//scr and gameTime use for counting the score and the time of playing
//hardshiplevel use for make change in game according to the level
int row, column, start, scr, hardshipLevel;
string showlevel;
int gameTime, gameTime_inthemoment, minute, sec;  
int **game;

//newmatrises help us to show the next shape in the easy level of the game
int nextmatris3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int nextmatris2[2][2] = {{0,0},{0,0}};
int nextmatris4[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

int matris3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
int matris2[2][2] = {{0,0},{0,0}};
int matris4[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

//all these booleans help for the payse key to found what happend to the game after the player pause it
bool pauseformenu,pauseforexit,pause = false;
//name is the player name and line use for save and sort datas in file
string line, name;

//struct use for sort datas
struct scoreBoard{
    string name;
    int score;
    int time;
};
scoreBoard board[100000];

void sortArray();
void sortData();

//help us for print the chart and matrises
void gotoxy(int x , int y){
    HANDLE hStsoout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD podition = {(short)x , (short)y};

    SetConsoleCursorPosition(hStsoout , podition);
}

//theGame function make the main matris for the play
void theGame(){
    for (int i = 0 ; i < row ; i++){
        for ( int j = 0 ; j < column+1 ; j++){
            game[i][j] = 0;
        }
    }
    for (int i = 0 ; i < row+1 ; i++){
        game[i][0] = -1;
        game[i][column+1] = -1;
    }
    for (int i = 0 ; i < column+2 ; i++){
        game[row][i] = -1;
    }
}

//shpe functions use for make the matris to make the play
void shape1(int matris[2][2]){              //##
                                            //##
    for (int i = 0 ; i < 2 ; i++){
        for (int j = 0 ; j < 2 ; j++){
                matris[i][j] = 8;
        }
    }
}

void shape2(int matris[3][3]){
                                          //#   (2)
    for (int i = 0 ; i < 3 ; i++){        //###
        for (int j = 0 ; j < 3 ; j++){
            matris[i][j] = 0;
        }
    }

    for (int i = 0 ; i < 3 ; i++){
        matris[1][i] = 2;
    }
    matris[0][0] = 2;
}

void shape3(int matris[3][3]){
                                        //  #   (3)
    for (int i = 0 ; i < 3 ; i++){      //###
        for (int j = 0 ; j < 3 ; j++){
            matris[i][j] = 0;
        }
    }

    for (int i = 0 ; i < 3 ; i++){
        matris[1][i] = 3;
    }
    matris[0][2] = 3;
}

void shape4(int matris[3][3]){

    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            matris[i][j] = 0;
        }
    }
                                        // #   (4)
    for (int i = 0 ; i < 3 ; i++){      //###
        matris[1][i] = 4;
    }
    matris[0][1] = 4;
}

void shape5(int matris[3][3]){

    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            matris[i][j] = 0;
        }
    }
                                            // ##  (5)
    for (int i = 1 ; i < 3 ; i++){          //##
        matris[0][i] = 5;
    }

    for (int i = 0 ; i < 2 ; i++){
        matris[1][i] = 5;
    }
}

void shape6(int matris[3][3]){
                                            //##     (6)
                                            // ##
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            matris[i][j] = 0;
        }
    }

    for (int i = 0 ; i < 2 ; i++){
        matris[0][i] = 6;
    }

    for (int i = 1 ; i < 3 ; i++){
        matris[1][i] = 6;
    }
}

void shape7(int matris[4][4]){
                                             //##### (7)
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            matris[i][j] = 0;
        }
    }

    for (int i = 0 ; i < 4 ; i++){
        matris[0][i] = 7;
    }
}

//counting the number of the digits of scr variable because we need it in tne printChart function
int numofDigits(int scr){
    int num = 0;
    while (scr > 0){
        scr /= 10;
        num++;
    }

    return num;
}

void timeCalculation(){
    minute = gameTime_inthemoment/60;
    sec = gameTime_inthemoment % 60;
}

//use this function in printChart function to show the next shape in easy level of the play to the player
void printNextShape(int ran){

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 20; i++){
        cout << " ";
    }
    cout << "Next Shape  " << endl << endl;

    if (ran == 1){
        shape1(nextmatris2);
        for (int i = 0 ; i < 2 ; i++){
            for (int k = 0; k < 23; k++){
                 cout << " ";
            }
            for (int j = 0 ; j < 2 ; j++){
                SetConsoleTextAttribute(console ,17);
                cout <<"\u2588\u2588";
                SetConsoleTextAttribute(console , 15);
            }
            cout << endl;
        }
    }

    if (ran == 2){
        shape2(nextmatris3);
        for (int i = 0 ; i < 3 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 3 ; j++){
                if (nextmatris3[i][j] != 0){
                    SetConsoleTextAttribute(console ,34);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }

    if (ran == 3){
        shape3(nextmatris3);
        for (int i = 0 ; i < 3 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 3 ; j++){
                if (nextmatris3[i][j] != 0){
                    SetConsoleTextAttribute(console ,51);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }

    if (ran == 4){
        shape4(nextmatris3);
        for (int i = 0 ; i < 3 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 3 ; j++){
                if (nextmatris3[i][j] != 0){
                    SetConsoleTextAttribute(console ,68);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }

    if (ran == 5){
        shape5(nextmatris3);
        for (int i = 0 ; i < 3 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 3 ; j++){
                if (nextmatris3[i][j] != 0){
                    SetConsoleTextAttribute(console ,85);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }

    if (ran == 6){
        shape6(nextmatris3);
        for (int i = 0 ; i < 3 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 3 ; j++){
                if (nextmatris3[i][j] != 0){
                    SetConsoleTextAttribute(console ,102);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }

    if (ran == 7){
        shape7(nextmatris4);
        for (int i = 0 ; i < 4 ; i++){
            for (int k = 0; k < 21; k++){
                cout << " ";
            }
            for (int j = 0 ; j < 4 ; j++){
                if (nextmatris4[i][j] != 0){
                    SetConsoleTextAttribute(console ,136);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                else {
                    cout <<"  ";
                }
            }
            cout << endl;
        }
    }
}

void printChart(int nextran){

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int sizeofname =size(name)+3;
    timeCalculation();
    
    gotoxy(15,0);
    cout <<"\u2554";
    for (int i = 0; i < 9+sizeofname ; i++){
        cout <<"\u2550";
    }
    cout <<"\u2557";
    for (int i=1 ; i<10;i++){
    gotoxy(15,i);
    cout <<"\u2551";
    gotoxy(25 + sizeofname,i);   
    cout <<"\u2551";
    }
    gotoxy(15,10);
        cout<<"\u255A";
    for (int i = 0 ; i < 9+sizeofname; i++){
        cout <<"\u2550";
    }
    cout <<"\u255D";    
    /////////////
    gotoxy(17,1);
    cout <<"NAME : "<<name;
    gotoxy(17,3);
    cout <<"MOOD : "<< showlevel;
    gotoxy(17,5);
    cout <<"TIME : "<< minute << ":" << sec ;
    gotoxy(17,7);
    cout <<"SIZE : "<< row << "*" << column;
    gotoxy(17,9);
    cout <<"SCORE : "<<scr;
    //////////////////////
    gotoxy(40+sizeofname,0);
    for (int i =0;i<5;i++){
         cout<<"🟥";
    }
    for (int i=1 ; i<9 ; i++){
        gotoxy(46+sizeofname,i);
        cout<<"🟥";

    }
    gotoxy(49+sizeofname,0);
    for (int i=0 ; i<5;i++){            //avalin dandone E
        cout <<"🟧";
    }
    gotoxy(54+sizeofname,4);
    cout <<" ";
    for (int i=0 ; i<4;i++){    
        cout<<"🟧";
    }
    gotoxy(54+sizeofname,8);
    cout <<" ";
    for (int i=0 ; i<4;i++){
        cout<<"🟧";
    }    
    for (int i=1 ; i<9;i++){
        gotoxy(53+sizeofname,i);
        cout <<"🟧";
    }
    gotoxy(58+sizeofname,0);
    for (int i=0 ; i<5;i++){
        cout <<"🟨";
    }
    for (int i =1 ;i<9;i++){
        if (i==4||i==8){
            gotoxy(68+sizeofname,i);
            cout <<"🟨";
        }
        else{
            gotoxy(72+sizeofname,i);
            cout <<"🟨";
        }    
    }
    gotoxy(67+sizeofname,0);
    for(int i =0 ; i<3;i++){
        cout <<"🟦";
    }
    gotoxy(87+sizeofname,1);
    cout <<"🟦";
    gotoxy(89+sizeofname,2);
    cout<<"🟦";
    gotoxy(87+sizeofname,3);
    cout<<"🟦";
    ////////////////
    gotoxy(85+sizeofname,5);
    cout<<"🟦";
    gotoxy(86+sizeofname,6);
    cout<<"🟦";
    gotoxy(87+sizeofname,7);
    cout<<"🟦";
    gotoxy(84+sizeofname,8);
    cout<<"🟦";

    for (int i=1;i<9;i++){
        gotoxy(79+sizeofname,i);
        if (i==4){
            gotoxy(75+sizeofname,i);
            for(int i=0;i<3;i++){
                cout <<"🟦";
            }
        }
        if (i==4||i==8){
            gotoxy(75+sizeofname,i);
            cout<<"🟦";
        }
        else{
            gotoxy(79+sizeofname,i);
            cout <<"🟦";
        }    
    }
    gotoxy(78+sizeofname,0);
    for (int i=0 ;i<3;i++){
        cout <<"🟪";
    }
    for(int i=1 ; i<9; i++ ){
        if (i==4){
            gotoxy(89+sizeofname,i);
            cout<<"🟪";
        }
        else if (i==8){
            gotoxy(87+sizeofname,i);
            cout<<"🟪 🟪 🟪";
        }
        else if (i!=8 && i!=4){
            gotoxy(94+sizeofname,i);
            cout<<"🟪";
        }
    }
    gotoxy(85+sizeofname,0);
    for (int i=0 ; i<4;i++){
        cout<<"🟩";
    }
    for(int i=1;i<5;i++){
        if (i==4){
            for (int z=0;z<4;z++){
                gotoxy(95+sizeofname+z,i);
                cout <<"🟩";
            }
        }
        gotoxy(98+sizeofname,i);
        cout <<"🟩";
    }
    for (int i=0 ; i<3 ; i++){
    gotoxy(108+sizeofname,5+i);
    cout <<"🟩";
    }
    gotoxy(92+sizeofname,8);
    for (int i=0 ; i<4;i++){
        cout <<"🟩";
    }
    /////////////////////////////
    cout << endl << endl << endl << endl;
    if (hardshipLevel ==500){
        gotoxy(15,11);
        cout<<"\u2554";
        for (int i=0 ; i<19 ; i++){
            cout <<"\u2550";
        }
        cout <<"\u2557";
        cout<<endl;
        printNextShape(nextran);
        for (int i=0 ;i<5 ; i++){
            gotoxy(35,12+i);
            cout<<"\u2551";
        }
        gotoxy(35,17);
        cout <<"\u255D";
        for (int i=0 ; i<5 ; i++){
            gotoxy(15,12+i);
            cout <<"\u2551";
        }
        gotoxy(15,17);
        cout<<"\u255A";
        for(int i=0 ; i<19 ; i++){
            cout <<"\u2550";
        }
        
    }

        cout <<endl <<endl<< endl;

        for(int i = 1; i < row; i++){

            for (int z=0 ; z<50; z++){
                    cout <<" ";
            }
        
        for (int j = 1; j < column+1; j++){
            if (game[i][j] != 0){

                if (game[i][j] == 8){
                        
                    SetConsoleTextAttribute(console ,17);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                    
                else if (game[i][j] == (-8)){
                        
                    SetConsoleTextAttribute(console ,17);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                    
                if (game[i][j] == 2){
                    
                    SetConsoleTextAttribute(console ,34);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                    
                if (game[i][j] == (-2)){
                    
                    SetConsoleTextAttribute(console ,34);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == 3){
                    
                    SetConsoleTextAttribute(console ,51);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == (-3)){
                    
                    SetConsoleTextAttribute(console ,51);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }
                    
                else if (game[i][j] == 4 ){
                    
                    SetConsoleTextAttribute(console ,68);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == (-4)){
                    
                    SetConsoleTextAttribute(console ,68);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == 5 ){
                    
                    SetConsoleTextAttribute(console ,85);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == (-5) ){
                    
                    SetConsoleTextAttribute(console ,85);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == 6){
                    
                    SetConsoleTextAttribute(console ,102);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == (-6)){
                    
                    SetConsoleTextAttribute(console ,102);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == 7){
                    
                    SetConsoleTextAttribute(console ,136);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                else if (game[i][j] == (-7)){
                    
                    SetConsoleTextAttribute(console ,136);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }

                
                else if (game [i][j] == (-1)){
                    SetConsoleTextAttribute(console , 150);
                    cout <<"\u2588\u2588";
                    SetConsoleTextAttribute(console , 15);
                }    
            }
            
            else if (game [i][j]== 0 ){
                SetConsoleTextAttribute(console , 15);
                cout <<"\u2588\u2588";
                SetConsoleTextAttribute(console , 15);
            }        
            
        }
        cout << endl;
        
    }
}

//all rotate functions use for rtating the shape and check that if the shape can rotate in the game and there is not something in the way of rotating the shape or not
void rotate3_right(int shape[3][3]){              //rotate 3*3
    int save[3][3];
    for (int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            save[i][j] = shape[i][j];
        }
    }

    for (int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            shape[j][2-i] = save[i][j];
        }
    }
}

void rotate3_left(int shape[3][3]){
    int save[3][3];
    for (int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            save[i][j] = shape[i][j];
        }
    }

    for (int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            shape[2-j][i] = save[i][j];
        }
    }
}

void rotate4_right(int shape[4][4]){              //rotate 4*4
    int save[4][4];
    for (int i = 0 ; i < 4 ; i++){
        for ( int j = 0 ; j < 4 ; j++){
            save[i][j] = shape[i][j];
        }
    }

    for (int i = 0 ; i < 4 ; i++){
        for ( int j = 0 ; j < 4 ; j++){
            shape[j][3-i] = save[i][j];
        }
    }
}

void rotate4_left(int shape[4][4]){              //rotate 4*4
    int save[4][4];
    for (int i = 0 ; i < 4 ; i++){
        for ( int j = 0 ; j < 4 ; j++){
            save[i][j] = shape[i][j];
        }
    }

    for (int i = 0 ; i < 4 ; i++){
        for ( int j = 0 ; j < 4 ; j++){
            shape[3-j][i] = save[i][j];
        }
    }
}

bool rotateCheck3_right(int count_row, int ran, int count_column){

    int check[3][3];
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            check[i][j] = matris3[i][j];
        }
    }
    rotate3_right(check);

    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (check[i][j] != 0){
                if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                    return 0;
                }
            }
        }
    }

    return 1;
}

bool rotateCheck3_left(int count_row, int ran, int count_column){

    int check[3][3];
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            check[i][j] = matris3[i][j];
        }
    }
    rotate3_left(check);


    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (check[i][j] != 0){
                if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                    return 0;
                }
            }
        }
    }

    return 1;
}

bool rotateCheck4_right(int count_row, int ran, int count_column){

    int check[4][4];
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            check[i][j] = matris4[i][j];
        }
    }
    rotate4_right(check);


    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (check[i][j] != 0){
                if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                    return 0;
                }
            }
        }
    }

    return 1;
}

bool rotateCheck4_left(int count_row, int ran, int count_column){

    int check[4][4];
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            check[i][j] = matris4[i][j];
        }
    }
    rotate4_left(check);


    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (check[i][j] != 0){
                if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                    return 0;
                }
            }
        }
    }

    return 1;
}

//make the shape go to the right in game
void right (int& count_column){
    count_column++;
}

//check if the right sight of the shape is empty and shape can move to the right or not
bool rightCheck(int ran){
    if (ran == 1){
        for (int i = 0 ; i < row ; i++){
            for ( int j = column ; j > 0 ; j--){
                if (game[i][j] == 8){
                    if (game[i][j+1] != 0 && game[i][j+1] != 8){
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
    else {
        for (int i = 0 ; i < row ; i++){
            for ( int j = column ; j > 0 ; j--){
                if (game[i][j] == ran){
                    if (game[i][j+1] != 0 && game[i][j+1] != ran){
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
}

//make the shape go to the left in game
void left (int& count_column){
    count_column--;
}

//check if the left sight of the shape is empty and shape can move to the left or not
bool leftCheck(int ran){
    if (ran == 1){
        for (int i = 0 ; i < row ; i++){
            for ( int j = 1 ; j < column+1 ; j++){
                if (game[i][j] == 8){
                    if (game[i][j-1] != 0 && game[i][j-1] != 8){
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
    else {
        for (int i = 0 ; i < row ; i++){
            for ( int j = 1 ; j < column+1 ; j++){
                if (game[i][j] == ran){
                    if (game[i][j-1] != 0 && game[i][j-1] != ran){
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
}

//the function for counting the score
void score(){
    for ( int i = row-1 ; i > 0 ; i--){
        bool fill = true;
        for (int j = 1 ; j < column+1; j++){
            if (game[i][j] == 0){
                fill = false;       //check if there id a full line in the play or not 
                break;
            }
        }

        if (fill){          //if there is a full line the player's score increase and that line will be earase from the game chart 
            scr += 10;
            for (int j = 1; j < column+1; j++){
                game[i][j]=0;
            }

            for (int k = i; k > 0; k--){
                for (int j = 1; j < column+1 ; j++){
                    game[k][j]=game[k-1][j];
                }
            }
            for (int j = 1; j < column+1 ; j++){
                game[0][j] = 0;
            }
        }
    }
}

void addShapetoGame(int ran, int count_column, int count_row){
    if (ran == 1){
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                if (matris2[i][j] != 0){
                    game[i+count_row][j+start+count_column] = matris2[i][j];
                }
            }
        }
    }

    else if (ran == 7){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (matris4[i][j] != 0){
                    game[i+count_row][j+start+count_column] = matris4[i][j];
                }
            }
        }
    }

    else{
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (matris3[i][j] != 0){
                    game[i+count_row][j+start+count_column] = matris3[i][j];
                }
            }
        }
    }
}

//check if the line under the shape is empty or not and can the shape go down in the play or not
void checkGametogoDown(int ran,int count_column, int count_row, bool& space){
    if (ran == 1){
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                if (matris2[i][j] != 0){
                    if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != 8){
                        space = true;
                    }
                }
            }
        }
    }

    else if (ran == 7){
        for(int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (matris4[i][j] != 0){
                    if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                        space = true;
                    }
                }
            }
        }
    }

    else{
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (matris3[i][j] != 0){
                    if (game[i+1+count_row][j+start+count_column] != 0 && game[i+1+count_row][j+start+count_column] != ran){
                        space = true;
                    }
                }
            }
        }
    }
}

//when the shape stop in the game the matris we made for control the play should edit and this function do the edits that game needs
void editGame(int ran, int count_column, int count_row, bool space){
    if (ran == 1){
        if (space){
            for(int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    if (matris2[i][j] != 0){
                        game[i+count_row][j+start+count_column] = (-1)*8;
                    }
                }
            }
        }

        if (!space){
            for(int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    if (matris2[i][j] != 0){
                        game[i+count_row][j+start+count_column] = 0;
                    }
                }
            }
        }

    }

    else if (ran == 7){
        if (space){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    if (matris4[i][j] != 0){
                        game[i+count_row][j+start+count_column] = (-1)*ran;
                    }
                }
            }
        }

        if (!space){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    if (matris4[i][j] != 0){
                        game[i+count_row][j+start+count_column] = 0;
                    }
                }
            }
        }
    }

    else{
        if (space){
            for(int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (matris3[i][j] != 0){
                        game[i+count_row][j+start+count_column] = (-1)*ran;
                    }
                }
            }
        }

        if (!space){
            for(int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if (matris3[i][j] != 0){
                        game[i+count_row][j+start+count_column] = 0;
                    }
                }
            }
        }
    }
}

//when the player hit the down arrow the shape in the game should move down fast until it stop
void moveDownFast(int ran, int count_column, bool space, int& count_row, int nextran){
    if (ran == 1){
        while(1){
            system("cls");

            addShapetoGame(ran,count_column,count_row);

            printChart(nextran);

            checkGametogoDown(ran,count_column,count_row,space);

            if (space){
                editGame(ran,count_column,count_row,space);
                break;
            }

            if (!space){
                editGame(ran,count_column,count_row,space);
            }

            Sleep(5);
            count_row++;
        }
    }

    else if (ran == 7){
        while(1){
            system("cls");

            addShapetoGame(ran,count_column,count_row);

            printChart(nextran);

            checkGametogoDown(ran,count_column,count_row,space);

            if (space){
                editGame(ran,count_column,count_row,space);
                break;
            }

            if (!space){
                editGame(ran,count_column,count_row,space);
            }

            Sleep(5);
            count_row++;
        }

    }

    else {
        while(1){
            system("cls");

            //add shape in game**
            addShapetoGame(ran,count_column,count_row);

            printChart(nextran);

            checkGametogoDown(ran,count_column,count_row,space);

            if (space){
                editGame(ran,count_column,count_row,space);
                break;
            }

            if (!space){
                editGame(ran,count_column,count_row,space);
            }

            Sleep(5);
            count_row++;
        }
    }
}

//all the variable we need in the play function initialize in this function
void initializeVariables(int& count_row, int& count_column, bool& space, bool& move){
    count_row = 0;
    count_column = 0;
    space = false;
    move = false;
}

//according to the selected random number the shape make in the matris for use in the code 
void makeShape(int ran){

    if (ran == 1){
        shape1(matris2);
    }

    if (ran == 2){
        shape2(matris3);
    }

    if (ran == 3){
        shape3(matris3);
    }

    if (ran == 4){
        shape4(matris3);
    }

    if (ran == 5){
        shape5(matris3);
    }

    if (ran == 6){
        shape6(matris3);
    }

    if (ran == 7){
        shape7(matris4);
    }
}

//this function make for whenever player hit the esc buttom to pause the game
void pauseShow(){
    system("cls");

    cout << "1.Back to the Game\n2.Back to the menu\n3.leaderboard\n4.Exit";

    char input = getch();

    if (input == '1'){

    }

    if (input == '2'){
        system("cls");
        cout << "Are you sure you want to go back to the menu ?(your play will be close!)\n1.yes\n2.No";
        char sure = getch();
        if (sure == '1'){
            pause = true;
            pauseformenu = true;
        }
        if (sure == '2'){
            pauseShow();
        }
    }

    if (input == '3'){
        system("cls");
        sortData();

        char back = getch();
        pauseShow();
    }

    if (input == '4'){
        system("cls");
        cout << "Are you sure you want to quit ?\n1.yes\n2.No";
        char sure = getch();
        if (sure == '1'){
            system("cls");
            cout << "\033[0;34m" << "Thanks for Playing our Game >_<  " << "\033[0m";
            pause = true;
            pauseforexit = true;
        }
        if (sure == '2'){
            pauseShow();
        }
    }
}

//this function is the main function for make the game
void play(){

    system("cls");
    theGame();
    srand(time(0));
    scr = 0;
    int ran = (rand()%7)+1;  //choose a random number for put a random shape in the game
    auto startTime = std::chrono::high_resolution_clock::now();    //start the timer
    auto startTimeinGame = std::chrono::high_resolution_clock::now();    //start the timer

    while(1){
            
            bool y = false;
            for (int i = 1; i < column+1; i++){         //check if there is any space to add another shape to the game or not
                if (game[1][i] != 0)                    //if there is no space, end the game
                    y = true;
            }

            if(y){
                auto endTime = std::chrono::high_resolution_clock::now();  //end the timer
                system("cls");
                cout << "Game Over\n" << "Your Score : " << scr << endl;
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
                gameTime = duration.count();     //count the time of the player playing and save it in gameTime variuable
                cout << "Your Time is : " << gameTime/60 << ":" << gameTime % 60 << "\n";
                break;
            }

            //when the player choose to close the game or go back to the menu in the middle of the game, code can find it with pause boolean and end the play function
            if (pause){      
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
                gameTime = duration.count();    //count the time of the player playing and save it in gameTime variuable
                break;
            }

            score();    //count the score

            srand(time(0));
            int nextran = (rand()%7)+1;   //choose another random number to know about the next shape and show it to the player 
            makeShape(ran);

            //count_row or column is for show where the shape should be in the main matris
            start = (column + 3)/2; 
            int count_row, count_column;
            //booleans help to find that the shapes could move or not
            //move is the boolean that get true when the player hit the down arrow and it prevent other actions until the shape stop in the play  
            bool space, move;
            bool moveRight,moveLeft;

            if (ran == 1){             
                initializeVariables(count_row,count_column,space,move);

                while (1){
                    while (!kbhit()){
    				    system("cls");

                        addShapetoGame(ran,count_column,count_row);


                        auto endTimeinGame = std::chrono::high_resolution_clock::now();  //end the timer
                        auto durationGame = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeinGame - startTimeinGame);
                        gameTime_inthemoment = durationGame.count()/1000;
    				    printChart(nextran);
                        
                        moveRight = rightCheck(ran);
                        moveLeft = leftCheck(ran);

                        checkGametogoDown(ran,count_column,count_row,space);

                        if (space){
                            editGame(ran,count_column,count_row,space);
                            break;
                        }

                        if (!space){
                           editGame(ran,count_column,count_row,space);
                        }

                        Sleep(hardshipLevel);
                        count_row++;

                    }

                    if (space){
                        break;
                    }

                    char input = getch();
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

                    if (input == 77){       //move the shape to right when player hit the right arrow
                        if (moveRight && !move){
                            right(count_column);
                        }

                    }

                    if (input == 75){       //move the shape to left when player hit the left arrow
                        if (moveLeft && !move){
                            left(count_column);
                        }
                    }

                    if (input == 80){       //move the shape down so fast when player hit the down arrow
                        moveDownFast(ran, count_column, space, count_row, nextran);
                        move = true;
                    }

                    if (input == 27){       //pause the game and show the pause menu when the player hit the esc key
                        pauseShow();
                        if (pause){
                            break;
                        }
                    }

                }
    		}

    		if (ran > 1 && ran < 7){
                initializeVariables(count_row,count_column,space,move);

                while (1){
                    while (!kbhit()){
                        system("cls");

                        addShapetoGame(ran,count_column,count_row);

                        auto endTimeinGame = std::chrono::high_resolution_clock::now();  //end the timer
                        auto durationGame = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeinGame - startTimeinGame);
                        gameTime_inthemoment = durationGame.count()/1000;
                        printChart(nextran);

                        moveRight = rightCheck(ran);
                        moveLeft = leftCheck(ran);

                        checkGametogoDown(ran,count_column,count_row,space);

                        if (space){
                            editGame(ran,count_column,count_row,space);
                            break;
                        }

                        if (!space){
                            editGame(ran,count_column,count_row,space);
                        }

                        Sleep(hardshipLevel);
                        count_row++;
                    }

                    if (space){
                        break;
                    }

                    char input = getch();
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

                    if (input == 77){       //move the shape to right when player hit the right arrow
                        if (moveRight && !move){
                            right(count_column);
                        }

                    }

                    if (input == 75){       //move the shape to left when player hit the left arrow
                        if (moveLeft && !move){
                            left(count_column);
                        }
                    }

                    if (input == 80){       //move the shape down so fast when player hit the down arrow
                        moveDownFast(ran, count_column, space, count_row, nextran);
                        move = true;
                    }

                    if (input == 27){       //pause the game and show the pause menu when the player hit the esc key
                        pauseShow();
                        if (pause){
                            break;
                        }
                    }

                    if (input == 'x' || input == 'X'){      //rotate right when player hit x 
                        bool y = rotateCheck3_right(count_row, ran, count_column);
                        if (y){
                            rotate3_right(matris3);
                        }
                    }

                    if (input == 'z' || input == 'Z'){      //rotate the shape to the left when player hit z
                        bool y = rotateCheck3_left(count_row, ran, count_column);
                        if (y){
                            rotate3_left(matris3);
                        }
                    }

                }
            }

    		if (ran == 7){
                initializeVariables(count_row,count_column,space,move);

        		while (1){
                    while (!kbhit()){
    				    system("cls");

                        //add shape to game
                        addShapetoGame(ran,count_column,count_row);

                        auto endTimeinGame = std::chrono::high_resolution_clock::now();  //end the timer
                        auto durationGame = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeinGame - startTimeinGame);
                        gameTime_inthemoment = durationGame.count()/1000;
                        printChart(nextran);

                        moveRight = rightCheck(ran);
                        moveLeft = leftCheck(ran);

                        checkGametogoDown(ran,count_column,count_row,space);;

                        if (space){
                            editGame(ran,count_column,count_row,space);
                            break;
                        }

                        if (!space){
                            editGame(ran,count_column,count_row,space);
                        }

        				Sleep(hardshipLevel);
        				count_row++;
                    }

                    if (space){
                        break;
                    }

                    char input = getch();
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

                    if (input == 77){       //move the shape to right when player hit the right arrow
                        if (moveRight && !move){
                            right(count_column);
                        }

                    }

                    if (input == 75){       //move the shape to left when player hit the left arrow
                        if (moveLeft && !move){
                            left(count_column);
                        }
                    }

                    if (input == 80){       //move the shape down so fast when player hit the down arrow
                        moveDownFast(ran, count_column, space, count_row, nextran);
                        move = true;
                    }

                    if (input == 27){       //pause the game and show the pause menu when the player hit the esc key
                        pauseShow();
                        if (pause){
                            break;
                        }
                    }

                    if (input == 'x' || input == 'X'){      //rotate the shape to the right when player hit x
                        bool y = rotateCheck4_right(count_row, ran, count_column);
                        if (y){
                            rotate4_right(matris4);
                        }
                    }

                     if (input == 'z' || input == 'Z'){     //rotate the shape  to the left when player hit z
                        bool y = rotateCheck4_left(count_row, ran, count_column);
                        if (y){
                            rotate4_left(matris4);
                        }
                    }

                }
            }

            ran = nextran;           
    }
}

void menu(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i=0 ; i<51 ; i++){
        gotoxy(18+i,0);
        SetConsoleTextAttribute(console ,8);
        cout << "\u2573";
    }

    for (int i=0 ; i<8; i++){
        gotoxy(18,1+i);
        cout << "\u2573";
    }
    for (int i=0 ; i<8 ; i++){
        gotoxy(68,1+i);
        cout <<"\u2573";
    }
    for (int i=0 ; i<51 ; i++){
        gotoxy(18+i,9);
        cout <<"\u2573";
    }

    gotoxy(22,2);
    cout << "\033[0;35m"<< "¤¸¸.•´¯"<< "\33[0m"<< "\033[0;36m"<< "`•¸¸.•..>>"<< "\33[0m";
    cout << "\033[0;34m"<< " TETRIS "<< "\33[0m";
    cout << "\033[0;36m"<<"<<..•.¸¸•´"<< "\33[0m"<< "\033[0;35m"<<"¯`•.¸¸¤"<< "\33[0m";
    
    gotoxy(38,4);
    SetConsoleTextAttribute(console ,2);
    cout << "1." <<"ℕ𝕖𝕨 𝔾𝕒𝕞𝕖";
    
    gotoxy(37,5);
    SetConsoleTextAttribute(console ,8);
    cout << "2."<<"𝕃𝕖𝕒𝕕𝕖𝕣𝕓𝕠𝕒𝕣𝕕";

    gotoxy(37,6);
    SetConsoleTextAttribute(console ,6);
    cout << "3."<< "ℍ𝕠𝕨 𝕥𝕠 ℙ𝕝𝕒𝕪";

    gotoxy(40,7);
    SetConsoleTextAttribute(console ,4);
    cout << "4."<< "𝔼𝕩𝕚𝕥";
    SetConsoleTextAttribute(console ,4);
}

void help(){

    for (int i = 0 ; i < 31 ; i++){
        cout << " ";
    }
    cout << "CONTROL KEYS" << endl << endl;

    for (int i = 0 ; i < 26 ; i++){
        cout << " ";
    }
    cout << "Left Arrow - Move Left" << endl;

    for (int i = 0 ; i < 25 ; i++){
        cout << " ";
    }
    cout << "Right Arrow - Move Right" << endl;

    for (int i = 0 ; i < 26 ; i++){
        cout << " ";
    }
    cout << "Down Arrow - Soft Drop" << endl;

    for (int i = 0 ; i < 35 ; i++){
        cout << " ";
    }
    cout << "Z - Rotate Left" << endl;

    for (int i = 0 ; i < 35 ; i++){
        cout << " ";
    }
    cout << "X - Rotate Right" << endl;

    for (int i = 0 ; i < 33 ; i++){
        cout << " ";
    }
    cout << "Esc - Pause" << endl << endl;

    cout << "          Back to menu";
}

//use for print the leaderboard whenever player want to see the chart
void printBoard(int num){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i =0 ; i<40; i++){
        gotoxy(i,0);
        SetConsoleTextAttribute(console ,3);
        cout <<"\u2509";
    }
    for (int i=0 ; i<40 ; i++){
        gotoxy(i,3);
        SetConsoleTextAttribute(console ,3);
        cout <<"\u2509";
    }
    for (int i = 0; i < num; i++){
    gotoxy(0,i+4);
    SetConsoleTextAttribute(console ,8);
    cout <<i+1;    
        for (int k =4 ; k<num+4;k++){
            gotoxy(28,k);
            SetConsoleTextAttribute(console ,3);
            cout <<"\u254E";
            gotoxy(17,k);
            SetConsoleTextAttribute(console ,3);
            cout <<"\u254E";
        }

        gotoxy(5,1);
        cout <<"Name";
        gotoxy(20,1);
        cout <<"Score";
        gotoxy(32,1);
        cout <<"Time";
        gotoxy(3,i+4);

        SetConsoleTextAttribute(console ,1); 
        cout.width(20);
        cout << left << board[i].name;
                        
        SetConsoleTextAttribute(console ,13);
        cout.width(10); 
        cout << left << board[i].score;
         
        SetConsoleTextAttribute(console ,15);
        int time = board[i].time;
        
        SetConsoleTextAttribute(console ,0); 
        cout << left << time/60 << ":" << (time % 60);
        SetConsoleTextAttribute(console ,15);
    }
}

//sortArray and sortData functions use for sort all the datas about the player
void sortArray(int num){
    for (int i = 0; i < num; i++){                          //sortArray function compare the scores of players at first and if there is the equl scores it compare the times
        if (board[num - 1].score > board[i].score){ 
            for (int j = num - 1; j >= i; j--){
                board[j+1].name = board[j].name;
                board[j+1].score = board[j].score;
                board[j+1].time = board[j].time;
            }
            board[i].name = board[num].name;
            board[i].score = board[num].score;
            board[i].time = board[num].time;
        }
        if (board[num - 1].score == board[i].score){
            if (board[num - 1].time < board[i].time){
                for (int j = num - 1; j >= i; j--){
                    board[j+1].name = board[j].name;
                    board[j+1].score = board[j].score;
                    board[j+1].time = board[j].time;
                }
                board[i].name = board[num].name;
                board[i].score = board[num].score;
                board[i].time = board[num].time;
            }
        }
    }
}

void sortData(){
    int numofGame = 0; //counting the  number that someone playing the game and it help to sort datas
    string read, name; //name, read, time and score use for read names from files and save them in the struct we made
    int time;
    int score;

    //read file and move datas to struct for sorting and show them to the player
    ifstream readScoreBoard("filetetris.txt");

    while(readScoreBoard >> read) {
        if (read == ":") {
           readScoreBoard >> score >> time;
            board[numofGame].time = time;
            board[numofGame].score = score;
            board[numofGame].name = name;
            numofGame++;
            name = "";
            }
        else {
            name += read;
            name += ' ';
        }
    }
    readScoreBoard.close();

    sortArray(numofGame);
    printBoard(numofGame);
}

//make the game matris according to the row and column entered by the player
void getSpace(){
    //get space for the game chart
    game = new int*[row+1];
    for (int i = 0; i < row+1; i++){
        game[i] = new int[column+2];
    }
}

int main(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\033[0;33m" << "Press Space to Play the Game " << "\033[0m";
    cout << "=))";
    string line;

    while(true){

        if (pauseformenu){  //check if the player choose to go back to the menu after pause the play
            system("cls");
            menu();
            pause = false;
            pauseformenu = false;
        }

        if (pauseforexit){ //check if the player choose to close the play when he pause the play
            return 0;
        }

        char input = getch();
        if (input == 32){
            system("cls");
            menu();
        }

        if (input == '4'){
            system("cls");
            cout << "Are you sure you want to quit ?\n1.yes\n2.No";
            char sure = getch();
            if (sure == '1'){
                system("cls");
                cout << "\033[0;34m" << "Thanks for Playing our Game >_<  " << "\033[0m";
                return 0;
            }
            system("cls");
            menu();
        }

        if (input == '3'){
            system("cls");
            help();
            char back = getch();
            system("cls");
            menu();
        }

        if (input == '1'){
            system("cls");
            
            gotoxy(0,0);
            SetConsoleTextAttribute(console ,8);
            cout <<"\u256D";
            
            for (int i=0 ;i<17;i++){
                
                cout<<"\u254C";
            }
            
            cout<<"\u256E";
            gotoxy(0,1);
            
            cout <<"\u250A";
            
            gotoxy(0,2);
            cout <<"\u2570";

            for (int i=0 ; i<18 ; i++){
                cout <<"\u254C";
                gotoxy(1+i,2);
            }
            
            
            cout <<"\u256F";
            
            gotoxy(2,1);
            SetConsoleTextAttribute(console ,11);
            cout << "Enter your name "; //get the name of the player
            
            SetConsoleTextAttribute(console ,8);
            cout <<"\u250A";
            
            gotoxy(3,3);
            SetConsoleTextAttribute(console ,1);
            cin >> name;
            system("cls");
            //////////////////////////////////////
            gotoxy(0,0);
            SetConsoleTextAttribute(console ,8);
            cout <<"\u256D";
            for (int i=0 ;i<30;i++){
                SetConsoleTextAttribute(console ,8);
                cout<<"\u254C";
            }
            cout <<"\u256E";

            gotoxy(0,1);
            cout <<"\u250A";

            gotoxy(0,2);
            cout <<"\u255E";
            for (int i =0 ; i<30; i++){
                cout <<"\u2505";
            }
            cout <<"\u2561";
            
            for (int i=0 ; i<3 ; i++){
                gotoxy(0,3+i);
                cout<<"\u250A";
            }

            gotoxy(0,5);
            cout <<"\u2570";
            for (int i=0 ; i<30 ; i++){
                cout<<"\u254C";
            }
            cout <<"\u256F";

            for (int i=0 ; i<2 ; i++){
                gotoxy(31,3+i);
                cout <<"\u250A";
            }

            gotoxy(1,3);
            SetConsoleTextAttribute(console ,2);
            cout <<"   1.EASY";
            
            gotoxy(1,4);
            SetConsoleTextAttribute(console ,12);
            cout <<"   2.HARD";
            
            gotoxy(1,1);
            SetConsoleTextAttribute(console ,11);
            cout << " Choose the Level of the game ";                  //get the level of the game that player want to play
            SetConsoleTextAttribute(console ,8);
            cout <<"\u250A";
            
            char level = getch();                                     //according to the level choose by the player the hardshipLevel get diffrent values 
            if (level == '1'){                                        //and it help us in play and printChart functions to make diffrent types of game for the play
                hardshipLevel = 500;
                showlevel = "EASY"; 
            }
            if (level == '2'){
                hardshipLevel = 200;
                showlevel = "HARD"; 
            }
            system("cls");
            cout << "Enter the size of the rows and columns: "; //get the number of the row and column for the game
            cin >> row >> column;
            getSpace();
            play();

            ofstream saveScoreBoard("filetetris.txt", ios::app); //save players datas in file
            if (saveScoreBoard.is_open()){
                saveScoreBoard << name << " : " << scr << " " << gameTime << '\n';
            }
            saveScoreBoard.close();
        }

        if (input == '2'){
            system("cls");
            sortData();         //sort and show datas to players

        }

    }
}