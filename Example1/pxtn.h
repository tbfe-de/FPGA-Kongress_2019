#ifndef PXT_H
#define PXT_H

#include <iostream>
#include <sstream>

#define PX(...)\
	((void)(std::cout << "::: " << __FUNCTION__\
			  << '[' << __LINE__ << ']'\
                          << "\t" #__VA_ARGS__ " --> " << (__VA_ARGS__)\
			  << std::endl))

#define PX_(expect, ...)\
	do {\
		std::ostringstream result;\
		result.flags(std::cout.flags());\
		result.precision(std::cout.precision());\
		result << (__VA_ARGS__);\
		++PN_test.done;\
		if (result.str() == expect) break;\
		std::cout << "::: " << __FUNCTION__ << '[' << __LINE__ << ']'\
                          << "\t" #__VA_ARGS__ " --> " << result.str()\
			  << "\t!= " << expect << std::endl;\
		++PN_test.fail;\
	} while (false)

#if __has_include("boost/typeindex.hpp")
#include "boost/type_index.hpp"

#define PT(...)\
	((void)(std::cout << "::: " << __FUNCTION__\
			  << '[' << __LINE__ << ']'\
                          << "\t" #__VA_ARGS__ " --> "\
			  << boost::typeindex::type_id_with_cvr<__VA_ARGS__>()\
			  << std::endl))

#define PT_(expect, ...)\
	do {\
		std::ostringstream result;\
		result.flags(std::cout.flags());\
		result.precision(std::cout.precision());\
		result << boost::typeindex::type_id_with_cvr<__VA_ARGS__>();\
		++PN_test.done;\
		if (result.str() == expect) break;\
		std::cout << "::: " << __FUNCTION__ << '[' << __LINE__ << ']'\
                          << "\t" #__VA_ARGS__ " --> " << result.str()\
			  << "\t!= " << expect << std::endl;\
		++PN_test.fail;\
	} while (false)

#endif

#define PN_(testname)\
	struct PN_ {\
		PN_(const char* fn) {\
			std::cout << "... " #testname;\
			if (fn[0]) std::cout << "(" << fn << ")";\
			std::cout << std::endl;\
		}\
		~PN_() {\
			std::cout << "=== " << __FILE__ << ": "\
				  << done << " tests ";\
			if (fail) std::cout << ", " << fail\
                                            << " FAILED";\
			else      std::cout << "passed (OK)";\
			std::cout << std::endl;\
		}\
		int done{}, fail{};\
	} PN_test(__FUNCTION__);\

#endif
