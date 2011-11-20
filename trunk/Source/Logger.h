#include <string>
#include <time.h>

class Logger{
public:
   static Logger* getInstance();
   void debug(const char* str);
   void error(const char* str);
   void info(const char* str);

private:
   Logger();  // Private so that it can  not be called
   Logger(Logger const&){};             // copy constructor is private
   Logger& operator=(Logger const&){};  // assignment operator is private
   static Logger* m_pInstance;
   std::string filename;
   void log(const char* text, ...);
   tm* getTime();
   void formatLog(const char* level, const char* text);
};