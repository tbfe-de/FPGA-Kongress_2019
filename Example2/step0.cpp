#include <cassert>
#include <cstddef>

enum class Event : unsigned {
	Idle,
	ConnectionRequest,
	DataLinkUp,
	DataRequested,
	DataReceived,
	ConnectionShutdown,
};

class EventQueue {
	static const std::size_t QueueSize = 10+1;
	Event data[QueueSize];
	size_t iput = 0, iget = 0;
	static std::size_t wrap(std::size_t idx) {
		return idx % QueueSize;
	}
public:
	bool empty() const;
	bool full() const;
	std::size_t size() const;
	void put(Event);
	void get(Event&);
	Event peek(std::size_t = 0) const;
};

inline bool EventQueue::empty() const {
	return (iput == iget);
}

inline bool EventQueue::full() const {
	return (wrap(iput+1) == iget);
}

inline std::size_t EventQueue::size() const {
	return (iput >= iget)
		? iput - iget
		: iput + 11 - iget;
}

void EventQueue::put(Event e) {
	if (full())
		iget = wrap(iget+1);
	assert(!full());
	data[iput] = e;
	iput = wrap(iput+1);
}

void EventQueue::get(Event &e) {
	assert(!empty());
	e = data[iget];
	iget = wrap(iget+1);
}

Event EventQueue::peek(std::size_t offset) const {
	assert(offset < size());
	return data[wrap(iget + offset)];
}

#include "pxtn.h"

PN_(Basic Event Queue Tests)

std::ostream& operator<<(std::ostream& lhs, Event rhs) {
	switch (rhs) {
	case Event::Idle: 		return lhs << "Event::Idle";
	case Event::ConnectionRequest:	return lhs << "Event::ConnectionRequest";
	case Event::DataLinkUp:		return lhs << "Event::DataLinkUp";
	case Event::DataRequested:	return lhs << "Event::DataRequested";
	case Event::DataReceived:	return lhs << "Event::Datareceived";
	case Event::ConnectionShutdown:	return lhs << "Event::ConnectionShutdown";
	}
	return lhs << "Event::" << '{' << static_cast<unsigned>(rhs) << '}';
}

constexpr Event next(Event e) {
	 return static_cast<Event>(static_cast<unsigned>(e) + 1);
}

int main() {
	std::cout.setf(std::ios::boolalpha);

						EventQueue q;
						Event e;
//	====================== EXPECTED		========================== TEST
PX_(	"true"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"0"				, 	q.size()			);
						q.put(Event::ConnectionRequest);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"1"				, 	q.size()			);
PX_(	"Event::ConnectionRequest"	, 	q.peek()			);
						q.put(Event::DataLinkUp);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"2"				, 	q.size()			);
PX_(	"Event::ConnectionRequest"	, 	q.peek(0)			);
PX_(	"Event::DataLinkUp"		, 	q.peek(1)			);
PX_(	"Event::ConnectionRequest"	, 	q.get(e), e			);
PX_(	"false"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
PX_(	"1"				, 	q.size()			);
PX_(	"Event::DataLinkUp"		, 	q.peek()			);
PX_(	"Event::DataLinkUp"		, 	q.get(e), e 			);
PX_(	"true"				, 	q.empty()			);
PX_(	"false"				, 	q.full()			);
//	-------------------------------		-------------------------------
						e = static_cast<Event>(1200);
						while (!q.full())
							q.put(e), e = next(e);
PX_(	"Event::{1200}"			, 	q.peek(0)			);
PX_(	"Event::{1201}"			, 	q.peek(1)			);
PX_(	"Event::{1202}"			, 	q.peek(2)			);
PX_(	"Event::{1203}"			, 	q.peek(3)			);
PX_(	"Event::{1204}"			, 	q.peek(4)			);
PX_(	"Event::{1205}"			, 	q.peek(5)			);
PX_(	"Event::{1206}"			, 	q.peek(6)			);
PX_(	"Event::{1207}"			, 	q.peek(7)			);
PX_(	"Event::{1208}"			, 	q.peek(8)			);
PX_(	"Event::{1209}"			, 	q.peek(9)			);
//	-------------------------------		-------------------------------
PX_(	"true"				, 	q.full()			);
PX_(	"false"				, 	q.empty()			);
PX_(	"10"				, 	q.size()			);
PX_(	"Event::{1200}"			, 	q.get(e), e			);
PX_(	"9"				, 	q.size()			);
PX_(	"Event::{1201}"			, 	q.get(e), e			);
PX_(	"8"				, 	q.size()			);
PX_(	"Event::{1202}"			, 	q.get(e), e			);
PX_(	"7"				, 	q.size()			);
PX_(	"Event::{1203}"			, 	q.get(e), e			);
PX_(	"6"				, 	q.size()			);
PX_(	"Event::{1204}"			, 	q.get(e), e			);
PX_(	"5"				, 	q.size()			);
PX_(	"Event::{1205}"			, 	q.get(e), e			);
PX_(	"4"				, 	q.size()			);
PX_(	"Event::{1206}"			, 	q.get(e), e			);
PX_(	"3"				, 	q.size()			);
PX_(	"Event::{1207}"			, 	q.get(e), e			);
PX_(	"2"				, 	q.size()			);
PX_(	"Event::{1208}"			, 	q.get(e), e			);
PX_(	"1"				, 	q.size()			);
PX_(	"Event::{1209}"			, 	q.get(e), e			);
PX_(	"0"				, 	q.size()			);
PX_(	"false"				, 	q.full()			);
PX_(	"true"				, 	q.empty()			);
						
}
