#include <random>
#include "Cell.h"

class Board
{
  public:
    Board();
    Board(int mapChoice, int boundaryStyle, int outputChoice);
    ~Board();

    void setup();
    void play();
    void print();
    bool isEmpty();

  private:
    int m_mapChoice;
    int m_boundaryStyle;
    int m_outputChoice;

    int m_row;
    int m_col;
    float m_popDensity;

    Cell **cellArray = nullptr;

    //add stuff for this, move reference back and forth
    Cell **shadowArray = nullptr;

    Cell **currentArray = nullptr;


    void fillArray(Cell** array, float pop);
    void copyArray(Cell** original, Cell** copy);
    void playRegular();

    int checkUp(int i, int j);
    int checkDown(int i, int j);
    int checkRight(int i, int j);
    int checkLeft(int i, int j);
    int checkTopRight(int i, int j);
    int checkTopLeft(int i, int j);
    int checkBotRight(int i, int j);
    int checkBotLeft(int i, int j);

    //used for donut mode.
    int checkDonutUp(int i, int j); //goes to bot row in same column
    int checkDonutDown(int i, int j); //goes to top row in same column
    int checkDonutLeft(int i, int j); //goes to right col in same row
    int checkDonutRight(int i, int j); //goes to left col in same row

    int checkDonutUpRight(int i, int j); //goes up 1 row, then check left on other side.
    int checkDonutUpLeft(int i, int j); //goes up 1 row, then check right on other side.
    int checkDonutDownRight(int i, int j); //goes down 1 row, then check left on other side.
    int checkDonutDownLeft(int i, int j); //
};
