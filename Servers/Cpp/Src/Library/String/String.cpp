/**
 * @file    String.cpp
 * @brief   Файл с имплементацией класса String.
 */

#include <cstring> // Для std::memcpy.

#include "Include/Library/String.hpp"

namespace BabbleChat {

///////////////////////////////////////////////////////////////////////////////
/// Вспомогательные фукнции
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Вычисляет длину null-терминированной строки.
 *
 * @param[in] Str Указатель на null-терминированную строку.
 *
 * @return Количество символов в строке (не включая \0). Если Str равен nullptr, возвращает 0.
 */
std::size_t
Strlen(const char* Str) {
   std::size_t length = 0;

   do {
      if (nullptr == Str) {
         break;
      }

      while (*Str) {
         ++length;
         ++Str;
      }

   } while (false);

   return length;
}


///////////////////////////////////////////////////////////////////////////////
/// Реализация интерфейса.
///////////////////////////////////////////////////////////////////////////////

String::String() :
   data_(nullptr),
   dataSize_(0) {}


String::String(const char* Str) {
   std::size_t dataSize = Strlen(Str) + sizeof('\0');
   data_ = new char[dataSize]; // Как обработать ошибку выделения памяти?
   std::memcpy(data_, Str, dataSize); // Как обработать ошибку при копировании памяти?
   dataSize_ = dataSize;
}


String::~String() {
   delete[] data_;
}

}