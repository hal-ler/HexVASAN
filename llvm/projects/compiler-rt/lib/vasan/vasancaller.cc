#include "vasan.h"

#include "sanitizer_common/sanitizer_report_decorator.h"
#include "sanitizer_common/sanitizer_common.h"
#include "sanitizer_common/sanitizer_flags.h"
#include "sanitizer_common/sanitizer_libc.h"

#include <iostream> 
#include <fstream>
#include <cxxabi.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <csignal>
#include <signal.h>
#include <ucontext.h>
#include <list>
#include <stack>
#include <map>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>

bool destructor_register = false;
thread_local std::stack<callerside_info*> mystack;
thread_local std::map<int, int>callsite_cnt;
thread_local std::map<int, int>vfunc_cnt;


using namespace std;


extern "C" SANITIZER_INTERFACE_ATTRIBUTE


//__attribute__((destructor))
void destroy_vasancaller() {
  std::ofstream func_csite;
	
	//std::string pathname = "/home/priyam/up_llvm/data/runtime_csite" + getpid() + ".csv";
	char pathname[100];
	std::sprintf(pathname,"/home/priyam/up_llvm/yet_mozilla/runtime_csite%d.csv", getpid() ); 
	func_csite.open(pathname,std::ios_base::app | std::ios_base::out);

	for ( std::map<int, int>::const_iterator it = callsite_cnt.begin(); it != callsite_cnt.end(); it++) {
		
		func_csite << it->first << "\t" << it->second << "\n";   

	}
  func_csite.close();

	//===============================================================================

	std::ofstream func_va;
  char pathname_va[100];
	std::sprintf(pathname_va, "/home/priyam/up_llvm/yet_mozilla/runtime_vfunc%d.csv", getpid() ); 
	func_va.open(pathname_va, std::ios_base::app | std::ios_base::out);

	for ( std::map<int, int>::const_iterator it2 = vfunc_cnt.begin(); it2 != vfunc_cnt.end(); it2++) {
		
		func_va << it2->first << "\t" << it2->second << "\n";   

	}
  func_va.close();

}

extern "C" SANITIZER_INTERFACE_ATTRIBUTE

//CallerSide: Function to push the pointer in the stack
void info_push(callerside_info* x) {

	if(!destructor_register) {

		destructor_register = true;
		atexit(destroy_vasancaller);
		
	}
	callsite_cnt[x->id]++;

	mystack.push(x);
       // mprotect (memblock, 4096, PROT_READ);

	
}

extern "C" SANITIZER_INTERFACE_ATTRIBUTE

//CallerSide: Function to pop the pointer from the stack
void info_pop(int i) {
	if(!mystack.empty())
		mystack.pop();
	
}

