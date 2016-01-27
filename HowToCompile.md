# How to compile #

  * Download and install [Visual C++ 2008 Express Edition](http://msdn.microsoft.com/en-us/express/future/bb421473) and [Visual C++ 2010 Express Edition](http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express). The 2008 edition is needed for the v90 Platform Toolkit, the bot will not compile with the v100 Platform Toolkit offered by the 2010 edition.
  * Download and unzip BWAPI from http://code.google.com/p/bwapi/.
  * Download and install Boost from http://www.boost.org/.
  * Create two environment variables in Windows ([how to](http://www.itechtalk.com/thread3595.html)):
    * **BOOST** pointing to _boost-installation-dir_/boost\_x\_xx (for example: C:\Program Files (x86)\boost\boost\_1\_44)
    * **BWAPI** pointing to _bwapi-unzip-dir_/BWAPI\_x.x.x (for example: C:\Users\User\Documents\bwapi\BWAPI\_3.6.1)
  * Check out the source to a directory.
  * Open the .sln file in Visual C++ 2010 Express Edition, change _Debug_ to _Release_ and compile with F7.