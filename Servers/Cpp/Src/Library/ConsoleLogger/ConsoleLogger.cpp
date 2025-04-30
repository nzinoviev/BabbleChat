// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

/**
 * @file    ConsoleLogger.cpp
 * @brief   Реализация класса ConsoleLogger.
 */

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <format>

#include "Include/Library/Status.hpp"

#include "Include/Library/Logger.hpp"

///////////////////////////////////////////////////////////////////////////////
/// Helper Functions
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief   Возвращает текущее дату и время в виде строки в формате дд-мм-гггг чч:мм:сс.
 * @return  std::string Строка с текущими датой и временем.
 */
std::string
GetCurrentDateTime()
{
   std::ostringstream oss;

   std::time_t now = std::time(nullptr);
   std::tm tmNow{};

   localtime_r(&now, &tmNow);

   oss << std::put_time(&tmNow, "%d-%m-%Y %H:%M:%S");

   return oss.str();
}


/**
 * @brief   Перегрузка оператора вывода для LoggerMessageTag.
 *          Позволяет выводить значения перечисления LoggerMessageTag в виде строки.
 *
 * @param[in, out]   Os          Ссылка на выходной поток.
 * @param[in]        MessageTag  Значения перечисления LoggerMessageTag.
 *
 * @return std::ostream& Ссылка на выходной поток.
 */
std::ostream& operator<<(std::ostream& Os, LoggerMessageTag MessageTag)
{
   switch (MessageTag)
   {
   case LoggerMessageTag::Debug:
      Os << "Debug";
      break;

   case LoggerMessageTag::Info:
      Os << "Info";
      break;

   case LoggerMessageTag::Security:
      Os << "Security";
      break;
   }
   return Os;
}


/**
 * @brief   Перегрузка оператора вывода для LoggerResultTag.
 *          Позволяет выводить значения перечисления LoggerResultTag в виде строки.
 *
 * @param[in, out]   Os          Ссылка на выходной поток.
 * @param[in]        MessageTag  Значения перечисления LoggerResultTag.
 *
 * @return std::ostream& Ссылка на выходной поток.
 */
std::ostream& operator<<(std::ostream& Os, LoggerResultTag ResultTag)
{
   switch (ResultTag)
   {
   case LoggerResultTag::Success:
      Os << "Success";
      break;

   case LoggerResultTag::Warning:
      Os << "Warning";
      break;

   case LoggerResultTag::Error:
      Os << "Error";
      break;
   }
   return Os;
}


///////////////////////////////////////////////////////////////////////////////
/// Interface Implementation
///////////////////////////////////////////////////////////////////////////////

ConsoleLogger& ConsoleLogger::GetInstance()
{
   static ConsoleLogger logger;
   return logger;
}


Status ConsoleLogger::Log(
   const LoggerResultTag   ResultTag,
   const LoggerMessageTag  MessageTag,
   const std::string&      Message)
{
   Status status;

   do
   {
      std::ostringstream oss;
      oss << GetCurrentDateTime() << " " << "[" << ResultTag << "]" <<
            "[" << MessageTag << "]" << " " << Message;

      std::cerr << oss.str() << std::endl;

   } while (false);

   return status;
}