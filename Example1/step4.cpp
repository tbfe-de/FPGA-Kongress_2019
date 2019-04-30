#include "pxtn.h"

PN_(Basic Tests for `class` Voltage)

class Voltage {
	double value;
	explicit constexpr Voltage(double v) : value{v} {}
public:
	static constexpr auto kV(double v)	{ return Voltage{v*1e3}; }
	static constexpr auto  V(double v)	{ return Voltage{v}; }
	static constexpr auto mV(double v)	{ return Voltage{v/1e3}; }
	static constexpr auto uV(double v)	{ return Voltage{v/1e6}; }

	constexpr auto get_kV() const 		{ return value/1e3; }
	constexpr auto get_V()  const		{ return value; }
	constexpr auto get_mV() const		{ return value*1e3; }
	constexpr auto get_uV() const		{ return value*1e6; }

	constexpr auto operator+() const	{ return Voltage{+value}; }
	constexpr auto operator-() const 	{ return Voltage{-value}; }
	constexpr auto& operator+=(Voltage rhs)	{ value += rhs.value; return *this; }
	constexpr auto& operator-=(Voltage rhs)	{ value -= rhs.value; return *this; }
	constexpr auto& operator*=(double rhs) 	{ value *= rhs; return *this; }
	constexpr auto& operator/=(double rhs) 	{ value /= rhs; return *this; }
};

constexpr inline auto operator"" _kV(unsigned long long v) { return Voltage::kV(double(v)); }
constexpr inline auto operator"" _kV(long double v)        { return Voltage::kV(v); }
constexpr inline auto operator""  _V(unsigned long long v) { return Voltage:: V(double(v)); }
constexpr inline auto operator""  _V(long double v)        { return Voltage:: V(v); }
constexpr inline auto operator"" _mV(unsigned long long v) { return Voltage::mV(double(v)); }
constexpr inline auto operator"" _mV(long double v)        { return Voltage::mV(v); }
constexpr inline auto operator"" _uV(unsigned long long v) { return Voltage::uV(double(v)); }
constexpr inline auto operator"" _uV(long double v)        { return Voltage::uV(v); }

constexpr inline auto operator+(Voltage lhs, Voltage rhs) { return lhs += rhs; }
constexpr inline auto operator-(Voltage lhs, Voltage rhs) { return lhs -= rhs; }

constexpr inline auto operator*(Voltage lhs, double rhs) { return lhs *= rhs; }
constexpr inline auto operator*(double lhs, Voltage rhs) { return lhs *= lhs; }
constexpr inline auto operator/(Voltage lhs, double rhs) { return lhs /= rhs; }
constexpr inline auto operator/(double lhs, Voltage rhs) { return rhs /= lhs; }

int main() {

	std::cout.setf(std::ios::boolalpha);
	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);

				auto v = 4.86_V;
//	======== EXPECT		========================== TEST
PX_(	"4.86"		,	v.get_V()			);
PX_(	"4860.00"	,	v.get_mV()			);
PX_(	"0.00"		,	v.get_kV()			);
PX_(	"4860000.00"	,	v.get_uV()			);
//	---------------		-------------------------------
PX_(	"1.23"		, (	1.23_uV		).get_uV()	);
PX_(	"12345.00"	, (	12345_uV	).get_uV()	);
PX_(	"1.23"		, (	1.2345_mV	).get_mV()	);
PX_(	"12345.00"	, (	12345_mV	).get_mV()	);
PX_(	"1.23"		, (	1.23_V		).get_V()	);
PX_(	"12345.00"	, (	12345_V		).get_V()	);
PX_(	"1.23"		, (	1.23_kV		).get_kV()	);
PX_(	"12345.00"	, (	12345_kV	).get_kV()	);
//	---------------		-------------------------------
PX_(	"4.86"		, (	+v		).get_V()	);
PX_(	"-4.86"		, (	-v		).get_V()	);
//	---------------		-------------------------------
PX_(	"5.86"		, (	v += 1_V	).get_V()	);
PX_(	"5.00"		, (	v -= 860_mV	).get_V()	);
PX_(	"15.00"		, (	v *= 3 		).get_V()	);
PX_(	"3.00"		, (	v /= 5 		).get_V()	);
//	---------------		-------------------------------
PX_(	"4.00"		, (	v + 1_V		).get_V()	);
PX_(	"2.14"		, (	v - 860_mV	).get_V()	);
PX_(	"9.00"		, (	v * 3 		).get_V()	);
PX_(	"0.60"		, (	v / 5 		).get_V()	);
}
