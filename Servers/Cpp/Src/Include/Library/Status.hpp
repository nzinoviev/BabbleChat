// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

/**
 * @file    Status.hpp
 * @brief   Header-only библиотека для работы со статус-кодами.
 */

#ifndef __STATUS_H__
#define __STATUS_H__

#include <string>
#include <string_view>


/**
 * @enum    StatusCode
 * @brief   Перечисление для представления статус-кодов операции.
 */
enum class StatusCode
{
   Success,             /** Операция выполнена успешно. */
   Unsuccess,           /** Операция завершилась неудачно (общий код ошибки). */
   InvalidParameter,    /** Передан неверный параметр. */
   BadMemoryAllocation, /** Ошибка выделения памяти. */
   Unsupported,         /** Запрошенная операция не поддерживается. */
   BadBufferSize,       /** Некорректный размер буфера. */
   BufferTooSmall,      /** Переданный буфер слишком маленький. */
   NotFound,            /** Элемент или объект не найден. */
   AlreadyExists,       /** Элемент или объект уже существуют. */
};


/**
 * @brief Преобразует значение перечисления StatusCode в строковое представление.
 * @param[in]  Code  Значение перечисления StatusCode, которое необходимо преобразовать в строку.
 * @return std::string_view Строковое представление переданного статус-кода.
 */
constexpr std::string_view StatusCodeToString(const StatusCode Code)
{
   switch (Code)
   {
   case StatusCode::Success:
      return "Success";

   case StatusCode::Unsuccess:
      return "Unsuccess";

   case StatusCode::InvalidParameter:
      return "InvalidParameter";

   case StatusCode::Unsupported:
      return "Unsupported";

   case StatusCode::BadBufferSize:
      return "BadBufferSize";

   case StatusCode::BufferTooSmall:
      return "BufferTooSmall";

   case StatusCode::NotFound:
      return "NotFound";

   case StatusCode::AlreadyExists:
      return "AlreadyExists";

   case StatusCode::BadMemoryAllocation:
      return "BadMemoryAllocation";

   default:
      return "Unknown";
   }
}


/**
 * @class   Status
 * @brief   Класс для работы со статус-кодами операций.
 *
 * @details Этот класс хранит статус выполнения операции. По умолчанию статус считается
 *          успешным (StatusCode::Success). Предоставляет возможность использовать объект как
 *          булевское значение для удобной проверки результат.
 */
class Status
{
public:
   /**
    * @brief Конструктор по умолчанию. Инициализирует статус значением StatusCode::Success.
    */
   Status() : code_(StatusCode::Success) {}

   /**
    * @brief Конструктор с заданным статус-кодом.
    * @param[in] Code Статус-код, задающий результат операции.
    */
   Status(StatusCode Code) : code_(Code) {}

   /**
    * @brief Оператор преобразования к bool.
    *
    * @details Позволяет использовать объект в логических выражениях.
    *          Возвращает true, если статус равен StatusCode::Success.
    */
   explicit operator bool() const
   {
      return code_ == StatusCode::Success;
   }

   /**
    * @brief   Возвращает текущий статус-код.
    * @return  StatusCode текущий статус-код.
    */
   StatusCode GetStatusCode() const
   {
      return code_;
   }


   /**
    * @brief   Преобразует текущий статус-код в строковое представление.
    * @return  std::string Строковое представление текущего статус-кода.
    */
   std::string ToString() const
   {
      return std::string(::StatusCodeToString(code_));
   }

private:
   StatusCode code_; /** Статус-код операции. */
};

#endif // __STATUS_H__