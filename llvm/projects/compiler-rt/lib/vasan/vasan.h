#include <iostream> 
#include <cxxabi.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <csignal>
#include <signal.h>
#include <ucontext.h>
#include <list>
#include <stack>

struct callerside_info {
	uint64_t id;
	uint32_t arg_count;
	uint64_t*  arg_array;
	
};
/*
struct callsite_info {
	uint64_t func_id,
	bool direct;
	std::string func_name;
	std::string func_type;
	uint32_t line_no,
	uint32_t column_no,
	std::string file_name;
	uint32_t arg_count;
	uint64_t*  arg_array;	

};*/

