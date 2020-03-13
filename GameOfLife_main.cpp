
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

  if (outputChoice == 1)
  {
    while (!b -> isEmpty())
    {
      if (b->checkStable() == true)
      {
        cout << "Program is stable. Press any key to exit simulation." << endl;
        getchar();
        break;
      }
      //http://www.martinbroadhurst.com/sleep-for-milliseconds-in-c.html
      this_thread::sleep_for(chrono::milliseconds(500));
      b->print();
      b->play();
    }
    cout << "Thank you for playing!" << endl;
  }

  if (outputChoice == 2)
  {
    while (!b -> isEmpty())
    {
      if (b->checkStable() == true)
      {
        cout << "program is stable. Press any key to exit simulation." << endl;
        getchar();
        break;
      }
      b->print();
      cout << "press any key to continue." << endl;
      getchar();
      b->play();
    }

    cout << "Thank you for playing!" << endl;
  }

  if (outputChoice == 3)
  {
    ofstream outFS;
    string fileName;
    cout << "What is the name of the file you want results outputted to?" << endl;
    cin >> fileName;

    //creates file for the first time
    outFS.open(fileName);
    outFS << "GAME OF LIFE" << endl;
    outFS.close();

    while(!b -> isEmpty())
    {
      if (b->checkStable() == true)
      {
        cout << "program is stable. Press any key to exit simulation." << endl;
        getchar();
        break;
      }
      b->printToFile(fileName);
      b->play();
    }


    cout << "Thank you for playing!" << endl;

  }
}
