#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include <list>
#include <tuple>

namespace lab2 {
  template<class T>
  class Calendar {
    struct Event {
      std::string text;
      T date;

      Event(const std::string & t, const T & d) : text(t), date(t) {}

      bool operator< (const Event & e) const {
        return date < e.date;
      }

      bool operator== (const Event & e) const {
        return date == e.date;
      }
    };

    std::list<Event> events;

    T currentDate;

  public:
    Calendar();

    Calendar(const Calendar & cal);

    bool set_date(int year, int month, int day);

    bool add_event(const std::string & event, int day, int month, int year);
    bool add_event(const std::string & event);

    bool remove_event(const std::string & event, int day, int month, int year);

  private:
    std::iterator<Event> find(const std::string & event, int day, int month, int year) const;
    bool exist(const std::string & event, int day, int month, int year) const;
  };
}

#endif