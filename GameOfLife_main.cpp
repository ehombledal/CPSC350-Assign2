
#include "Board.h"

//map Variables
int mapChoice = 0;  //1 = RNG map, 2 = Mapfile

//Boundary Variable
int boundaryStyle = 0;  //1 = Classic, 2 = Doughnut, 3 = Mirror

//Output Variable
int outputChoice = 0; //1 = Continous, 2 = User Input, 3 = File


void introInput()
{
  cout << "Welcome to the Game of Life!" << endl;
  cout << endl;

  //MAP GENERATION QUESTIONS
  cout << "Map Generation Options" << endl;
  cout << "1. Randomly Generated Map" << endl;
  cout << "2. Map From File" << endl;
  cin >> mapChoice;

  cout << mapChoice;
  while (mapChoice != 1 && mapChoice != 2)
  {
    //cout << "Invalid option entered. Please enter a valid value." << endl;
    cin >> mapChoice;
  }
  cout << endl;

  //BOUNDARY MODE QUESTIONS
  cout << "What boundary mode would you like?" << endl;
  cout << "1. Classic" << endl;
  cout << "2. Doughnut" << endl;
  cout << "3. Mirror" << endl;
  cin >> boundaryStyle;
  while (boundaryStyle != 1 && boundaryStyle != 2 && boundaryStyle != 3)
  {
    //cout << "Invalid option entered. Please enter a valid value." << endl;
    cin >> boundaryStyle;
  }
  cout << endl;

  //OUTPUT OPTIONS
  cout << "How would you like the game to be displayed?" << endl;
  cout << "1. Continous with Delay" << endl;
  cout << "2. User Input to Progress" << endl;
  cout << "3. Output results to file" << endl;
  cin >> outputChoice;
  while (outputChoice != 1 && outputChoice != 2 && outputChoice != 3)
  {
    //cout << "Invalid option entered. Please enter a valid value." << endl;
    cin >> outputChoice;
  }
  cout << endl;
}

int main(int argc, char **argv)
{
  //gets input
  introInput();
  Board *b = new Board(mapChoice, boundaryStyle, outputChoice);
  b->setup();
  b->print();
  b->play();
  b->print();
  b->play();
  b->print();

  cout << b->isEmpty() << endl; 
}
