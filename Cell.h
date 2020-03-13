#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;


class Cell
{
  public:
     Cell(); //default
    ~Cell(); //destructor

     //functions
     bool isAlive();
     void changeState(); //swaps between alive and dead
     void setAlive();
     void setDead();
     char print(); //character to return to print


  private:
    bool m_isAlive;
};
