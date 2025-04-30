/**
 * @file    Timer.hpp
 * @brief   Реализация простейшего таймера с размерностью - микросекунды.
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <iostream>
#include <string>


/**
 * @class   Timer
 * @brief   Класс Timer измеряет время выполнения между двумя событиями (Start/Stop)
 *          с точностью до микросекунд.
 */
class Timer
{
public:
   /**
    * @brief Конструктор по умолчанию. Также запускат таймер.
    */
   Timer()
   :  startTimepoint_(std::chrono::high_resolution_clock::now()),
      endTimepoint_(startTimepoint_),
      isRunning_(true)
   { }


   /**
    * @brief   Запускает таймер.
    */
   void Start()
   {
      isRunning_ = true;
      startTimepoint_ = std::chrono::high_resolution_clock::now();
   }


   /**
    * @brief Останавливает таймер.
    */
   void Stop()
   {
      endTimepoint_ = std::chrono::high_resolution_clock::now();
      isRunning_ = false;
   }


   /**
    * @brief   Возвращает прошеднее время в микросекундах.
    */
   double ElapsedMicroseconds() const
   {
      auto end = isRunning_ ? std::chrono::high_resolution_clock::now() : endTimepoint_;
      return std::chrono::duration<double, std::micro>(end - startTimepoint_).count();
   }

private:
   friend std::ostream& operator<<(std::ostream& Os, const Timer& Timer)
   {
      return Os << Timer.ElapsedMicroseconds() << " microseconds";
   }

private:
   bool isRunning_;
   std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint_;
   std::chrono::time_point<std::chrono::high_resolution_clock> endTimepoint_;
};

#endif // __TIMER_H__