#include <string>

#include "format.h"

using std::string;

// Done: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)
{ 
    long hour,min,sec;
    string sh,sm,ss;
    string format ;
     hour     = seconds / 3600;
     seconds  = seconds %3600;
     min      = seconds /60;
     seconds  = seconds % 60;
     sec      = seconds;

    if(hour < 10)
     sh = "0"+std::to_string(hour);
     else 
     sh = std::to_string(hour);

     if(min < 10)
     sm = "0"+std::to_string(min);
     else 
     sm = std::to_string(min);


     if(sec < 10)
     ss = "0"+std::to_string(sec);
     else 
     ss = std::to_string(sec);

 format = sh + ":" + sm +":" +ss;
 return format;
  
}