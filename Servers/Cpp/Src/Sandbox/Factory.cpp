#include <iostream>


class Product
{
public:
   virtual void Use() = 0;
   virtual ~Product() = default;
};


class Product_A : public Product
{
public:
   void Use() override
   {
      // Реализация для A.
   }
};


class Product_B : public Product
{
public:
   void Use() override
   {
      // Реализация для B.
   }
};


// Базовый класс фабрики.
class Creator
{
public:
   virtual Product* FactoryMethod() = 0;
   virtual ~Creator() = default;
};


class Creator_A : public Creator
{
public:
   Product* FactoryMethod() override
   {
      return new Product_A();
   }
};


class Creator_B : public Creator
{
public:
   Product* FactoryMethod() override
   {
      return new Product_B();
   }
};


int main()
{
   return 0;
}