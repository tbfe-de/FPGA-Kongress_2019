#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

typedef struct { double value; } Voltage;
typedef struct { double value; } Current;
typedef struct { double value; } Power;

int main() {
	Voltage u1 = { 5.0 };	// 5 Volt exactly
	Current i1 = { 0.02 };	// actually 20 mA
	Power p1 = { u1.value * i1.value };
	#ifndef __cplusplus
	printf("%3.0f mW\n", p1.value*1000);
	#else
	std::cout << p1.value*1000 << " mW" << std::endl;
	#endif
	// this does NOT compile:
	// i1 = u1;
	// BUT this DOES compile:
	// i1.value = u1.value;
}
