#if __cplusplus < 201402L
#error "requires C++14 language standard or better"
#endif

#include <iostream>

class Voltage {
	double value;
	explicit Voltage(double v) : value{v} {}
public:
//	static auto mV(double v) { return Voltage{v/1e3}; }
	static auto  V(double v) { return Voltage{v};     }
//	static auto kV(double v) { return Voltage{v*1e3}; }
//	auto get_mV() const { return value*1e3; }
	auto get_V()  const { return value; }
//	auto get_kV() const { return value/1e3; }
};

// auto operator"" _mV(unsigned long long v) { return Voltage::mV(double(v)); }
// auto operator"" _mV(long double v)        { return Voltage::mV(v); }
// auto operator""  _V(unsigned long long v) { return Voltage:: V(double(v)); }
   auto operator""  _V(long double v)        { return Voltage:: V(v); }
// auto operator"" _kV(unsigned long long v) { return Voltage::kV(double(v)); }
// auto operator"" _kV(long double v)        { return Voltage::kV(v); }

class Current {
	double value;
	explicit Current(double v) : value(v) {}
public:
	static auto mA(double v) { return Current{v/1e3}; }
//	static auto  A(double v) { return Current{v;} }
//	static auto kV(double v) { return Current{v*1e3}; }
//	auto get_mA() const { return value*1e3; }
  	auto get_A()  const { return value; }
//	auto get_kA() const { return value/1e3; }
};

   auto operator"" _mA(unsigned long long v) { return Current::mA(double(v)); }
// auto operator"" _mA(long double v)        { return Current::mA(v); }
// auto operator""  _A(unsigned long long v) { return Current:: A(double(v)); }
// auto operator""  _A(long double v)        { return Current:: A(v}; }
// auto operator"" _kA(unsigned long long v) { return Current::kA(double(v)); }
// auto operator"" _kA(long double v)        { return Current::kA(v); }

class Power {
	double value;
	explicit Power(double v) : value(v) {}
public:
	Power(Voltage voltage, Current current)
		: value(voltage.get_V() * current.get_A())
	{}
	auto get_mW() const { return value; }
//	auto get_W()  const { return value; }
//  	auto get_kW() const { return value; }
};

   auto operator*(Voltage lhs, Current rhs) { return Power(lhs, rhs); }
// auto operator*(Current lhs, Voltage rhs) { return Power(rhs, lhs); }

int main() {
//	Voltage u1 = Voltage::V{5.0};
	Voltage u1 = 5.0_V;
//	Voltage u1 = 5_V;
//	auto u1 = 5_V;

//	Current i1 = Current::mA{20};
	Current i1 = 20_mA;
//	auto i1 = 20_mA;

//	Power p1{u1, i1};
//	Power p1 = u1 * i1;
	Power p1{u1 * i1};
//	auto p1 = Power{u1 * i1}
//	auto p1 = i1 * u1;

	std::cout << p1.get_mW() << " mW" << std::endl;
}
