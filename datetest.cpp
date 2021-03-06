// projektlokala headerfiler
#include "kattistime.h"
#include "julian.h"
#include "gregorian.h"

// STL headerfiler
#include <iostream>
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <ctime>


// Obs att testerna f�ruts�tter att dina klasser returnerar
// m�nader och dagar indexerade fr�n ETT. Testerna �r inte
// fullst�ndiga


int main()
{
    set_k_time(100000);

    using namespace lab2;        // Exponera funktionalitet i namnrymden lab2

    {
      Julian j = Julian(1858, 11, 5);
      assert(j.mod_julian_day() == 0);
    }
    {
      Julian j = Julian(2858, 11, 5);
      assert(j.mod_julian_day() == 365250);
    }
    {
      Julian j = Julian(1600, 11, 5);
      assert(j.mod_julian_day() == -94234);
    }
    {
      Julian j = Julian(1858, 11, 4);
      assert(j.mod_julian_day() == -1);
    }
    {
      Julian j = Julian(1977, 1, 20);
      j.add_month(-5);
    }
    {
      Julian j = Julian(2604, 2, 29);
      j.add_year(1);

      assert(j.day() == 28);
    }
    {
      Julian j = Julian(2390, 2, 28);
      j.add_month(-2);
      assert(j.month() == 12);
      assert(j.day() == 28);
    }
    {
      Julian j = Julian(1998, 9, 6);
      Gregorian g;

      Date *to = &g;

      (*to) = j;

      assert(g.year() == 1998);
      assert(g.month() == 9);
      assert(g.day() == 19);
    }
    {
      Julian j(2100, 12, 27);

      Date *pj2 = &j;
      Date *pj = &j;
      (*pj2) = *(pj);

      assert(j.year() == 2100);
      assert(j.month() == 12);
      assert(j.day() == 27);
    }

    {
      Gregorian g(2013, 11, 23);

      assert(g.week_day_name() == "saturday");
      g++;
      assert(g.week_day_name() == "sunday");
      g++;
      assert(g.week_day_name() == "monday");
      g++;
      assert(g.week_day_name() == "tuesday");
      g++;
      assert(g.week_day_name() == "wednesday");
      g++;
      assert(g.week_day_name() == "thursday");
      g++;
      assert(g.week_day_name() == "friday");
      g++;
      assert(g.week_day_name() == "saturday");
      g++;
      assert(g.week_day_name() == "sunday");
      g++;
      assert(g.week_day_name() == "monday");
    }
    {
      Gregorian g(2013, 11, 23);

      assert(g.month_name() == "november");
      g.add_month();
      assert(g.month_name() == "december");
      g.add_month();
      assert(g.month_name() == "january");
      g.add_month();
      assert(g.month_name() == "february");
      g.add_month();
      assert(g.month_name() == "march");
      g.add_month();
      assert(g.month_name() == "april");
      g.add_month();
      assert(g.month_name() == "may");
      g.add_month();
      assert(g.month_name() == "june");
      g.add_month();
      assert(g.month_name() == "july");
      g.add_month();
      assert(g.month_name() == "august");
      g.add_month();
      assert(g.month_name() == "september");
      g.add_month();
      assert(g.month_name() == "october");
      g.add_month();
      assert(g.month_name() == "november");
      g.add_month();
      assert(g.month_name() == "december");
      g.add_month();
      assert(g.month_name() == "january");
      g.add_month();
      assert(g.month_name() == "february");
    }
    {
      Julian j;
      Gregorian g;

      assert(j >= g);
    }

    ////////////////////////////////////////////////////////////
    // S�tt tiden. OBS skicka inte nedanst�ende kod till kattis
    time_t mytime;
    time(&mytime);
    set_k_time(mytime);
    ////////////////////////////////////////////////////////////


    Julian tj;                  // ok: defaultkonstruktor ger dagens datum
    Gregorian gtoday;           // ok f�r gregorian ocks�
    std::cout << "Idag �r det " << gtoday << std::endl;
    std::cout << "Idag �r det " << tj << std::endl;
    std::cout << tj - gtoday;
    assert(tj - gtoday == 0);
    Gregorian tg(2006, 10, 31); // ok: s�tt datum explicit
                                // f�ljande fungerar ocks�:
                                // Gregorian(2000, Gregorian::October, 31)
    Date &j = tj;               // �tkomst av funktioner genom Dates interface
    Date &g = tg;
    Date &today = gtoday;

    {
      Julian j1;
      Date & d1 = j1;
      Julian j2(d1);
      Date * dp = &j2;
      Julian j3(dp);
    }

    time_t tp;
    time(&tp);
    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // m�naderna och dagarna
    int day   = t->tm_mday;         // indexerade fr�n ETT

    std::cout << "Testing constructors..." << std::endl;
    assert(today.year() == year &&          // r�tt initierad
           today.month() == month &&
           today.day() == day);
    assert(g.year() == 2006 &&              // r�tt initierad
           g.month() == 10 &&
           g.day() == 31);                  // obs! ettindexerade

    std::cout << "Testing access..." << std::endl;
    assert(g.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(j.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(g.days_this_month() == 31);      // r�tt antal dagar denna m�nad
    assert(g.months_per_year() == 12);      // r�tt antal m�nader per �r
    assert(j.months_per_year() == 12);      // r�tt antal m�nader per �r
    std::cout << g << " " << g.week_day();
    assert(g.week_day() == 2); // r�tt veckodag

    std::cout << "Testing manipulation..." << std::endl;
    ++g;                                    // prefix �kning
    assert(g.week_day() == 3); // r�tt veckodag
    --g;                                    // prefix minskning
    assert(g.week_day() == 2); // r�tt veckodag
    g += 2;                                 // l�gg till tv� dagar
    assert(g.week_day() == 4); // r�tt veckodag
    g -= 3;                     // dra bort tre dagar
    g.add_month();              // l�gg till en m�nad
    g.add_month(-1);            // dra bort en m�nad
    g.add_year(10);             // l�gg till tio �r.

    std::cout << "Testing miscellaneous functions..." << std::endl;
    Julian jj(tj);              // kopieringskonstruktor
    const Gregorian gg;
    gg.year();                  // gg konstant, l�sa g�r bra
    g = gg;                     // tilldelning
    if(g == gg ||               // j�mf�relse
       g != gg ||               // j�mf�relse
       g < gg ||                // j�mf�relse
       g >= gg)                 // j�mf�relse
        {}

    std::cout << "Testing boundary violations";
    Gregorian temp(1900, 1, 1);
    Date &d = temp;

    // loopa �ver dagar och kolla att inga gr�nser �ver/underskrids
    for(int i = 0; i < 100000; ++i, ++d)
        {
            if(!(i % 5000))        // utskrift p� framsteg
                {
                    std::cout << ".";
                    flush(std::cout);
                }
            int m[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(d.year() >= 1900 &&
               d.month() >= 1 && d.month() <= 12 &&
               d.day() >= 1 && d.day() <= m[d.month() - 1])
                {}
            else
                {
                    std::cout << std::endl;
                    std::cout << "boundary checks failed: " << std::endl;
                    std::cout << d.year() << ", "
                              << d.month() << ", "
                              << d.day() << std::endl;
                    return 1;
                }
        }
    std::cout << std::endl;

    std::cout << "Testing leap years..." << std::endl;
    // testa om skott�ren f�r sekelskiften fungerar som de ska
    for(int y = 1958; y < 2500; y += 100)
        {
            Gregorian temp(y, 2, 28);
            Date &e = temp;
            ++e;                                   // l�gg till en dag
            if((y % 400 == 0 && e.day() == 29) ||  // skottdag (obs! ETTindexerad)
               (y % 400 != 0 && e.day() == 1))     // ej skottdag
                {}
            else
                {
                    std::cout << std::endl << "leap day test failed: " << std::endl;
                    std::cout << e.year() << ", "
                              << e.month() << ", "
                              << e.day() << std::endl;
                    return 1;
                }
        }

    std::cout << std::endl << "All tests were successful." << std::endl;

    // f�ljande ska inte g� att kompilera
#if 0
    gg.leap_year();             // fel: kan inte komma �t protected/private medlem
    gg = g;                     // fel: kan inte tilldela konstant
    ++gg;                       // fel: kan inte �ndra p� en konstant
#endif

    return 0;
}
