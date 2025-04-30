// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


/**
 * @file    String.cpp
 * @brief   Файл с имплементацией класса String.
 */

#include <cstddef>
#include <cstring>
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
Strlen(
   const char* Str) noexcept
{
   std::size_t length = 0;

   do
   {
      if (nullptr == Str)
      {
         break;
      }

      while (*Str)
      {
         ++length;
         ++Str;
      }

   } while (false);

   return length;
}


///////////////////////////////////////////////////////////////////////////////
/// Реализация интерфейса.
///////////////////////////////////////////////////////////////////////////////

String::String() noexcept
   :  heap_data_(sso_buffer_),
      length_(0)
{
   sso_buffer_[0] = '\0';
}


String::~String()
{
   if (heap_data_ != sso_buffer_)
   {
      delete[] heap_data_;
   }
}


String::String(
   const char* CString,
   std::size_t Length)
{
   if (Length <= sso_capacity_)
   {
      std::memcpy(sso_buffer_, CString, Length);
      sso_buffer_[Length] = 0;
      heap_data_ = sso_buffer_;
      length_ = Length;
   }
   else
   {
      heap_data_ = new char[Length + 1];
      std::memcpy(heap_data_, CString, Length);
      heap_data_[Length] = '\0';
      length_ = Length;
      allocated_capacity_ = Length;
   }
}


String::String(const char* CString)
   : String(CString, Strlen(CString))
{ }


String::String(const String& Other)
{
   length_ = Other.length_;

   if (Other.length_ <= sso_capacity_)
   {
      std::memcpy(sso_buffer_, Other.sso_buffer_, length_ + 1);
      heap_data_ = sso_buffer_;
   }
   else
   {
      heap_data_ = new char[length_ + 1];
      std::memcpy(heap_data_, Other.heap_data_, length_ + 1);
      allocated_capacity_ = Other.allocated_capacity_;
   }
}


String& String::operator=(const String& Other)
{
   if (this == &Other)
   {
      return *this;
   }

   if (heap_data_ != sso_buffer_)
   {
      delete[] heap_data_;
   }

   length_ = Other.length_;

   if (Other.length_ <= sso_capacity_)
   {
      std::memcpy(sso_buffer_, Other.sso_buffer_, length_ + 1);
      heap_data_ = sso_buffer_;
   }
   else
   {
      heap_data_ = new char[length_ + 1];
      std::memcpy(heap_data_, Other.heap_data_, length_ + 1);
      allocated_capacity_ = Other.allocated_capacity_;
   }

   return *this;
}


const char*
String::CStr() const
{
   return heap_data_;
}


std::size_t
String::Length() const noexcept
{
   return length_;
}


bool
String::IsEmpty() const noexcept
{
   return 0 == length_;
}

}