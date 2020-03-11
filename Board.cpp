#include "Board.h"


Board::Board() //this shouldnt be used
{
  m_mapChoice = 1;
  m_boundaryStyle = 1;
  m_outputChoice = 1;
}

Board::Board(int mapChoice, int boundaryStyle, int outputChoice)
{
  m_mapChoice = mapChoice;
  m_boundaryStyle = boundaryStyle;
  m_outputChoice = outputChoice;
}

void Board::copyArray(Cell** original, Cell** copy)
{
  for (int i = 0; i < m_row; ++i)
  {
    for (int j = 0; j < m_col; ++j)
    {
      if (original[i][j].isAlive())
      {
        copy[i][j].setAlive();
      }
      if (!original[i][j].isAlive())
      {
        copy[i][j].setDead();
      }
    }
  }
}


void Board::fillArray(Cell** array, float pop)
{
  float total = m_row * m_col;
  float aliveGoal = total * pop;
  int liveCount = 0;
  cout << total << " " << aliveGoal << endl;

  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> xDist(0, m_row - 1);
  uniform_int_distribution<int> yDist(0, m_col - 1);

  //doesnt work at extremely high values, for some reason.
  int i = 0;
  while (liveCount <= aliveGoal || i >= 500)
  {
    int xRand = xDist(mt);
    int yRand = yDist(mt);

    //cout << "x: " << xRand << " y: " << yRand << endl;
    if (array[xRand][yRand].isAlive() == false)
    {
      array[xRand][yRand].changeState();
      liveCount++;
    }
    i++;
  }
  cout << i << endl;

}


//CHANGE CHECK STATEMENT TO WORK OFF CURRENT ARRAY
int Board::checkUp(int i, int j)
{
  if (cellArray[i-1][j].isAlive() == true)
  {
    return 1;
  } else {
    return 0;
  }
}

int Board::checkDown(int i, int j)
{
  if (cellArray[i+1][j].isAlive() == true)
  {
    return 1;
  } else {
    return 0;
  }
}

