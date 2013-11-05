#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include "julian.h"
#include "gregorian.h"

#include <list>
#include <iterator>
#include <iostream>
#include <algorithm>

namespace lab2 {
  template<typename T>
  struct Event {
    std::string text;
    T date;

    friend struct Event<Julian>;
    friend struct Event<Gregorian>;

    Event(const std::string & t, const T & d) : text(t), date(d) {}

    template<class A>
    Event(const Event<A> & e) : text(e.text), date(e.date) {}

    bool operator< (const Event & e) const {
      return (date < e.date);
    }

    bool operator== (const Event & e) const {
      return date == e.date && text == e.text;
    }

    bool operator> (const Event & e) const {
      return !(*this < e && *this == e);
    }
  };

  template<typename T>
  class Calendar {
    std::list<Event<T> > events;

    T currentDate;

  public:
    friend class Calendar<Julian>;
    friend class Calendar<Gregorian>;
    template<class A>
    friend std::ostream & operator<< (std::ostream & os, const Calendar<A> & cal) {
      for(auto it = cal.events.begin(); it != cal.events.end(); it++) {
        if((*it).date > cal.currentDate) {
          os << (*it).date << " : " << (*it).text << std::endl;
        }
      }

      return os;
    }

    Calendar() {}

    Calendar(const Date * date) {
      currentDate = *date;
    }

    Calendar(const Date & date) {
      currentDate = date;
    }

    template<class F>
    Calendar(const Calendar<F> & cal) {
      events = std::list<Event<T> >(cal.events.begin(), cal.events.end());
      currentDate = cal.currentDate;
    }

    //TODO: Remove me.
    T get_date() {
      return currentDate;
    }

    bool set_date(int year, int month, int day) {
      try {
        currentDate = T(year, month, day);
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

    bool add_event(const std::string & event, int day = -1, int month = -1, int year = -1) {
      try {
        if(exist(event, day, month, year)) {
          return false;
        }

        events.push_back(Event<T>(event, to_date(day, month, year)));
        events.sort();
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

    bool remove_event(const std::string & event, int day = -1, int month = -1, int year = -1) {
      try {
        auto pos = find(event, day, month, year);

        if(pos != events.end()) {
          events.erase(pos);
        } else {
          return false;
        }
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

  private:
    typename std::list<Event<T> >::const_iterator find(const std::string & event, int day = -1, int month = -1, int year = -1) const {
      Event<T> e(event, to_date(day, month, year));

      typename std::list<Event<T> >::const_iterator it = std::find(events.begin(), events.end(), e);
      return it;
    }

    bool exist(const std::string & event, int day = -1, int month = -1, int year = -1) const {
      return find(event, day, month, year) != events.end();
    }

    T to_date(int day = -1, int month = -1, int year = -1) const {
      if(day == -1 || month == -1 || year == -1) {
        int y = currentDate.year();
        int m = currentDate.month();
        int d = currentDate.day();

        if(year != -1) {
          y = year;
        }

        if(month != -1) {
          m = month;
        }

        if(day != -1) {
          d = day;
        }

        return T(y, m, d);
      }

      return T(year, month, day);
    }
  };
}

/* << operator. Function used to print object by ostream. */
//std::ostream & operator<< (std::ostream & os, const lab2::Calendar<lab2::Gregorian> & cal);
//std::ostream & operator<< (std::ostream & os, const lab2::Calendar<lab2::Julian> & cal);

#endif