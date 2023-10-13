#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <cassert>

namespace recipe_6_01
{
   void execute()
   {
      {
         std::chrono::hours         half_day(12);
         std::chrono::minutes       half_hour(30);
         std::chrono::seconds       half_minute(30);
         std::chrono::milliseconds  half_second(500);
         std::chrono::microseconds  half_milisecond(500);
         std::chrono::nanoseconds   half_microsecond(500);
      }

      {
         using namespace std::chrono_literals;

         auto half_day        = 12h;
         auto half_hour       = 30min;
         auto half_minute     = 30s;
         auto half_second     = 500ms;
         auto half_milisecond = 500us;
         auto half_microsecond= 500ns;
      }

      {
         std::chrono::hours   half_day_in_h(12);
         std::chrono::minutes half_day_in_min(half_day_in_h);
         // direct conversion from a lower precision duration to a higher precision duration.
         // 低精度duration(按小时)可以直接转换成高精度duration(按分钟);

         std::cout << half_day_in_h.count() << "h" << '\n';
         std::cout << half_day_in_min.count() << "min" << '\n';
         // counter 本精度下的个数。
      }

      {
         using namespace std::chrono_literals;

         auto total_seconds = 12345s;
         auto hours = std::chrono::duration_cast<std::chrono::hours>(total_seconds);
         auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total_seconds % 1h);
         auto seconds = std::chrono::duration_cast<std::chrono::seconds>(total_seconds % 1min);
         
         std::cout << hours.count() << ':' 
                   << minutes.count() << ':' 
                   << seconds.count() << '\n'; // 3:25:45
        /*
          duration_cast 从高精度向低精度cast，取整，零头扔掉。
          比如std::chrono::duration_cast<std::chrono::minutes>(total_seconds) 结果是205min，即12300 sec。

          auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total_seconds % 1h); 则是去掉整小时后
          再计算有多少分钟，结果是25min，零头也被去掉。

          up cast，比如从hour to minutes 则不需要用duration_cast, 引用cppref note：
          Casting between integer durations where the source period is exactly divisible by the target period
          (e.g. hours to minutes) or between floating-point durations can be performed with ordinary casts
          or implicitly via std::chrono::duration constructors, no duration_cast is needed. 
          
        */
      }

      {
         using namespace std::chrono_literals;

         auto total_seconds = 12345s;
         auto m1 = std::chrono::floor<std::chrono::minutes>(total_seconds); // 205 min
         auto m2 = std::chrono::round<std::chrono::minutes>(total_seconds); // 206 min
         auto m3 = std::chrono::ceil<std::chrono::minutes>(total_seconds);  // 206 min
         auto sa = std::chrono::abs(total_seconds);

         // 如上，从sec类型cast到min类型的细节。
         // 具体应用中会用到时间的rounding，比如跑了205min以上的人都到206min一档。
      }

      {
         using namespace std::chrono_literals;

         auto d1 = 1h + 23min + 45s; // d1 = 5025s
         auto d2 = 3h + 12min + 50s; // d2 = 11570s
         if (d1 < d2) {}

         // 还可以进行arithmetic operations， comparision oeprations.
         // 这样的话，基于一个base time point，比如今天零点，去拼出一个固定时间就不难了。比如今天股票开盘时间。
      }

      {
         using namespace std::chrono_literals;

         std::chrono::duration<double, std::ratio<10>> d(1.2); // 12 sec

         assert(std::chrono::duration_cast<std::chrono::seconds>(d).count() == (12s).count());

         /*
          h/m/s 是60进制的数。
          s/ms/us/ns 是1000进制

          chrono中以上这些都是独立类型，可以互相cast。
          实现这些类型的基础是ratio<x,y>（默认的基础单位是秒，其他类型由秒来构建）
         故也可以diy一个类型，比如上面的10sec，而且指还可以是小数，比如1.2代表12秒。
            
        */

      }
   }
}
