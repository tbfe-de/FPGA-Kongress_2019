#include <cassert>
#include <cstddef>
#include <type_traits>

template<typename Payload, std::size_t Size, template<typename> class BCP>
class RingBuffer : public BCP<RingBuffer<Payload, Size, BCP>> {
	using BC_Policy = BCP<RingBuffer<Payload, Size, BCP>>; 
	Payload data[Size+1];
	size_t iput = 0, iget = 0;
	static std::size_t wrap(std::size_t idx) {
		return idx % (Size+1);
	}
	using BC_Policy::full_handled;
	using BC_Policy::empty_handled;
protected:
	using Payload_in = std::conditional_t<
		 std::is_same<Payload, bool>{} ||
		(std::is_arithmetic<Payload>{} && (sizeof(Payload) <= 4))
	, Payload, const Payload&>;
	using Payload_out = Payload&;
public:
	using payload_type = Payload;
	bool empty() const;
	bool full() const;
	std::size_t size() const;
	bool put(Payload_in);
	bool get(Payload_out);
	Payload peek(std::size_t = 0) const;
};

template<typename Payload, std::size_t Size, template<typename> class BCP>
inline
bool RingBuffer<Payload, Size, BCP>::empty() const {
	return (iput == iget);
}

template<typename Payload, std::size_t Size, template<typename> class BCP>
inline
bool RingBuffer<Payload, Size, BCP>::full() const {
	return (wrap(iput+1) == iget);
}

template<typename Payload, std::size_t Size, template<typename> class BCP>
inline
std::size_t RingBuffer<Payload, Size, BCP>::size() const {
	return (iput >= iget)
		? iput - iget
		: iput + (Size+1) - iget;
}

template<typename Payload, std::size_t Size, template<typename> class BCP>
//inline
bool RingBuffer<Payload, Size, BCP>::put(Payload_in e) {
	if (full() && !full_handled())
		return false;
	assert(!full());
	data[iput] = e;
	iput = wrap(iput+1);
	return true;
}

template<typename Payload, std::size_t Size, template<typename> class BCP>
//inline
bool RingBuffer<Payload, Size, BCP>::get(Payload_out e) {
	if (empty() && !empty_handled())
		return false;
	assert(!empty());
	e = data[iget];
	iget = wrap(iget+1);
	return true;
}

template<typename Payload, std::size_t Size, template<typename> class BCP>
Payload RingBuffer<Payload, Size, BCP>::peek(std::size_t offset) const {
	assert(offset < size());
	return data[wrap(iget + offset)];
}

template<typename RingBufferImplementation>
class EasyBorderCaseHandler {
	auto& underlying_buffer() {
		return static_cast<RingBufferImplementation&>(*this);
	}
protected:
	bool empty_handled();
	bool full_handled();
};

template<typename RingBufferImplementation>
//inline
bool EasyBorderCaseHandler<RingBufferImplementation>::empty_handled() {
	typename RingBufferImplementation::payload_type filler{};
	(void) underlying_buffer().put(filler);
	return true;
}

template<typename RingBufferImplementation>
//inline
bool EasyBorderCaseHandler<RingBufferImplementation>::full_handled() {
	typename RingBufferImplementation::payload_type discard;
	(void) underlying_buffer().get(discard);
	return true;
}

template<typename Payload, std::size_t Size>
using EasyRingBuffer = RingBuffer<Payload, Size, EasyBorderCaseHandler>;

template<typename RingBufferImplementation>
class SafeBorderCaseHandler {
protected:
	bool empty_handled() {
		return false;
	}
	bool full_handled() {
		return false;
	}
};

template<typename Payload, std::size_t Size>
using SafeRingBuffer = RingBuffer<Payload, Size, SafeBorderCaseHandler>;

#include "pxtn.h"

PN_(Basic RingBuffer Tests)

