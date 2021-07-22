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


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(),'=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  string line;
  string key;
  string value;
  float freeMem     = 0.0; 
  float memT        = 0.0;
  float utilizedMem = 0.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          memT = (float)std::stof(value);
        }else if(key == "MemFree")
        {
          freeMem =  (float)std::stof(value);
          break;
        }
      }
    }
  }
    utilizedMem = ((memT - freeMem)/memT) ;
    return utilizedMem;
}

// Done: Read and return the system uptime
long LinuxParser::UpTime() 
{  
  string line;
  string sUpTime;
  string sIdleTime;
  long  upTime = 0; 
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line))
     {
      std::istringstream linestream(line);
      while(linestream >> sUpTime >>sIdleTime) 
      {
       try
       {
         upTime = std::stol(sUpTime);
       }
       catch(const std::exception& e)
       {
         std::cerr << e.what() << '\n';
         upTime = 0.0;
       }
        
      } 
    }
  }
    return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { pid =0; 
  return pid; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
std::vector<std::string>LinuxParser::CpuUtilization() 
{ 
  string line;
  string key; 
  string value;
  vector<string> CPU_info ;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line))
     {
      std::istringstream linestream(line);
      while(linestream >> key) 
      {
        if( key == "cpu")
        {
          for( int i=0 ;i < TotalStates ;i++)
          {
           linestream>>value;
          CPU_info.push_back(value);    
          }
          
        }
      } 
    }
  }
  return CPU_info;
}

std::vector<float>LinuxParser:: CpuUtilization(int pid)
{
  string line;
  string value;
  vector<float> cpuVal;

  std::ifstream filestream(LinuxParser::kProcDirectory+"/"+std::to_string(pid)+"/" + LinuxParser::kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line))
     {
      std::istringstream linestream(line);
         
        for (int i = 1; i < LinuxParser::totalIndecies ; i++) 
      {
        linestream >> value;
        if( (i>=utime && i<=cstime) || (i == starttime) )
        {
          cpuVal.push_back (std::stof(value));
        }
      }  
     }
   }
  return cpuVal;
}
// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses()
 {
  string line;
  string processes;
  string processesNumber;
  int  procNum = 0; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line))
     {
      std::istringstream linestream(line);
      while(linestream >> processes >>processesNumber) 
      {
        if( processes == "processes")
        {
          procNum = std::stoi(processesNumber);
        }
      } 
    }
  }
    return procNum;
   
 }
 


// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{string line;
  string processes;
  string processesNumber;
  int  procNum = 0; 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line))
     {
      std::istringstream linestream(line);
      while(linestream >> processes >>processesNumber) 
      {
        if( processes == "procs_running")
        {
          procNum = std::stoi(processesNumber);
        }
      } 
    }
  }
    return procNum;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string line;
  string value;
  std::ifstream filestream(kProcDirectory+"/"+std::to_string(pid)+"/" + kCmdlineFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      linestream >> value;
    }
  }
      return value;   
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid)
 { string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+"/"+std::to_string(pid)+"/" + kStatusFilename);
  if (filestream.is_open())
   {
    while (std::getline(filestream, line)) 
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while(linestream >> key )
      {
      if(key == "VmSize")
      {
        linestream >> value;
      }
      }
    }
  }
      return value; 
 
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{ 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory+"/"+std::to_string(pid)+"/" + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "Uid") {
          linestream >> value;
          
        }
      }
    }
  } 
      return value;
}


// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  string uid = LinuxParser::Uid(pid);
  string line;
  string key;
  string value;
  string garbage;
  string usr;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> value >> garbage >> key) {
        if (key == uid) {
         
          usr = value;
        }
      }
    }
  }
  return usr;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{
  string line;
  long uptime = 0;
  string value;
  const int index_ = 22;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      for (int i = 0; i < (index_) ; i++)
       {
         linestream >> value;
        if (i == (index_ - 1) )  
        {
             
           try
           {
             uptime = std::stol(value) / sysconf(_SC_CLK_TCK);
           }
           catch(const std::exception& e)
           {
             std::cerr << e.what() << '\n';
             uptime =0;
           }
            
        }
      }
    }
  }
  return uptime;
 }


void LinuxParser::sortProcesses (std::vector<Process>& processList)
{
    for (unsigned int i=0;i<processList.size()-1;i++)
    {
        for(unsigned int j=i+1;j<processList.size();j++)
        {
            if(processList[j].CpuUtilization( )> processList[i].CpuUtilization())
            {
                Process temp = processList[j];
                processList[j]=processList[i];
                processList[i]=temp;
            }
        }
        
    }

}