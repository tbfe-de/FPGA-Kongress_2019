#include <cassert>
#include <cstddef>

#if 0
template <typename T>
class Whatever {
	T *m_data;
	std::size_t m_size;
public:
	Whatever(T* data, std::size_t size)
		: m_data{data}
		, m_size{size}
	{}
	auto size() const { return m_size; }
};

int main() {
	int theBuffer[100];
	Whatever<int> object{theBuffer, sizeof theBuffer / sizeof theBuffer[0]};
	assert(object.size() == 100);
}
#else

template<typename T>
struct BufferRef {
	T* const m_data;
	const std::size_t m_size;
	BufferRef(T data[], std::size_t size)
		: m_data{data}
		, m_size{size}
	{}
	template<std::size_t N>
	BufferRef(T (&data)[N])
		: BufferRef{data, N}
	{}
};

template <typename T>
class Whatever {
	BufferRef<T> m_buffer;
public:
	Whatever(const BufferRef<T> &init)
		: m_buffer{init}
	{}
	Whatever(T* data, std::size_t size)
		: Whatever{BufferRef<T>{data, size}}
	{}
	auto size() const { return m_buffer.m_size; }
};

int main() {
	int theBuffer[100];
	Whatever<int> object{theBuffer};
	assert(object.size() == 100);
}
#endif
