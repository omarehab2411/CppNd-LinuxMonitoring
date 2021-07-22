#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"
#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;


// Done: Return the system's CPU
Processor& System::Cpu() 
{      
    return cpu_; 
}

// Done: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{
     vector<Process> Processes{};
     vector<int>IDs = LinuxParser:: Pids();
    for(int i : IDs )
    {   
        Process proc {i} ;
        Processes.push_back(proc);
    }

     LinuxParser::sortProcesses(Processes);
     processes_= Processes;
     return processes_;      
}

// Done: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Done: Return the system's memory utilization
float System::MemoryUtilization() { return (LinuxParser::MemoryUtilization() ); }

// Done: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Done: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses() ; }

// Done: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Done: Return the number of seconds since the system started running
long int System::UpTime() 
{ 
    return ( LinuxParser::UpTime() ); 
}