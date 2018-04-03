#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include<time.h>
using namespace std;
//Global Variables.
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
char data[100];
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
//Setup Class to start the setup
class gameSetup{
        public:
    // Constructor
        gameSetup(){
            cout<<"Hello to snake game. The controls are :"<<endl<<"W for Up"<<endl<<"S for Down"<<endl<<"A for Left"<<endl<<"D for Right"<<endl<<"E for Exit"<<endl<<"Enjoy the Game"<<endl;
            cout<<"Enter your Name"<<endl;
            cin.getline(data, 100);

        }

        void Setup()
        {
            gameOver = false;
            dir = STOP;
            x = width / 2;
            y = height / 2;
            fruitX = rand() % width;
            fruitY = rand() % height;
            score = 0;
        }
};
class Render{
        public:
            void Draw()
            {
                system("cls");
                //Prining Arean
                //Top Wall
                for (int i = 0; i < width+2; i++)
                    cout << "#";
                cout << endl;
                //side walls
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        if (j == 0)
                            cout << "#";
                        if (i == y && j == x)
                            cout << "O";
                        else if (i == fruitY && j == fruitX)
                            cout << "F";
                        else
                        {
                            bool print = false;
                            for (int k = 0; k < nTail; k++)
                            {
                                if (tailX[k] == j && tailY[k] == i)
                                {
                                    cout << "o";
                                    print = true;
                                }
                            }
                            if (!print)
                                cout << " ";
                        }


                        if (j == width - 1)
                            cout << "#";
                    }
                    cout << endl;
                }
                //bottom wall
                for (int i = 0; i < width+2; i++)
                    cout << "#";
                cout << endl;
                cout<<"Name:"<<data<<endl;
                cout << "Score:" << score << endl;
            }
};
class movementLogic:public Render//Inherit Render class in public Mode
{
        public:
            void Input()
            {
                if (_kbhit())//check if keyboard any key is pressed
                {
                    switch (_getch())//get a character
                    {
                    case 'a':
                        dir = LEFT;
                        break;
                    case 'd':
                        dir = RIGHT;
                        break;
                    case 'w':
                        dir = UP;
                        break;
                    case 's':
                        dir = DOWN;
                        break;
                    case 'e':
                        gameOver = true;
                        break;
                    }
                }
            }
            void Logic()
            {
                int prevX = tailX[0];
                int prevY = tailY[0];
                int prev2X, prev2Y;
                tailX[0] = x;
                tailY[0] = y;
                for (int i = 1; i < nTail; i++)
                {
                    prev2X = tailX[i];
                    prev2Y = tailY[i];
                    tailX[i] = prevX;
                    tailY[i] = prevY;
                    prevX = prev2X;
                    prevY = prev2Y;
                }
                switch (dir)
                {
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UP:
                    y--;
                    break;
                case DOWN:
                    y++;
                    break;
                default:
                    break;
                }
                //Playing with solid walls
                //if (x > width || x < 0 || y > height || y < 0)
                //	gameOver = true;
                //playing with liquid walls
                if (x >= width) x = 0; else if (x < 0) x = width - 1;
                if (y >= height) y = 0; else if (y < 0) y = height - 1;

                for (int i = 0; i < nTail; i++)
                    if (tailX[i] == x && tailY[i] == y)
                        gameOver = true;

                if (x == fruitX && y == fruitY)
                {
                    score += 10;
                    fruitX = rand() % width;
                    fruitY = rand() % height;
                    nTail++;
                }
            }

};
int main()
{
	gameSetup s;
	movementLogic mL;
	s.Setup();
	char c;
	cout<<"Enter 'C' to continue"<<endl;
	cin>>c;
	if(c){
	while (!gameOver)
	{
		mL.Draw();
		mL.Input();
		mL.Logic();
		Sleep(100); //sleep for 100 millisec;
	}
	}
	//Storing the Score and name in File.
	ofstream outfile;
                outfile.open("scoreFile.txt",ios::app);//opening file in append mode
                outfile <<data<<"\t"<<score<<endl;
                outfile.close();
	return 0;
}
