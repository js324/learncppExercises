#include <iostream>
#include <string>
template <typename T>
class Pair1 {
private:
	T m_one;
	T m_two;
public:
	Pair1(T one, T two) : m_one{ one }, m_two{ two } {
	}
	const T& first() const {
		return m_one;
	}
	const T& second() const {
		return m_two;
	}
	
};
template <typename T1, typename T2>
class Pair {
private:
	T1 m_one;
	T2 m_two;
public:
	Pair(T1 one, T2 two) : m_one{ one }, m_two{ two } {
	}
	const T1& first() const {
		return m_one;
	}
	const T2& second() const {
		return m_two;
	}
	virtual ~Pair() = default;
};
template<typename T2>
class StringValuePair : public Pair<std::string, T2> {
public:
	StringValuePair(std::string str, T2 val) : Pair<std::string, T2>{ str, val } {

	};
};
int main()
{
	StringValuePair<int> svp { "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}
