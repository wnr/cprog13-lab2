#include "calendar.h"

using namespace lab2;

std::ostream & operator<< (std::ostream & os, const Calendar<Gregorian> & cal) {
  for(auto it = cal.events.begin(); it != cal.events.end(); it++) {
    if((*it).date > cal.currentDate) {
      os << (*it).date << " : " << (*it).text << std::endl;
    }
  }

  return os;
}