/**
 * @file    String.cpp
 * @brief   Файл с имплементацией класса String.
 */

#include <cstring> // Для std::memcpy.
#include <stdexcept>

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
   dataSize_(0),
   length_(0) {}


String::String(const char* Str) {
   if (nullptr == Str) {
      throw std::runtime_error("Invalid argument in String Constructor. Str in nullptr.");
   }

   dataSize_ = Strlen(Str) + sizeof('\0');
   try {
      data_ = new char[dataSize_];
      length_ = dataSize_ - 1;
   }
   catch (const std::bad_alloc&) {
      data_ = nullptr;
      dataSize_ = 0;
      length_ = 0;
      throw std::runtime_error("Bad Alloc in String Constructor.");
   }

   std::memcpy(data_, Str, dataSize_);
}


String::~String() {
   delete[] data_;
}




std::size_t String::Length() {
   return length_;
}


char* String::Data() {
   return data_;
}

}