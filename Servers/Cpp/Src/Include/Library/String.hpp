/**
 * @file    String.hpp
 * @brief   Заголовочный файл с описание класса String.
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <cstddef> // Для std::size_t.

namespace BabbleChat {

/**
 * @class   String
 * @brief   Класс, реализующий часть функционала std::string.
 */
class String {
public:
   /**
    * @brief Конструктор по умолчанию. Создает пустую строку.
    */
   String();

   /**
    * @brief Конструктор из C-строки.
    *
    * @param[in] Str Указатель на null-терминированную строку.
    */
   String(const char* Str);

   /**
    * @brief Деструктор.
    */
   ~String();

private:
   char*       data_;      /** Указатель на данные. */
   std::size_t dataSize_;  /** Размер данных в байтах. */
};

}

#endif // __STRING_H__