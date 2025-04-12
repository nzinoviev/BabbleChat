/**
 * @file    Solid.cpp
 * @brief   Пример кода, следующего принципам SOLID.
 *
 * @details SOLID - набор пяти принципов ООП, направленных на создание гибкого, легко поддерживаемого
 *          и масштабируемого ПО. Эти принципы помогают строить архитектуру приложений таким образом,
 *          чтобы отдельные компоненты имели минимальную связанность и максимальную самостоятельность.
 *          - Single Responsibility: каждый класс или модуль должен иметь лишь одну причину для
 *          изменения, то есть отвечать за одну единственную задачу.
 *          - Open/Closed: Классы, модули и функции должны быть открыты для расширения, но закрыты
 *          для модификации.
 *          - Liskov Substitution: Объекты базового класса должны быть заменяемы объектами его
 *          подклассов без нарушения корректности работы программы.
 *          - Interface Segregation: Лучше иметь несколько специализированных интерфейсов, чем
 *          один универсальный, который содержит методы, не используемые всеми клиентами.
 *          - Dependency Inversion: Модули верхних уровней не должны зависеть от модулей нижних
 *          уровней, обе группы должны зависеть от абстракций. Абстракции не должны зависеть от
 *          деталей. Детали должны зависеть от абстракций.
 */

#include <iostream>
#include <memory>
#include <string>


// -- Interface Segregation --
// Интерфейс для отправки уведомлений.
class INotifier
{
public:
   virtual void Send(const std::string& Message) = 0;
   virtual ~INotifier() = default;
};


// Интерфейс для журналирования.
class ILogger
{
public:
   virtual void Log(const std::string& Message) = 0;
   virtual ~ILogger() = default;
};


// -- Single Responsibility --
// Класс для отправки уведомлений по email.
class EmailNotifier : public INotifier
{
public:
   void Send(const std::string& Message) override
   {
      std::cout << "Sending email: " << Message << std::endl;
   }
};


// Класс для отправки уведомлений по sms.
class SmsNotifier : public INotifier
{
public:
   void Send(const std::string& Message) override
   {
      std::cout << "Sending: " << Message << std::endl;
   }
};


// Класс для логирования к консоль.
class ConsoleLogger : public ILogger
{
public:
   void Log(const std::string& Message) override
   {
      std::cout << "Log: " << Message << std::endl;
   }
};


// -- Dependency Inversion --
// Класс NotificationManager зависит от абстракций INotofier и ILogger.
class NotificationManager
{
public:
   NotificationManager(
      std::shared_ptr<INotifier> Notifier,
      std::shared_ptr<ILogger>   Logger) : notifier_(Notifier), logger_(Logger) {}

      void NotifyUser(const std::string& Message)
      {
         // Отправка уведомления через абстракцию INotifier.
         notifier_->Send(Message);
         // Журналирование уведомления через абстракцию ILogger.
         logger_->Log("Notification sent: " + Message);
      }

private:
   std::shared_ptr<INotifier> notifier_;
   std::shared_ptr<ILogger>   logger_;
};


// -- Open/Closed and Liskov Substitution
// Благодаря реализации абстракции INotifier, можно легко менять способы отправки уведомлений.
int main()
{
   // Используем EmailNotifier для отправки уведомлений.
   std::shared_ptr<INotifier> emailNotifier = std::make_shared<EmailNotifier>();
   std::shared_ptr<ILogger> consoleLogger = std::make_shared<ConsoleLogger>();

   // NotificationManager работает через интерфейсы, не завися от конкретных реализаций.
   NotificationManager notificationManager(emailNotifier, consoleLogger);
   notificationManager.NotifyUser("Hello from SOLID design!");

   // Для отправки по sms достаточно создать новй класс, реализующий INotifier.
   std::shared_ptr<INotifier> smsNotifier = std::make_shared<SmsNotifier>();
   NotificationManager smsNotificationManager(smsNotifier, consoleLogger);
   smsNotificationManager.NotifyUser("Hello via sms!");

   return 0;
}