#ifndef __cplusplus
#include <stdio.h>
#else
#include <iostream>
#endif

#ifdef CLASSIC_TYPEDEF
typedef double Current;
typedef double Voltage;
typedef double Power;
#else
#if __cplusplus < 201103L
#error "requires C++11 language standard or better"
#endif
using Current = double;
using Voltage = double;
using Power = double;
#endif

int main() {
	Voltage u1 = 5.0;	// 5 Volt exactly
	Current i1 = 0.02;	// actually 20 mA
	Power p1 = u1*i1;
	#ifndef __cplusplus
	printf("%3.0f mW\n", p1*1000);
	#else
	std::cout << p1*1000 << " mW" << std::endl;
	#endif
	// but this compiles too ... :-(
	// Power p2 = u1 + i1;
	// NO strong typing that way (in C and C++ !!)
	
}
