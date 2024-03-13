#pragma once
#include <fstream>
#include <objbase.h>

#define PATHTOLOGFILE L"E:\\student\\learn\\3_course\\2_sem\\SP\\COMx64\\Debug\\sp02com.log"

static std::ofstream log_file;
static ULONG line = 0;

#define OPENLOGFILE log_file = std::ofstream(PATHTOLOGFILE)
#define OPENWITHAPPEND log_file = std::ofstream(PATHTOLOGFILE, std::ofstream::app)
#define ADDLINE ULONG __line=InterlockedIncrement(&line);
#define LOG(TEXT1, TEXT2) log_file<<__line<<"."<<(TEXT1)<<(TEXT2)<< "\n"
#define LOGFILECLOSE log_file.close()