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

bool Board::checkStable()
{
  return m_isStable;
}

bool Board::isStable(Cell** array, Cell** toCheck)
{
  for (int i = 0; i < m_row; ++i)
  {
    for (int j = 0; j < m_col; ++j)
    {
      if (array[i][j].isAlive())
      {
        if (!toCheck[i][j].isAlive())
        {
          return false;
        }
      }
      if (!array[i][j].isAlive())
      {
        if (!toCheck[i][j].isAlive())
        {
          return false;
        }
      }
    }
  }
  return true;
}


void Board::fillArray(Cell** array, float pop)
{
  float total = m_row * m_col;
  float aliveGoal = total * pop;
  int liveCount = 0;

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


  } else
  {
    ifstream inFS;
    string line;
    string fileName;
    int lineCounter = 0;

    cout << "what is the name of the map file?" << endl;
    cin >> fileName;
    inFS.open(fileName);

    if (!inFS.is_open())
    {
      cout << "Could not open file." << endl;
      cout << "Aborting. Please input a proper file name and try again." << endl;
    }

    //gets the first 2 lines
    inFS >> line;
    m_row = stoi(line);
    inFS >> line;
    m_col = stoi(line);


    //makes the array
    cellArray = new Cell *[m_row];
    shadowArray = new Cell *[m_row];
    for (int i = 0; i < m_row; ++i)
    {
      cellArray[i] = new Cell[m_col];
      shadowArray[i] = new Cell[m_col];
    }
    while(!inFS.eof())
    {
      inFS >> line;
      if (!inFS.fail())
      {
        for (int i = 0; i < m_col; ++i)
        {

          if (line[i] == 'X')
          {
            cellArray[lineCounter][i].setAlive();
          }
        }
        lineCounter++;
      }
    }




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
            if (m_boundaryStyle == 2) // donut
            {
              //check up left (aka bot right)
              if (cellArray[m_row-1][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check up right
              if (cellArray[m_row-1][j+1].isAlive())
              {
                NeighborCount++;
              }
              //check left (loops around to right side)
              if(cellArray[i][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check down left
              if (cellArray[i+1][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check up
              if(cellArray[m_row-1][j].isAlive())
              {
                NeighborCount++;
              }
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
            }
          } else if (j == m_col - 1) //top right
          {
              NeighborCount = checkDown(i,j) + checkLeft(i,j) + checkBotLeft(i,j);
              if (m_boundaryStyle == 2) // donut
              {
                //check up left
                if (cellArray[m_row-1][j-1].isAlive())
                {
                  NeighborCount++;
                }

                //check up
                if(cellArray[m_row-1][j].isAlive())
                {
                  NeighborCount++;
                }

                //check up right (aka bot left corner)
                if (cellArray[m_row-1][0].isAlive())
                {
                  NeighborCount++;
                }

                //check right
                if (cellArray[i][0].isAlive())
                {
                  NeighborCount++;
                }

                //check down right
                if (cellArray[i+1][0].isAlive())
                {
                  NeighborCount++;
                }

              }
              if (m_boundaryStyle == 3) //mirror
              {
                if (cellArray[i][j].isAlive())
                {
                  NeighborCount+= 3;
                }
              }

          } else  //regular top row
          {
            NeighborCount = checkDown(i,j) + checkLeft(i,j) + checkRight(i,j) + checkBotLeft(i,j) + checkBotRight(i,j);
            if (m_boundaryStyle == 2) // donut
            {
              //check up right
              if (cellArray[m_row-1][j+1].isAlive())
              {
                NeighborCount++;
              }

              //check up
              if (cellArray[m_row-1][j].isAlive())
              {
                NeighborCount++;
              }

              //check up left
              if (cellArray[m_row-1][j-1].isAlive())
              {
                NeighborCount++;
              }
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
            }
          }

        } else if (i == m_row - 1) //bottom
        {
          if (j == 0) //bot left
          {
            NeighborCount = checkUp(i,j) + checkRight(i,j) + checkTopRight(i,j);
            if (m_boundaryStyle == 2) // donut
            {
              //check up left
              if (cellArray[i-1][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check left
              if (cellArray[i][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check down left (aka top right)
              if (cellArray[0][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check down
              if (cellArray[0][j].isAlive())
              {
                NeighborCount++;
              }
              //check down right
              if (cellArray[0][j+1].isAlive())
              {
                NeighborCount++;
              }
            }
            if (m_boundaryStyle == 3) //mirror
            {

              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
            }


          } else if (j == m_col - 1) //bot right
          {
            NeighborCount = checkUp(i,j) + checkLeft(i,j) + checkTopLeft(i,j);
            if (m_boundaryStyle == 2) // donut
            {
              //check up right
              if (cellArray[i-1][0].isAlive())
              {
                NeighborCount++;
              }
              //check right
              if (cellArray[i][0].isAlive())
              {
                NeighborCount++;
              }
              //check down right (aka top left)
              if (cellArray[0][0].isAlive())
              {
                NeighborCount++;
              }
              //check down
              if (cellArray[0][j].isAlive())
              {
                NeighborCount++;
              }
              //check down left
              if (cellArray[0][j-1].isAlive())
              {
                NeighborCount++;
              }
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 3;
              }
            }

          } else  //regular bot row
          {
            NeighborCount = checkUp(i,j) + checkLeft(i,j) + checkRight(i,j) + checkTopLeft(i,j) + checkTopRight(i,j);
            if (m_boundaryStyle == 2) // donut
            {
              //check down left
              if (cellArray[0][j-1].isAlive())
              {
                NeighborCount++;
              }
              //check down
              if (cellArray[0][j].isAlive())
              {
                NeighborCount++;
              }
              //check down right
              if (cellArray[0][j+1].isAlive())
              {
                NeighborCount++;
              }

            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
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
            if (m_boundaryStyle == 2) // donut
            {
              //check up left
              if (cellArray[i-1][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check left
              if (cellArray[i][m_col-1].isAlive())
              {
                NeighborCount++;
              }
              //check down left
              if (cellArray[i+1][m_col-1].isAlive())
              {
                NeighborCount++;
              }

            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
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
            if (m_boundaryStyle == 2) // donut
            {
              //check up right
              if (cellArray[i-1][0].isAlive())
              {
                NeighborCount++;
              }
              //check right
              if (cellArray[i][0].isAlive())
              {
                NeighborCount++;
              }
              //check down right
              if (cellArray[i+1][0].isAlive())
              {
                NeighborCount++;
              }
            }
            if (m_boundaryStyle == 3) //mirror
            {
              if (cellArray[i][j].isAlive())
              {
                NeighborCount+= 1;
              }
            }
          }
        }

      } else
      { //regular case, no collumn or row on edge
        NeighborCount = checkDown(i,j) + checkUp(i,j) + checkLeft(i,j) + checkRight(i,j) + checkTopLeft(i,j) + checkTopRight(i, j) + checkBotLeft(i,j) + checkBotRight(i,j);
      }

      //cout << NeighborCount;
      //DO THE MATH WITH THE POINTER SWITCHING
      //What to do with different neighbor numbers
      if (NeighborCount <= 1)
      {
        shadowArray[i][j].setDead();
        //cout << ". setting dead. Neighbor <= 1." << endl;
      } else if (NeighborCount == 2)
      {
        //do nothing
        //cout << ". do nothing. Neighbor = 2." << endl;
      } else if (NeighborCount == 3)
      {
          shadowArray[i][j].changeState();
          //cout << ". changing state. Neighbor = 3." << endl;
      } else
      { //if 4 neighbors or more
          shadowArray[i][j].setDead();
          //cout << ". Setting dead. Neighbor >= 4." << endl;
      }


    //copies results back over to original array.
    }
    cout << endl;
  }
  m_isStable = isStable(shadowArray, cellArray);
  if (m_isStable == true)
  {
    cout << "Program stabilizing..." << endl;
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


void Board::printToFile(string fileName)
{
  ofstream outFS;
  outFS.open(fileName,ios::app);
  for (int i = 0; i < m_row; ++i)
  {
    for (int j = 0; j < m_col; ++j)
    {
      outFS << cellArray[i][j].print();
    }
    outFS << endl;
  }
  outFS << endl;
  outFS.close();
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
