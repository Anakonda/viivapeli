#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>

#include <unordered_set>
#include <cmath>
class Coordinates
{
	friend std::ostream& operator<<(std::ostream &output, const Coordinates &vector);
	public:
		short x;
		short y;

		Coordinates(int x = 0, int y = 0);

		Coordinates cpy(void) const;
		Coordinates operator+(const Coordinates &coordinates) const;
		Coordinates operator-(const Coordinates &coordinates) const;

		void operator+=(const Coordinates &coordinates);
		void operator-=(const Coordinates &coordinates);
		Coordinates& operator=(const Coordinates &coordinates);

		bool operator==(const Coordinates &coordinates) const;
		bool operator!=(const Coordinates &coordinates) const;
};

inline Coordinates Coordinates::cpy() const
{
	return Coordinates(this->x, this->y);
}

inline Coordinates Coordinates::operator+(const Coordinates &other) const
{
	return Coordinates(this->x + other.x, this->y + other.y);
}

inline Coordinates Coordinates::operator-(const Coordinates &other) const
{
	return Coordinates(this->x - other.x, this->y - other.y);
}

inline void Coordinates::operator+=(const Coordinates &other)
{
	this->x += other.x;
	this->y += other.y;
}

inline void Coordinates::operator-=(const Coordinates &other)
{
	this->x -= other.x;
	this->y -= other.y;
}

inline Coordinates& Coordinates::operator=(const Coordinates &other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

inline bool Coordinates::operator==(const Coordinates &other) const
{
	return this->x == other.x && this->y == other.y;
}

inline bool Coordinates::operator!=(const Coordinates &other) const
{
	return this->x != other.x || this->y != other.y;
}

namespace std
{
	template <>
	struct hash<Coordinates>
	{
		size_t operator()(const Coordinates &t) const
		{
			return size_t(t.x) * size_t(std::pow(2, sizeof(t.y)*8)) + size_t(t.y);
		}
	};
}

#endif
