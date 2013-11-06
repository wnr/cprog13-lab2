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

    // template<class A>
    // friend std::ostream & operator<< (std::ostream & os, const Event<A> & event) {
    //   os << event.date << " : " << event.text;
    //   return os;
    // }
  };

  template<typename T>
  class Calendar {
    std::list<Event<T> > events;

    T currentDate;

  public:
    friend class Calendar<Julian>;
    friend class Calendar<Gregorian>;

    friend std::ostream & operator<< (std::ostream & os, const Calendar & cal) {
      for(typename std::list<Event<T> >::const_iterator it = cal.events.begin(); it != cal.events.end(); it++) {
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

    bool set_date(int year) {
      return set_date(year, currentDate.month(), currentDate.day());
    }

    bool set_date(int year, int month) {
      return set_date(year, month, currentDate.day());
    }

    bool set_date(int year, int month, int day) {
      try {
        currentDate = T(year, month, day);
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

    bool add_event(const std::string & event) {
      return add_event(event, currentDate);
    }

    bool add_event(const std::string & event, int day) {
      return add_event(event, day, currentDate.month(), currentDate.year());
    }

    bool add_event(const std::string & event, int day, int month) {
      return add_event(event, day, month, currentDate.year());
    }

    bool add_event(const std::string & event, int day, int month, int year) {
      try {
        return add_event(event, T(year, month, day));
      } catch(std::out_of_range oor) {
        return false;
      }
    }

    bool add_event(const std::string & event, const T & date) {
      if(exist(event, date)) {
        return false;
      }

      events.push_back(Event<T>(event, date));
      events.sort();

      return true;
    }

    bool remove_event(const std::string & event) {
      return remove_event(event, currentDate);
    }

    bool remove_event(const std::string & event, int day) {
      return remove_event(event, day, currentDate.month(), currentDate.year());
    }

    bool remove_event(const std::string & event, int day, int month) {
      return remove_event(event, day, month, currentDate.year());
    }

    bool remove_event(const std::string & event, int day, int month, int year) {
      try {
        return remove_event(event, T(year, month, day));
      } catch(std::out_of_range oor) {
        return false;
      }
    }

    bool remove_event(const std::string & event, const T & date) {
      typename std::list<Event<T> >::iterator pos = find(event, date);

      if(pos == events.end()) {
        return false;
      }

      events.erase(pos);

      return true;
    }

  private:
    typename std::list<Event<T> >::iterator find(const std::string & event, const T & date) {
      Event<T> e(event, date);

      typename std::list<Event<T> >::iterator it = std::find(events.begin(), events.end(), e);
      return it;
    }

    typename std::list<Event<T> >::const_iterator find(const std::string & event, const T & date) const {
      Event<T> e(event, date);

      typename std::list<Event<T> >::const_iterator it = std::find(events.begin(), events.end(), e);
      return it;
    }

    bool exist(const std::string & event, const T & date) const {
      return find(event, date) != events.end();
    }
  };
}

/* << operator. Function used to print object by ostream. */
//std::ostream & operator<< (std::ostream & os, const lab2::Calendar<lab2::Gregorian> & cal);
//std::ostream & operator<< (std::ostream & os, const lab2::Calendar<lab2::Julian> & cal);

#endif
