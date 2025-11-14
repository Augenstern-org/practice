#include "../include/openGL_test.hpp"
#include <iostream>


int main()
{
   app first_openGL_test;
   try{
      first_openGL_test.run();
   }
   catch(std::runtime_error& ERROR){
      std::cout << ERROR.what() << std::endl;
   }
   return 0;
}
