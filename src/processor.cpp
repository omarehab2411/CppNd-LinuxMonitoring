#include "processor.h"
#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;



// Done: Return the aggregate CPU utilization
float Processor::Utilization()
 {
  vector<string> CPU_info ;
  vector<long> lCPU_info;
  float totalTime,idleTime,utilTime,temp;
  string stemp;
  CPU_info = LinuxParser::CpuUtilization();
  for(string i : CPU_info)
  {
    try
    {
      /* code */
      temp = std::stol(i);
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
     temp = 0;
    }
     
    lCPU_info.push_back(temp);
  }


  
  utilTime  =   lCPU_info[LinuxParser::USER]+ lCPU_info[LinuxParser::NICE]+ lCPU_info[LinuxParser::SYSTEM]
               +lCPU_info[LinuxParser::IRQ]+lCPU_info[LinuxParser::SOFTIRQ]
               +lCPU_info[LinuxParser::GUEST]+lCPU_info[LinuxParser::NICEGUEST];
  
  idleTime  =  lCPU_info[LinuxParser::IDLE]+lCPU_info[LinuxParser::IOWAIT]+lCPU_info[LinuxParser::STEAL];
  totalTime =  utilTime+idleTime;
  TotalUtilization = utilTime/totalTime;
  return (TotalUtilization); 
}