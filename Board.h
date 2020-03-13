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
    void printToFile(string fileName);
    bool isEmpty();
    bool checkStable();

  private:
    int m_mapChoice;
    int m_boundaryStyle;
    int m_outputChoice;
    string m_fileName;

    bool m_isStable = false;
    int m_row;
    int m_col;
    float m_popDensity;

    Cell **cellArray = nullptr;

    //add stuff for this, move reference back and forth
    Cell **shadowArray = nullptr;

    Cell **currentArray = nullptr;

    bool isStable(Cell** array, Cell** toCheck);
    void fillArray(Cell** array, float pop);
    void copyArray(Cell** original, Cell** copy);

    int checkUp(int i, int j);
    int checkDown(int i, int j);
    int checkRight(int i, int j);
    int checkLeft(int i, int j);
    int checkTopRight(int i, int j);
    int checkTopLeft(int i, int j);
    int checkBotRight(int i, int j);
    int checkBotLeft(int i, int j);
};
