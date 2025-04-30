// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

/**
 * @file    Logger.hpp
 * @brief   Содержит интерфейс логгера и реализующие его классы.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>

#include "Include/Library/Status.hpp"


/**
 * @enum    LoggerMessageTag
 * @brief   Перечисление, определяющее категорию (тематику) журналируемого события.
 */
enum class LoggerMessageTag
{
   /**
    * Отладочная информация. Используется для вывода технических деталей, полезных при разработке
    * и отладке.
    */
   Debug,

   /**
    * Информационное сообщение. Описывает стандартные события жизненного цикла системы,
    * такие как запуск, завершение или состояние.
    */
   Info,

   /**
    * Сообщение, связанное с безопасностью. Отражает события, связанные с аутентификацией,
    * правами доступа, нарушениями безопасности и т.п.
    */
   Security
};


/**
 * @enum    LoggerResultTag
 * @brief   Перечисление, определяющие теги, описывающие результат выполнения операции.
 *          Используется для указания статуса завершения операций, заносимых в журнал.
 */
enum class LoggerResultTag
{
   /**
    * Операция была выполнена штатно, без ошибок и предупреждений.
    * Такой результат указывает на корректное и ожидаемое поведение системы.
    */
   Success,

   /**
    * Операция была выполнена успешно, однако в процессе возникло предупреждение,
    * не повлиявшее на общий ход работы. Такие сообщения могут сигнализировать о возможных
    * неисправностях или нестандартных ситуациях.
    */
   Warning,

   /**
    * Операция завершилась ошибкой. Такое сообщение указывает на критический сбой в
    * процессе выполнения.
    */
   Error
};


/**
 * @class   ILogger
 * @brief   Интерфейс логгера.
 */
class ILogger
{
public:
   /**
    * @brief Запись сообщения в журнал.
    *
    * @param[in]  ResultTag   Тег, описывающий результат операции.
    * @param[in]  MessageTag  Тег, описывающий категорию сообщения.
    * @param[in]  Message     Сообщение, подлежащее журналированию.
    *
    * @return Статус выполнения операции журналирования.
    */
   virtual
   Status
   Log(
      const LoggerResultTag   ResultTag,
      const LoggerMessageTag  MessageTag,
      const std::string&      Message) = 0;


   /**
    * @brief Виртуальный деструктор для корректного удаления производных классов.
    */
   virtual ~ILogger() = default;
};


/**
 * @class   FileLogger
 * @brief   Реализация логгера, производящего запись в файл. Используется паттерн Singleton.
 */
class FileLogger final : public ILogger
{
public:
   /**
    * @brief   Возвращает единственный экземпляр логгера.
    * @return  Ссылка на единственный экземпляр логгера.
    */
   static FileLogger& GetInstance();

   Status
   Log(
      const LoggerResultTag   ResultTag,
      const LoggerMessageTag  MessageTag,
      const std::string&      Message) override;

private:
   /**
    * @brief   Приватный конструктор, предотвращающий создание экземпляров извне.
    * @details Открывает лог-файл и нициализирует внутреннее состояние логгера.
    *          Используется только внутри метода GetInstance();
    */
   explicit FileLogger();

   FileLogger(const FileLogger&) = delete;            /** Удаляем конструктор копирования. */
   FileLogger& operator=(const FileLogger&) = delete; /** Удаляем оператор присваивания. */

private:
   std::ofstream  logFile_;   /** Поток файла, используемый для записи логов. */
   bool           isReady_;   /** Флаг, указывающий на успешное открытие файла. */
};


/**
 * @class   ConsoleLogger
 * @brief   Реализация логгера, производящего запись в консоль. Используется паттерн Singleton.
 */
class ConsoleLogger final : public ILogger
{
public:
   /**
    * @brief   Возвращает единственный экземпляр логгера.
    * @return  Ссылка на единственный экземпляр логгера.
    */
   static ConsoleLogger& GetInstance();

   Status
   Log(
      const LoggerResultTag   ResultTag,
      const LoggerMessageTag  MessageTag,
      const std::string&      Message) override;


   template <typename... Args>
   Status Log(
      const LoggerResultTag         ResultTag,
      const LoggerMessageTag        MessageTag,
      std::format_string<Args...>   Fmt,
      Args&&...                     Arguments);

private:
   /**
    * @brief   Приватный конструктор, предотвращающий создание экземпляров извне.
    *          Используется только внутри метода GetInstance();
    */
   explicit ConsoleLogger() = default;

   ConsoleLogger(const ConsoleLogger&) = delete;            /** Удаляем конструктор копирования. */
   ConsoleLogger& operator=(const ConsoleLogger&) = delete; /** Удаляем оператор присваивания. */
};


template <typename... Args>
Status ConsoleLogger::Log(
   const LoggerResultTag         ResultTag,
   const LoggerMessageTag        MessageTag,
   std::format_string<Args...>   Fmt,
   Args&&...                     Arguments)
{
   std::string message = std::format(Fmt, std::forward<Args>(Arguments)...);
   return Log(ResultTag, MessageTag, message);
}

#endif // __LOGGER_H__