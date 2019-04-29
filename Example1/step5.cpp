#if __cplusplus < 201402L
#error "requires C++14 language standard or better"
#endif

#include "pxtn.h"

PN_((Basic Tests for Voltage, Current, and Power Class))

enum class Unit { V, A, W };

template<enum Unit M, typename T>
class TS {
	T& downcasted() { return static_cast<T&>(*this); }
protected:
	double value;
	constexpr TS(double v) : value{v} {}
public:
	constexpr auto operator+() const	{ return T{+value}; }
	constexpr auto operator-() const 	{ return T{-value}; }
	constexpr auto& operator+=(TS rhs)	{ value += rhs.value; return downcasted(); }
	constexpr auto& operator-=(TS rhs)	{ value -= rhs.value; return downcasted(); }
	constexpr auto& operator*=(double rhs) 	{ value *= rhs; return downcasted(); }
	constexpr auto& operator/=(double rhs) 	{ value /= rhs; return downcasted(); }
};

class Voltage : public TS<Unit::V, Voltage> {
	friend class TS<Unit::V, Voltage>;
	using TS<Unit::V, Voltage>::TS;
public:

	static constexpr auto kV(double v)	{ return Voltage{v*1e3}; }
	static constexpr auto  V(double v)	{ return Voltage{v}; }
	static constexpr auto mV(double v)	{ return Voltage{v/1e3}; }
	static constexpr auto uV(double v)	{ return Voltage{v/1e6}; }

	constexpr auto get_kV() const 	{ return value/1e3; }
	constexpr auto get_V()  const	{ return value; }
	constexpr auto get_mV() const	{ return value*1e3; }
	constexpr auto get_uV() const	{ return value*1e6; }

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

class Current : public TS<Unit::A, Current> {
	using TS<Unit::A, Current>::TS;
public:
	static constexpr auto mA(double v)	{ return Current{v/1e3}; }
	constexpr auto get_A()  const		{ return value; }
};

constexpr inline auto operator"" _mA(unsigned long long v) { return Current::mA(double(v)); }
constexpr inline auto operator"" _mA(long double v)        { return Current::mA(v); }

class Power : public TS<Unit::W, Power> {
	using TS<Unit::W, Power>::TS;
public:
	constexpr static auto W(Voltage u, Current i)	{ return Power{u.get_V() * i.get_A()}; }
	constexpr static auto W(Current i, Voltage u)	{ return Power{u.get_V() * i.get_A()}; }
	constexpr auto get_mW()  const			{ return value*1e3; }
};

void voltage_static_constructors() {
PX_(	"4.8600"	, (	Voltage::V (4.86)	).get_V());
PX_(	"4860.0000"	, (	Voltage::kV(4.86)	).get_V());
PX_(	"0.0049"	, (	Voltage::mV(4.86)	).get_V());
}

void voltage_literal_unit_suffixes() {
PX_(	"4.8600"	, (	4.86_V		).get_V());
PX_(	"4860.0000"	, (	4.86_kV		).get_V());
PX_(	"0.0049"	, (	4.86_mV		).get_V());
}

void voltage_by_unit_getters() {
	auto v = 4.86_V;
PX_(	"4.8600"	, v.get_V()	);
PX_(	"4860.0000"	, v.get_mV()	);
PX_(	"0.0049"	, v.get_kV()	);
}

void voltage_unary_plus_minus() {
PX_(	"4.8600"	, (	+4.86_V		).get_V());
PX_(	"-4.8600"	, (	-4.86_V		).get_V());
PX_(	"4.8600"	, (	-(-4.86_V)	).get_V());
}

void voltage_assigning_plus_minus() {
	auto v = 4_V;
PX_(	"4.0000"	, (	v		).get_V());
PX_(	"4.8600"	, (	v += 860_mV	).get_V());
PX_(	"4.8600"	, (	v          	).get_V());
PX_(	"0.8600"	, (	v -= 4_V       	).get_V());
PX_(	"0.8600"	, (	v		).get_V());
}

void voltage_binary_plus_minus() {
PX_(	"4.8600"	, (	4_V + 860_mV	).get_V());
PX_(	"4.0000"	, (	4.86_V - 860_mV	).get_V());
}

void voltage_assigning_multiply_divide() {
	auto v = 4_V;
PX_(	"5.0000"	, (	v *= 1.25	).get_V());
PX_(	"5.0000"	, (	v        	).get_V());
PX_(	"2.5000"	, (	v /= 2		).get_V());
}

void voltage_binary_multiply_divide() {
PX_(	"5.0000"	, (	4_V * 1.25	).get_V());
PX_(	"2.5000"	, (	5_V / 2		).get_V());
}

void misc_others_playground() {
PX_(	"0.0200"	, (20_mA).get_A());
//	Voltage v = 20_mA;
PX_(	"97.2000"	, Power::W(4.86_V, 20_mA).get_mW());
PX_(	"97.2000"	, Power::W(20_mA, 4.86_V).get_mW());
}

int main() {
	std::cout.setf(std::ios::boolalpha);
	std::cout.setf(std::ios::fixed);
	std::cout.precision(4);

	voltage_static_constructors();
	voltage_literal_unit_suffixes();
	voltage_by_unit_getters();
	voltage_unary_plus_minus();
	voltage_assigning_plus_minus();
	voltage_binary_plus_minus();
	voltage_assigning_multiply_divide();
	voltage_binary_multiply_divide();
}
