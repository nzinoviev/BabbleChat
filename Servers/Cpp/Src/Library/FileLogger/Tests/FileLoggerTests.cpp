#include "Include/Library/Logger.hpp"


int main()
{
   Status status = StatusCode::BadBufferSize;
   FileLogger& fileLogger = FileLogger::GetInstance();
   fileLogger.Log(LoggerResultTag::Error, LoggerMessageTag::Info, "Message " + status.ToString());
   return 0;
}