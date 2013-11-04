#ifndef JULIAN_H
#define JULIAN_H

#include "Date.h"

namespace lab2 {
  class Julian : Date {
  public:
    /* Default constructor. Inits to current date. */
    Julian();
    
    /* Initializing constructor. */
    Julian(int year, int month, int day);
    
  };
}

#endif
