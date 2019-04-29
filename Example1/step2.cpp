#include <iostream>

class Voltage {
	double value;
public:
	Voltage(double v) : value(v) {}
	double get() const { return value; }
};

class Current {
	double value;
public:
	Current(double v) : value(v) {}
	double get() const { return value; }
};

class Power {
	double value;
public:
	Power(double v) : value(v) {}
	double get() const { return value; }
};

int main() {
#if __cplusplus >= 201103L
	Voltage u1{5.0};
	Current i1{0.02};
	Power p1{u1.get() * i1.get()};
#else
	Voltage u1 = 5.0;
	Current i1 = 0.02;
	Power p1 = u1.get() * i1.get();
#endif
	std::cout << p1.get() << " mW" << std::endl;
	// this does NOT compile:
	// u1 = i1;
	// only this DOES compile:
	u1 = static_cast<Voltage>(i1.get());
	u1 = (Voltage)i1.get();
	u1 = Voltage(i1.get());
#if __cplusplus >= 201103L
	u1 = Voltage{i1.get()};
#endif
}
