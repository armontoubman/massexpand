#include "logger.h"

#include <fstream>
#include <stdarg.h>
#include <sys/stat.h>
#include <sstream>

#include <time.h>

#include "Util.h"

// Global static pointer used to ensure a single instance of the class.
Logger* Logger::m_pInstance = NULL;  

/** This function is called to create an instance of the class. 
    Calling the constructor publicly is not allowed. The constructor 
    is private and is only called by this Instance function.
*/
  
Logger* Logger::getInstance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Logger;

   return m_pInstance;
}

Logger::Logger()
{
	tm* timeinfo = this->getTime();

	char buffer[50];
	int n = sprintf(buffer, "bwapi-data\\logs\\%02d-%02d-%02d_%02d-%02d-%02d.log", timeinfo->tm_year+1900, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	this->filename = std::string(buffer);
}

void Logger::log(const char* text, ...)
{
  const int BUFFER_SIZE = 1024;
  char buffer[BUFFER_SIZE];

  va_list ap;
  va_start(ap, text);
  vsnprintf_s(buffer, BUFFER_SIZE, BUFFER_SIZE, text, ap);
  va_end(ap);

  FILE *outfile;
  if (fopen_s(&outfile, this->filename.c_str(), "a+")==0)
  {
    fprintf_s(outfile, buffer);
    fclose(outfile);
  }
}

tm* Logger::getTime()
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	return localtime ( &rawtime );
}

void Logger::debug(const char* text)
{
	this->formatLog("DEBUG", text);
}

void Logger::error(const char* text)
{
	this->formatLog("ERROR", text);
}

void Logger::info(const char* text)
{
	this->formatLog("INFO", text);
}

void Logger::formatLog(const char* level, const char* text)
{
	std::string log;
	log.append(level);
	log.append("\t");

	tm* timeinfo = this->getTime();
	char buffer[50];
	int n = sprintf(buffer, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	log.append(buffer);
	log.append("\t");

	log.append(text);
	log.append("\r\n");

	this->log(log.c_str());
}