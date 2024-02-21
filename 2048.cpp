#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>

using namespace std;

int score = 0;
int coplayer = 0;
int arr[4][4];
bool lose;

void swap(int &a,int &b){
    int c = 0;
    c = a;
    a = b;
    b = c;
}

int ehtemal(){

    srand (time(nullptr));
    int eht = rand()%4;
    int ehte[4] = {2,2,2,4};
    return ehte[eht];  
}

struct {
    string name;
    int score;
}player[100];

void Leaderboard(){
        
    for(int i=0; i <= coplayer; i++){
        for(int j=i+1; j <= coplayer; j++){ 
            if(player[i].score > player[j].score){
                int temp = player[i].score;
                string temp1 = player[i].name;
                player[i].score = player[j].score;
                player[i].name = player[j].name;
                player[j].score = temp;
                player[j].name = temp1; 
            }
        }
    }

    for (int i=coplayer ; i > 0 ; i--){
        cout << "Name: "<< player[i].name;
        for (int i = 0 ; i < 40 ; i++){
            cout << " ";
        }
        cout << "Score:"<< player[i].score;
        cout << endl;
    }
}



void shift_R(int arr[4][4], bool &lose){
    
    srand (time(nullptr));
	bool flag = false;
    lose = false;
    
    for (int i = 0 ; i < 4   ; i++){                  //AZ RAST HESAB BESHE
        for (int j = 3 ; j >= 0 ; j--){
            if (arr[i][j]!=0){
                for ( int k =3 ; k>j  ; k--){
                    if (arr[i][k]==0){
                        arr[i][k]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            } 
        }
    }

    for (int i = 0 ; i < 4   ; i++){              
        for (int j = 3 ; j > 0 ; j--){
            if (arr[i][j]==arr[i][j-1]){
                arr[i][j-1]*=2;
                arr[i][j]=0;
                score+=arr[i][j-1];
                lose = true;
            }
        }
    }
    for (int i = 0 ; i < 4   ; i++){                  
        for (int j = 3 ; j >= 0 ; j--){
            if (arr[i][j]!=0){
                for ( int k =3 ; k > j  ; k--){
                    if (arr[i][k]==0){
                        arr[i][k]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            } 
        }
    }

    if  (flag){
        bool flag2 = false;
        while(!flag2){
			int r=rand()%4;
        	int r1=rand()%4;
        	if (arr[r][r1]==0){
            	arr[r][r1]=ehtemal();
            	flag2 = true;
        	}
        }   
    }
}


void shift_L(int arr[4][4], bool &lose){

    srand(time(nullptr));
    bool flag = false;
    lose = false;
    
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (arr[i][j]!=0){
                for (int k = 0 ; k < j ; k++){
                    if (arr[i][k]==0){
                        arr[i][k]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }

    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (arr[i][j]==arr[i][j+1]){
                arr[i][j]*=2;
                arr[i][j+1]=0;
                score+=arr[i][j];
                lose = true;
            }
        }
    }
   
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (arr[i][j]!=0){
                for (int k = 0 ; k < j ; k++){
                    if (arr[i][k]==0){
                        arr[i][k]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }
    
    if (flag){
        bool flag2 = false;    
        while (!flag2){
            int r=rand()%4;
            int r1=rand()%4;
            if (arr[r][r1]==0){
                arr[r][r1]=ehtemal();
                flag2 = true;
            }   
        }
    }
}



void shift_D(int arr[4][4], bool &lose){
    
    srand(time(nullptr));
    bool flag =false;
    lose = false;

    for (int j = 0 ; j < 4 ; j++){
        for (int i = 3 ; i >= 0 ; i--){
            if (arr[i][j]!=0){
                for (int k = 3 ; k > i ; k--){
                    if (arr[k][j]==0){
                        arr[k][j]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }

    for (int j = 0 ; j < 4 ; j++){
        for (int i = 3 ; i >= 0 ; i--){
            if (arr[i][j]==arr[i-1][j]){
                arr[i][j]*=2;
                arr[i-1][j]=0;
                score+=arr[i][j];
                lose = true;
            }
        }
    }
    
    for (int j = 0 ; j < 4 ; j++){
        for (int i = 3 ; i >= 0 ; i--){
            if (arr[i][j]!= 0){
                for (int k = 3 ; k > i ; k--){
                    if (arr[k][j]== 0){
                        arr[k][j] = arr[i][j];
                        arr[i][j] = 0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }
    
    if (flag){
        bool flag2=false;
        while (!flag2){
            int r=rand()%4;
            int r1=rand()%4;
            if (arr[r][r1]==0){
                arr[r][r1]=ehtemal();
                flag2 = true;
            }   
        }
    }
}

void shift_U(int arr[4][4], bool &lose){

    srand(time(nullptr));
    bool flag = false;
    lose = false;

    for (int j = 0 ; j < 4 ; j++){
        for (int i = 0 ; i<=3 ; i++){
            if (arr[i][j]!=0){
                for (int k = 0 ; k < i ; k++){
                    if (arr[k][j]== 0){
                        arr[k][j] = arr[i][j];
                        arr[i][j] = 0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }

    for (int j = 0 ; j < 4 ; j++){
        for (int i = 0 ; i <=3 ; i++){
            if (arr[i][j]==arr[i+1][j]){
                arr[i][j]*=2;
                arr[i+1][j]=0;
                score+=arr[i][j];
                lose = true;
            }
        } 
    }

    for (int j = 0 ; j < 4 ; j++){
        for (int i = 0 ; i<=3 ; i++){
            if (arr[i][j]!=0){
                for (int k = 0 ; k < i ; k++){
                    if (arr[k][j]==0){
                        arr[k][j]=arr[i][j];
                        arr[i][j]=0;
                        flag = true;
                        lose = true;
                    }
                }
            }
        }
    }

    if (flag){
        bool flag2= false;
        while (!flag2){
            int r=rand()%4;
            int r1=rand()%4;
            if (arr[r][r1]==0){
                arr[r][r1]=ehtemal();
                flag2 = true;
            }      
        }
    }
}


void show(int arr[4][4]){
    system("cls");
    
    cout<<"\u2554";
    for (int i=0 ; i<16 ; i++){
        if (i==4 || i==8 || i==12){
            cout <<"\u2566";
        }
        cout <<"\u2550";
    }
    cout <<"\u2557";
    cout << endl;
    
    for (int i = 0 ; i < 4 ; i++){
        cout <<"\u2551";
        for (int j = 0 ; j < 4 ; j++ ){
            if (arr[i][j]>=0 && arr[i][j]<10){
                cout << " "<<"\033[0;36m"<< arr[i][j]<<"\033[0m"<<"  "<< "\u2551";
            }
            if (arr[i][j]>9 && arr[i][j]<100){
                cout << " "<< "\033[0;34m"<< arr[i][j]<< "\033[0m"<< " "<< "\u2551";
            }
            if (arr[i][j]>99 && arr[i][j]<1000){
                cout << " "<< "\033[0;35m"<< arr[i][j]<< "\033[0m"<< "\u2551";
            }
            if (arr[i][j]>999){
                cout <<"\033[0;31m"<< arr[i][j]<< "\033[0m";
            }

        }
            cout <<endl;
            if (i!=3){
                cout <<"\u2560";
                for (int i=0 ; i<17 ; i++){
                    if (i==4 || i==8 || i==12){
                        cout <<"\u256C";
                    }
                    if (i==16){
                        cout <<"\u2563";
                    }
                    else     
                        cout <<"\u2550";
                }
                cout << endl; 
            }
    }
    
    cout << "\u255A";
    for(int i = 0 ; i < 17 ; i++){
        if (i==4 || i==8 || i==12){
            cout << "\u2569";
        }
        if (i==16){
            cout <<"\u255D";
        }
        else 
            cout <<"\u2550";
    } 
    
    cout << endl << "score:" << score << endl;
    cout << "1.Back TO Menu"<< endl;
    cout << "2.Leaderboard"; 

}

void menu(){
    cout << "1.Start Game" <<endl;
    cout << "2.Leaderboard" <<endl;
    cout << "3.Exit" << endl;
}


int main(){
    
    srand(time(nullptr));
    menu();
    
    while(true){
        char game = getch();
        
        if (game=='1'){
            score=0;
            coplayer++;
            system("cls");
            cout << "Name:"<<" ";
            getline(cin,player[coplayer].name);

            for (int i=0;i<4;i++){
                for (int j=0 ;j<4;j++)
                arr[i][j]=0;
            }
    
            bool ply =false;
            while (!ply){

                int r=rand()%4;
                int r2=rand()%4;
                arr[r][r2]=2;
                arr[r2][r]=2;
                if (r!=r2){
                    ply=true;
                }
                else {
                    arr[r][r2]=0;
                    arr[r][r2]=0;
                }
            }

            show (arr);
            while (true){
                
                char input=getch();
                
                if (input=='1'){
                    system("cls");
                    player[coplayer].score=score;
                    menu();
                    break;
                }

                else if (input=='W'||input=='w'){
                    shift_U(arr,lose);
                    show(arr);
                }
                else if (input=='D'||input=='d'){
                    shift_R(arr,lose);
                    show(arr);
                }
                
                else if (input=='A'||input=='a'){
                    shift_L(arr,lose);
                    show(arr);
                }
                
                else if (input=='S'||input=='s'){
                    shift_D(arr,lose);
                    show(arr);
                }

                else if (input=='2'){
                    system("cls");
                    player[coplayer].score=score;
                    cout <<"1.Game Continue"<< endl<< endl;
                    Leaderboard();
                    char input2 = getch();
                    if (input2=='1'){
                        show(arr);
                        continue;
                    }
                }
                
                if (lose == false){
                    system("cls");
                    for (int i = 0 ; i<30 ; i++){
                        cout << " ";
                    }
                    cout << "Game Over! :(("<< endl;
                    cout << "1.Back To Menu"<<endl;
                    cout << "Your score:"<< score;
                    char input4 = getch() ;
                    if (input4=='1'){
                        menu();
                        break;
                    }
                } 
            }
        }
        else if (game=='2'){
            system("cls");
            cout << "1.Back TO Menu"<< endl<< "2.Exit"<< endl<< endl;
            player[coplayer].score=score;
            Leaderboard();
            char input3=getch();
            if (input3=='1'){
                system("cls");
                menu();
                continue;
            }
            else if (input3=='2'){
                return 0;
            }    
        }
        else if (game=='3'){
            return 0;
        }           
    }
}
