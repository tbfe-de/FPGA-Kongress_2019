class Voltage {
	double value;
	explicit Voltage(double v) : value{v} {}
public:
	auto kV() const 		{ return value/1e3; }
	auto V()  const			{ return value; }
	auto mV() const			{ return value*1e3; }
	static auto kV(double v)	{ return Voltage{v*1e3}; }
	static auto  V(double v)	{ return Voltage{v}; }
	static auto mV(double v)	{ return Voltage{v/1e3}; }
	auto& operator+=(Voltage rhs) 	{ value += rhs.value;
					  return *this; }
};
auto operator"" _kV(long double v) { return Voltage::kV(v); }
auto operator""  _V(long double v) { return Voltage::V(v); }
auto operator"" _mV(long double v) { return Voltage::mV(v); }

int main() {
	Voltage vcc = 5.0_V;
	auto v{vcc.mV()};
}
