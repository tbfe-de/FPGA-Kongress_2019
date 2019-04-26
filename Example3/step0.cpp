/*
 ==================================================================================================
 PoC Implememtation Calculating Sine Values via Data Points In a Table And Linear Interpolation
 ==================================================================================================
 Primary goals:
 - verify idea, algorithms are right, and test code
 - check whether it actually speed up calculations
 - better understand deviation from exact values
 TODO-s when turned into production code:
 - combine globals into class 
 - add more assertions and comments
*/
#if __cplusplus < 201402L
#error "C++14 language standard required at least"
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <random>
#include <utility>

#if TESTCASE == 1
constexpr std::size_t N = 19;
constexpr int mindeg = 0;
constexpr int maxdeg = 90;
#elif TESTCASE == 2
constexpr std::size_t N = 4;
constexpr int mindeg = 0;
constexpr int maxdeg = 45;
#elif TESTCASE == 3
constexpr std::size_t N = 11;
constexpr int mindeg = 45;
constexpr int maxdeg = 55;
#else
#error "TESTCASE must be defined as 1, 2, or 3"
#endif

std::array<double, N> lookup;

constexpr double PI = 2*std::acos(0.0);
constexpr inline double deg2rad(int deg) {
	return (2*PI*deg) / 360;
}

double quicksine(int deg) {
	using namespace std::string_literals;
	if (deg < mindeg) throw "out of range value (low): "s + std::to_string(deg);
	if (deg > maxdeg) throw "out of range value (high): "s + std::to_string(deg);

	const auto offset = deg - mindeg;
	const auto step = (maxdeg - mindeg) / (N - 1);
	const auto qr = std::div(offset, step);
	assert(qr.quot < lookup.size());
	assert(qr.rem < step);

	if (qr.rem == 0)
		return lookup[qr.quot];

	const auto lo_idx = qr.quot;
	const auto hi_idx = qr.quot + 1;
	assert(0 <= lo_idx);
	assert(lo_idx < N-1);
	assert(0+1 <= hi_idx);
	assert(hi_idx < N);

	const auto lower = lookup.at(lo_idx);
	const auto upper = lookup.at(hi_idx);
	const auto delta = upper - lower;
	return lower + (delta * qr.rem) / step;
}

void fill_table() {
	const auto step = (maxdeg-mindeg) / (N-1);
	auto deg = mindeg;
	for (std::size_t i = 0; i < N-1; ++i, deg += step)
		lookup.at(i) = std::sin(deg2rad(deg));
	lookup.at(N-1) = std::sin(deg2rad(maxdeg));
}

void test_table() {
#if TESTCASE == 1
	assert(lookup.at(0)  == std::sin(deg2rad(0)));
	assert(lookup.at(1)  == std::sin(deg2rad(5)));
	assert(lookup.at(2)  == std::sin(deg2rad(10)));
	assert(lookup.at(3)  == std::sin(deg2rad(15)));
	assert(lookup.at(4)  == std::sin(deg2rad(20)));
	assert(lookup.at(5)  == std::sin(deg2rad(25)));
	assert(lookup.at(6)  == std::sin(deg2rad(30)));
	assert(lookup.at(7)  == std::sin(deg2rad(35)));
	assert(lookup.at(8)  == std::sin(deg2rad(40)));
	assert(lookup.at(9)  == std::sin(deg2rad(45)));
	assert(lookup.at(10) == std::sin(deg2rad(50)));
	assert(lookup.at(11) == std::sin(deg2rad(55)));
	assert(lookup.at(12) == std::sin(deg2rad(60)));
	assert(lookup.at(13) == std::sin(deg2rad(65)));
	assert(lookup.at(14) == std::sin(deg2rad(70)));
	assert(lookup.at(15) == std::sin(deg2rad(75)));
	assert(lookup.at(16) == std::sin(deg2rad(80)));
	assert(lookup.at(17) == std::sin(deg2rad(85)));
	assert(lookup.at(18) == std::sin(deg2rad(90)));
#endif
#if TESTCASE == 2
	assert(lookup.at(0)  == std::sin(deg2rad(0)));
	assert(lookup.at(1)  == std::sin(deg2rad(15)));
	assert(lookup.at(2)  == std::sin(deg2rad(30)));
	assert(lookup.at(3)  == std::sin(deg2rad(45)));
#endif
#if TESTCASE == 3
	assert(lookup.at(0)  == std::sin(deg2rad(45)));
	assert(lookup.at(1)  == std::sin(deg2rad(46)));
	assert(lookup.at(2)  == std::sin(deg2rad(47)));
	assert(lookup.at(3)  == std::sin(deg2rad(48)));
	assert(lookup.at(4)  == std::sin(deg2rad(49)));
	assert(lookup.at(5)  == std::sin(deg2rad(50)));
	assert(lookup.at(6)  == std::sin(deg2rad(51)));
	assert(lookup.at(7)  == std::sin(deg2rad(52)));
	assert(lookup.at(8)  == std::sin(deg2rad(53)));
	assert(lookup.at(9)  == std::sin(deg2rad(54)));
	assert(lookup.at(10) == std::sin(deg2rad(55)));
#endif
}

