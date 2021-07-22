#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) ;

  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  static void sortProcesses (std::vector <Process>& processList);
  // TODO: Declare any necessary private members
 private:
 int  processId;
 float processUtil_;
 std::string command_;
 std::string ram_;
 long UpTime_;
 std::string user_;

 enum Process_TimeIndex
{
utime         = 0,
stime         = 1,
cutime        = 2,
cstime        = 3,
starttime     = 4,
totalIndecies = 5
};

};

#endif