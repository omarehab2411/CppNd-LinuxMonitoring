#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include "process.h"
namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum  CPU_Info
{
USER = 0,
NICE,
SYSTEM,
IDLE,
IOWAIT,
IRQ,
SOFTIRQ,
STEAL,
GUEST,
NICEGUEST,
TotalStates
};


std::vector<std::string>CpuUtilization();
std::vector<float> CpuUtilization(int pid);
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();




std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
void sortProcesses (std::vector <Process>& processList);

// Processes
enum Process_Info
{
utime  = 14,
stime  =15,
cutime =16,
cstime =17,
starttime =22,
totalIndecies =23
};

};  // namespace LinuxParser

#endif