int Board::checkRight(int i, int j)
{
  if (cellArray[i][j+1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkLeft(int i, int j)
{
  if (cellArray[i][j-1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkTopRight(int i, int j)
{
  if (cellArray[i-1][j+1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkTopLeft(int i, int j)
{
  if (cellArray[i-1][j-1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkBotRight(int i, int j)
{
  if (cellArray[i+1][j+1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkBotLeft(int i, int j)
{
  if (cellArray[i+1][j-1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkDonutUp(int i, int j)
{
  if (cellArray[m_row-1][j].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkDonutDown(int i, int j)
{
  if (cellArray[0][j].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkDonutRight(int i, int j)
{
  if (cellArray[i][0].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}

int Board::checkDonutLeft(int i, int j)
{
  if (cellArray[i][m_col-1].isAlive() == true)
  {
    return 1;
  } else  {
    return 0;
  }
}



void Board::setup()
{
  if (m_mapChoice == 1)
  {
    //RNG MAP
    cout << "How many rows?" << endl;
    cin >> m_row;
    cout << "How many columns?" << endl;
    cin >> m_col;
    cout << "What do you want the density of spawns to be? (0 - 1)" << endl;
    cin >> m_popDensity;
    //set pop density to .999 if at 1
    //TODO: Add catches

    //make the array
    //cellArray = new Cell[m_row][m_col];

    //https://stackoverflow.com/questions/44998478/c-array-size-in-new-expression-must-be-constant
    cellArray = new Cell *[m_row];
    shadowArray = new Cell *[m_row];
    for (int i = 0; i < m_row; ++i)
    {
      cellArray[i] = new Cell[m_col];
      shadowArray[i] = new Cell[m_col];
    }
    fillArray(cellArray, m_popDensity);
    copyArray(cellArray, shadowArray);


  }
  {
    //MAP FROM FILE
  }
}

void Board::play() //oh god
{
  for (int i = 0; i < m_row; ++i) //row
  {
    for (int j = 0; j < m_col; ++j) //column
    {
      int NeighborCount = 0; //COUNT OF NEIGHBORS

      if (i == 0 || i == m_row - 1) //row edge cases
      {
        if (i == 0) //top
        {
          if (j == 0) //top left
          {
            NeighborCount = checkDown(i,j) + checkRight(i,j) + checkBotRight(i,j);
            cout << NeighborCount;
            cout << " checking top left";
            if (m_boundaryStyle == 2) // donut
            {

            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
              cout << NeighborCount;
              cout << " checking top left. M";
            }
          } else if (j == m_col - 1) //top right
          {
              NeighborCount = checkDown(i,j) + checkLeft(i,j) + checkBotLeft(i,j);
              cout << NeighborCount;
              cout << " checking top right";
              if (m_boundaryStyle == 2) // donut
              {
                //add additional values
              }
              if (m_boundaryStyle == 3) //mirror
              {
                if (cellArray[i][j].isAlive())
                {
                  NeighborCount+= 3;
                }
                cout << NeighborCount;
                cout << "checking top left. M";
              }

          } else  //regular top row
          {
            NeighborCount = checkDown(i,j) + checkLeft(i,j) + checkRight(i,j) + checkBotLeft(i,j) + checkBotRight(i,j);
              cout << NeighborCount;
            cout << " checking top row";
            if (m_boundaryStyle == 2) // donut
            {
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
            cout << NeighborCount;
            cout << " checking top row. M";

            }

          }

        } else if (i == m_row - 1) //bottom
        {
          if (j == 0) //bot left
          {
            NeighborCount = checkUp(i,j) + checkRight(i,j) + checkTopRight(i,j);
              cout << NeighborCount;
            cout << " checking bot left";
            if (m_boundaryStyle == 2) // donut
            {
              //add additional values
            }
            if (m_boundaryStyle == 3) //mirror
            {

              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
              cout << NeighborCount;
            cout << " checking bot left";

            }


          } else if (j == m_col - 1) //bot right
          {
            NeighborCount = checkUp(i,j) + checkLeft(i,j) + checkTopLeft(i,j);
              cout << NeighborCount;
            cout << " checking bot right";
            if (m_boundaryStyle == 2) // donut
            {
              //add additional values
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
              cout << NeighborCount;
            cout << " checking bot right";

            }

          } else  //regular bot row
          {
            NeighborCount = checkUp(i,j) + checkLeft(i,j) + checkRight(i,j) + checkTopLeft(i,j) + checkTopRight(i,j);
              cout << NeighborCount;
            cout << " checking bot row";
            if (m_boundaryStyle == 2) // donut
            {

            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
               cout << NeighborCount;
            cout << " checking bot row";

            }

          }
        }


      } else if (j == 0 || j == m_col - 1) //column edge cases
      {
        if (j == 0) //left column
        {
          if (i == 0) //top left, already handled
          {
            //SKIPPING
          } else if(i == m_row-1)
          {  //top left, already handled
            //SKIPPING
          } else
          { // DEFAULT CASE FOR left COLUMN
            NeighborCount = checkDown(i,j) + checkUp(i,j) + checkRight(i,j) + checkBotRight(i,j) + checkTopRight(i,j);
              cout << NeighborCount;
            cout << " checking left col";
            if (m_boundaryStyle == 2) // donut
            {
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
              cout << NeighborCount;
            cout << " checking left col";

            }
          }

        } else if(j == m_col-1) //right column
        {
          if (i == 0) //bot right, already handled
          {
            //SKIPPING
          } else if(i == m_row-1)
          {  //bot right, already handled
            //SKIPPING
          } else
          { // DEFAULT CASE FOR RIGHT COLUMN
            NeighborCount = checkDown(i,j) + checkUp(i,j) + checkLeft(i,j) + checkBotLeft(i,j) + checkTopLeft(i,j);
              cout << NeighborCount;
            cout << " checking right col";
            if (m_boundaryStyle == 2) // donut
            {
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
              cout << NeighborCount;
            cout << " checking right col";

            }
          }
        }

      } else
      { //regular case, no collumn or row on edge
        NeighborCount = checkDown(i,j) + checkUp(i,j) + checkLeft(i,j) + checkRight(i,j) + checkTopLeft(i,j) + checkTopRight(i, j) + checkBotLeft(i,j) + checkBotRight(i,j);
        cout << NeighborCount;
        cout << " checking regular case.";
      }

      //cout << NeighborCount;
      //DO THE MATH WITH THE POINTER SWITCHING
      //What to do with different neighbor numbers
      if (NeighborCount <= 1)
      {
        shadowArray[i][j].setDead();
        cout << ". setting dead. Neighbor <= 1." << endl;
      } else if (NeighborCount == 2)
      {
        //do nothing
        cout << ". do nothing. Neighbor = 2." << endl;
      } else if (NeighborCount == 3)
      {
          shadowArray[i][j].changeState();
          cout << ". changing state. Neighbor = 3." << endl;
      } else
      { //if 4 neighbors or more
          shadowArray[i][j].setDead();
          cout << ". Setting dead. Neighbor >= 4." << endl;
      }


    //copies results back over to original array.
    }
    cout << endl;
  }
  copyArray(shadowArray, cellArray);
}

void Board::print()
{
  for (int i = 0; i < m_row; ++i)
  {
    for (int j = 0; j < m_col; ++j)
    {
      cout << cellArray[i][j].print();
    }
    cout << endl;
  }
  cout << endl;
}

bool Board::isEmpty()
{
  for (int i = 0; i < m_row; ++i)
  {
    for (int j = 0; j < m_col; ++j)
    {
      if (cellArray[i][j].isAlive())
      {
        return false;
      }
    }
  }
  return true; 
}
