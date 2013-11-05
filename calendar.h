#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include <list>
#include <tuple>
#include <iterator>

namespace lab2 {
  template<typename T>
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

  template<typename T>
  class Calendar {
    std::list<Event<T>> events;

    T currentDate;

  public:
    Calendar() {}

    Calendar(const Calendar & cal) {
      events = cal.events;
      currentDate = cal.currentDate;
    }

    bool set_date(int year, int month, int day) {
      try {
        currentDate = T(year, month, day);
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

    bool add_event(const std::string & event, int day, int month, int year) {
      try {
        if(exist(event, day, month, year)) {
          return false;
        }

        events.append(Event<T>(event, T(year, month, day)));
      } catch(std::out_of_range oor) {
        return false;
      }

      return true;
    }

    bool add_event(const std::string & event) {
      T d;

      return add_event(event, d.day(), d.month(), d.year());
    }

    bool remove_event(const std::string & event, int day, int month, int year) {
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
    typename std::list<Event<T>>::iterator find(const std::string & event, int day, int month, int year) const {
      Event<T> e(event, T(year, month, day));

      return std::find(events.begin(), events.end(), e);
    }

    bool exist(const std::string & event, int day, int month, int year) const {
      return find(event, day, month, year) != events.end();
    }
  };
}

#endif