void test_quicksine() {
#if TESTCASE == 1
	assert(quicksine(0)  == std::sin(deg2rad(0)));
	assert(quicksine(5)  == std::sin(deg2rad(5)));
	assert(quicksine(10) == std::sin(deg2rad(10)));
	assert(quicksine(15) == std::sin(deg2rad(15)));
	assert(quicksine(20) == std::sin(deg2rad(20)));
	assert(quicksine(25) == std::sin(deg2rad(25)));
	assert(quicksine(30) == std::sin(deg2rad(30)));
	assert(quicksine(35) == std::sin(deg2rad(35)));
	assert(quicksine(40) == std::sin(deg2rad(40)));
	assert(quicksine(45) == std::sin(deg2rad(45)));
	assert(quicksine(50) == std::sin(deg2rad(50)));
	assert(quicksine(55) == std::sin(deg2rad(55)));
	assert(quicksine(60) == std::sin(deg2rad(60)));
	assert(quicksine(65) == std::sin(deg2rad(65)));
	assert(quicksine(70) == std::sin(deg2rad(70)));
	assert(quicksine(75) == std::sin(deg2rad(75)));
	assert(quicksine(80) == std::sin(deg2rad(80)));
	assert(quicksine(85) == std::sin(deg2rad(85)));
	assert(quicksine(90) == std::sin(deg2rad(90)));

#endif
#if TESTCASE == 2
	assert(quicksine(0)  == std::sin(deg2rad(0)));
	assert(quicksine(15) == std::sin(deg2rad(15)));
	assert(quicksine(30) == std::sin(deg2rad(30)));
	assert(quicksine(45) == std::sin(deg2rad(45)));

	assert(std::sin(deg2rad(0)) < quicksine(10)); 
	assert(quicksine(10) < std::sin(deg2rad(15)));
	assert(std::sin(deg2rad(30)) < quicksine(44)); 
	assert(quicksine(44) < std::sin(deg2rad(45)));

#endif
#if TESTCASE == 3
	assert(quicksine(45) == std::sin(deg2rad(45)));
	assert(quicksine(46) == std::sin(deg2rad(46)));
	assert(quicksine(47) == std::sin(deg2rad(47)));
	assert(quicksine(48) == std::sin(deg2rad(48)));
	assert(quicksine(49) == std::sin(deg2rad(49)));
	assert(quicksine(50) == std::sin(deg2rad(50)));
	assert(quicksine(51) == std::sin(deg2rad(51)));
	assert(quicksine(52) == std::sin(deg2rad(52)));
	assert(quicksine(53) == std::sin(deg2rad(53)));
	assert(quicksine(54) == std::sin(deg2rad(54)));
	assert(quicksine(55) == std::sin(deg2rad(55)));
#endif

	try { (void)quicksine(mindeg-1); assert(!"should throw for too low"); }
	catch (const std::string&) {     assert( "did throw for too low"); }  
	try { (void)quicksine(maxdeg+1); assert(!"should throw for too high"); }
	catch (const std::string&) {	 assert( "did throw for too high"); }
}

