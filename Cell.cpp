#include "Cell.h"

Cell::Cell()
{
  m_isAlive = false;
}

Cell::~Cell()
{

}

void Cell::changeState() //swaps between alive and dead.
{
  if (m_isAlive == false)
  {
    m_isAlive = true;
  } else {
    m_isAlive = false;
  }
}

void Cell::setDead()
{
  m_isAlive = false;
}

void Cell::setAlive()
{
  m_isAlive = true; 
}


bool Cell::isAlive()
{
  return m_isAlive;
}

char Cell::print()
{
  if (m_isAlive == true)
  {
    return 'X';
  } else {
    return '-';
  }
}
