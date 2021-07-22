#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

#include <iostream>

Process::Process(int pid )
{
   processId = pid;
   CpuUtilization();
   Command();
   Ram();
   User();
   UpTime();
}
// TODO: Return this process's ID
int Process::Pid() { return processId; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization( ) 
{
 long uptime = LinuxParser::UpTime();
 vector<float> cpuVal = LinuxParser:: CpuUtilization( Pid() );
 float totalTime    = 0.0;
 float seconds      = 0.0;
 float cpuUtil      = 0.0;


if (cpuVal.size() == (Process::totalIndecies ) )
 {
    for (int i = 0; i < (Process::totalIndecies -1) ;i++)
 {
    totalTime +=cpuVal[i];
 }
 
  totalTime /=sysconf(_SC_CLK_TCK);
  seconds = uptime - ( cpuVal[Process::starttime] / sysconf(_SC_CLK_TCK) );
  cpuUtil = (totalTime/seconds ) ;
 }
  processUtil_ = cpuUtil;
 return processUtil_;
}

// TODO: Return the command that generated this process
string Process::Command() 
{  command_ =LinuxParser::Command(Pid());
   return  command_;
}

// TODO: Return this process's memory utilization
string Process::Ram()
 { 
     long ramMB =0;
     ram_= LinuxParser::Ram(Pid());
     try
     {
        /* code */
       ramMB = std::stol(ram_)/1000;
     }
     catch(const std::exception& e)
     {
        std::cerr << e.what() << '\n';
        ramMB =0;
     }
     ram_ = std::to_string(ramMB) ;
     return (ram_); 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{    user_  = LinuxParser::User(Pid()) ;
   return user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{  UpTime_ = LinuxParser::UpTime(Pid());
   return UpTime_ ; 
}

 