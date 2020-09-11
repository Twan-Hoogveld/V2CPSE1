#include "hwlib.hpp"
extern "C" void print_asciz(const char * s);

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void application();

extern "C" char convert(const char char_to_convert){
   char return_char = char_to_convert;
   if(char_to_convert >= 'A' && char_to_convert <= 'Z'){
      return_char = char_to_convert + 32;
   }
   else if(char_to_convert >= 'a' && char_to_convert <= 'z'){
      return_char = char_to_convert - 32; 
   }
   return return_char;
}

int main( void ){	
   
   namespace target = hwlib::target;   
    
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}