// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


/**
 * @file    String.hpp
 * @brief   Заголовочный файл с описание класса String, реализующего часть функционала std::string.
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <cstddef>
#include <cstdint>

namespace BabbleChat {

/**
 * @class   String
 * @brief   Минималистичная реализация строки с поддержкой SSO.
 * @details Гарантирует, что строка будет завершаться \0.
 */
class String {
public:
   /**
    * @brief Конструктор по умолчанию. Создает пустую строку.
    */
   String() noexcept;

   /**
    * @brief Конструктор из C-строки и её длины.
    * @param[in]  CString  C-строка.
    * @param[in]  Length   Количество символов в CString (без учета \0).
    */
   explicit
   String(const char* CString, std::size_t Length);

   /**
    * @brief Конструктор из C-строки.
    * @param[in]  CString  C-строка.
    */
   explicit
   String(const char* CString);

   /**
    * @brief Конструктор копирования.
    * @param[in]  Other Объект на основе которого будет выполняться копирование.
    */
   String(const String& Other);

   /**
    * @brief Деструктор. Освобождает выделенную память, если строка находится в куче.
    */
   ~String();


   /**
    * @brief   Оператор копирующего присваивания.
    * @param[in]  Other Строка, которую нужно присвоить.
    * @return  Ссылка на текущий объект.
    */
   String& operator=(const String& Other);

   /**
    * @brief   Возвращает длину строки (без учета \0).
    * @return  Количество символов.
    */
   std::size_t
   Length() const noexcept;

   /**
    * @brief   Возвращает C-строку.
    * @return  C-строка.
    */
   const char*
   CStr() const;

   /**
    * @brief Проверяет, пута ли строка.
    * @retval  true   Если строка пуста.
    * @retval  false  Если строка не пуста.
    */
   bool
   IsEmpty() const noexcept;

private:
   /**
    * Максимальная длина строки для хранения в sso_buffer_.
    * Строки длиной до 15 символов (не включая \0) хранятся прямо внутри объекта
    * без выделения памяти в куче.
    */
   static constexpr std::size_t sso_capacity_ = 15;

   /**
    * Указатель на данные строки.
    * Указывает либо на sso_buffer_, либо на память, выделенную в куче.
    */
   char* heap_data_;

   /**
    * Длина строки (не включая \0).
    **/
   std::size_t length_;

   /**
    * Анонимное объединение для реализации SSO или хранения allocated_capacity_
    * для heap-строки.
    */
   union {
      /**
       * Буфер для хранения короткой строки (до 15 символов).
       * Последний байт зарезервирован для \0.
       */
      char sso_buffer_[sso_capacity_ + 1];

      /**
       * Ёмкость выделенной памяти в куче (без учета \0).
       */
      std::size_t allocated_capacity_;
   };
};

}

#endif // __STRING_H__