template<template<typename, std::size_t> class TestBuffer>
void test_common_behavior() {
						TestBuffer<int, 3> q;
						int e;
//	====================== EXPECTED		========================== TEST
PX_(	"true"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"0"				, 	q.size()			);
PX_(	"true"				,	q.put(100)			);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"1"				, 	q.size()			);
PX_(	"100"				, 	q.peek()			);
PX_(	"true"				,	q.put(200)			);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"2"				, 	q.size()			);
PX_(	"100"				, 	q.peek(0)			);
PX_(	"200"				, 	q.peek(1)			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"100"				, 	e				);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"1"				, 	q.size()			);
PX_(	"200"				, 	q.peek()			);
PX_(	"true"				, 	q.get(e) 			);
PX_(	"200"				, 	e 				);
PX_(	"true"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
//	-------------------------------		-------------------------------
						e = 1200;
						while (!q.full())
							q.put(e++);
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.full()			);
PX_(	"1200"				, 	q.peek(0)			);
PX_(	"1201"				, 	q.peek(1)			);
PX_(	"1202"				, 	q.peek(2)			);
//	-------------------------------		-------------------------------
PX_(	"true"				, 	q.full()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"3"				, 	q.size()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"1200"				, 	e				);
PX_(	"2"				, 	q.size()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"1201"				, 	e				);
PX_(	"1"				, 	q.size()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"1202"				, 	e				);
PX_(	"0"				, 	q.size()			);
PX_(	"false"				, 	q.full()			);
PX_(	"true"				, 	q.empty()			);
}

template<template<typename, std::size_t> class TestBuffer>
void test_easy_behavior() {
						TestBuffer<float, 3> q;
						float e;
//	====================== EXPECTED		========================== TEST
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.put(1.1f)			);
PX_(	"1"				, 	q.size()			);
PX_(	"true"				, 	q.put(2.2f)			);
PX_(	"2"				, 	q.size()			);
PX_(	"true"				, 	q.put(3.3f)			);
PX_(	"3"				, 	q.size()			);
PX_(	"true"				, 	q.full()			);
PX_(	"true"				, 	q.put(4.4f)			);
PX_(	"3"				, 	q.size()			);
PX_(	"true"				, 	q.full()			);
//	-------------------------------		-------------------------------
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"2.2"				, 	e				);
PX_(	"2"				, 	q.size()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"3.3"				, 	e				);
PX_(	"1"				, 	q.size()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"4.4"				, 	e				);
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"0.0"				, 	e				);
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.empty()			);
}

template<template<typename, std::size_t> class TestBuffer>
void test_safe_behavior() {
						TestBuffer<float, 3> q;
						float e;
//	====================== EXPECTED		========================== TEST
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.put(1.1f)			);
PX_(	"1"				, 	q.size()			);
PX_(	"true"				, 	q.put(2.2f)			);
PX_(	"2"				, 	q.size()			);
PX_(	"true"				, 	q.put(3.3f)			);
PX_(	"3"				, 	q.size()			);
PX_(	"true"				, 	q.full()			);
PX_(	"false"				, 	q.put(4.4)			);
PX_(	"3"				, 	q.size()			);
PX_(	"true"				, 	q.full()			);
//	-------------------------------		-------------------------------
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"1.1"				, 	e				);
PX_(	"2"				, 	q.size()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"2.2"				, 	e				);
PX_(	"1"				, 	q.size()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"true"				, 	q.get(e)			);
PX_(	"3.3"				, 	e				);
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.empty()			);
						e = 0.0;
PX_(	"false"				, 	q.get(e)			);
PX_(	"0.0"				, 	e				);
PX_(	"0"				, 	q.size()			);
PX_(	"true"				, 	q.empty()			);
}

int main() {
	std::cout.setf(std::ios::boolalpha);
	std::cout.setf(std::ios::fixed);
	std::cout.precision(1);

	test_common_behavior<EasyRingBuffer>();
	test_easy_behavior<EasyRingBuffer>();

	test_common_behavior<SafeRingBuffer>();
	test_safe_behavior<SafeRingBuffer>();
}