template<typename Code>
void measure_performance(const char* text, Code test, int runs = 1'000'000) {
	std::mt19937 gen;
        std::uniform_int_distribution<> dis(mindeg, maxdeg);
	static volatile double result;

	namespace sc = std::chrono;
	const auto start_time = sc::steady_clock::now();
	for (int i = 0; i < runs; ++i) {
		result = test(dis(gen));
	}
	const auto end_time = sc::steady_clock::now();
	using float_us = sc::duration<float, std::ratio<1, 1'000'000>>;
	const auto fus = sc::duration_cast<float_us>(end_time - start_time);
	std::cout << text << ": "
		  << fus.count() << " usec for " << runs << " calls\n"
		  << std::setw(std::strlen(text) + 2) << "= "
		  << fus.count()/runs << " usec per call" << std::endl;
}

#include <map>

void measure_deviation(int runs) {
	std::mt19937 gen;
        std::uniform_int_distribution<> dis(mindeg, maxdeg);

	std::map<float, int> accuracy = {
		{.0, 0}, {.01, 0}, {.02, 0}, {.05, 0}, {.10, 0},
		{.25, 0}, {.50, 0}, {1.0, 0}, {2.0, 0}, {1e5, 0}
	};
	std::cout << "deviation: " << runs << " random data points\n";
	for (int i = 0; i < runs; ++i) {
		const auto deg = dis(gen);
		const auto rad = deg2rad(deg);
		const auto result = quicksine(deg);
		const auto sin_rad = std::sin(rad);
		const auto diff = std::abs(result - sin_rad);
		const auto rel_diff = sin_rad ? std::abs(diff / sin_rad) : 0.0;
		const auto percentage = 100*rel_diff;
		if (runs <= 10) {
			std::cout << "deg="	<< deg		<< ", "
				  << "rad="	<< rad		<< ", "
				  << "sin="	<< result	<< ", "
				  << "diff="	<< diff		<< ", "
				  << "rel="	<< rel_diff	<< ", "
				  << "percent=" << percentage	<< std::endl;
		}
		for (auto &e : accuracy) {
			const bool is_last = (e.first == std::prev(accuracy.cend())->first);
			if ((percentage <= e.first) || is_last) {
				++e.second;
				break;
			}
		}
	}
	assert(accuracy.size() >= 2);
	const auto exact = accuracy.cbegin()->second;
	std::cout << std::setw(8) << exact
		  << " = exact results (" << 100.0*exact/runs << "%)\n";
	std::for_each(std::next(accuracy.cbegin()),
		      std::prev(accuracy.cend()),
			[runs](const auto& e) {
				std::cout << std::setw(8) << e.second
					  << " = within " << e.first << " percent"
			  		  << " (" << 100.0*e.second/runs << "%)\n";
			});
	const auto worse = std::prev(accuracy.cend())->second;
	std::cout << std::setw(8) << worse
		  << " = worse results (" << 100.0*worse/runs << "%)" << std::endl;
}

int main() {
	std::cout << __FILE__
		  << "\n****************"
		  <<	  " TESTCASE "
		  <<        TESTCASE
		  << " ****************\n"
		  << "" << mindeg << " to " << maxdeg << " degree"
                  << " lookup-table with " << N << " entries\n"
		  << "--------------------------------------------"
		  << std::endl;
	fill_table();
	test_table();
	test_quicksine();
	measure_performance("quicksine", [](auto arg) { return quicksine(arg); });
	measure_performance("std::sin ", [](auto arg) { return std::sin(arg); });
	measure_deviation(2'000);
}
