#pragma once

template <typename T>
class Vector2
{
public:
	// X�v�f
	T x;
	// Y�v�f
	T y;

	// �R���X�g���N�^
	Vector2() {
		(*this) = T(0);
	}
	Vector2(const T& i) {
		(*this) = i;
	}
	Vector2(const T& x, const T& y) {
		this->x = x;
		this->y = y;
	}

	// �R�s�[�R���X�g���N�^
	Vector2(const Vector2& vec) {
		(*this) = vec;
	}

	// �f�X�g���N�^
	~Vector2() {}


	void operator=(const T& i) {
		x = y = i;
	}
	void operator=(const Vector2& vec) {
		x = vec.x;
		y = vec.y;
	}

	void operator+=(const T& i) {
		x += i;
		y += i;
	}
	void operator-=(const T& i) {
		x -= i;
		y -= i;
	}
	void operator*=(const T& i) {
		x *= i;
		y *= i;
	}
	void operator/=(const T& i) {
		x /= i;
		y /= i;
	}

	void operator+=(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
	}
	void operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
	}
	void operator*=(const Vector2& vec) {
		x *= vec.x;
		y *= vec.y;
	}
	void operator/=(const Vector2& vec) {
		x /= vec.x;
		y /= vec.y;
	}

	Vector2 operator-(void) {
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& vec) {
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator-(const Vector2& vec) {
		return Vector2(x - vec.x, y - vec.y);
	}
	Vector2 operator*(const Vector2& vec) {
		return Vector2(x * vec.x, y * vec.y);
	}
	Vector2 operator/(const Vector2& vec) {
		return Vector2(x / vec.x, y / vec.y);
	}

	Vector2 operator+(const T& i) {
		return Vector2(x + i, y + i);
	}
	Vector2 operator-(const T& i) {
		return Vector2(x - i, y - i);
	}
	Vector2 operator*(const T& i) {
		return Vector2(x * i, y * i);
	}
	Vector2 operator/(const T& i) {
		return Vector2(x / i, y / i);
	}
};

template <typename T>
Vector2<T> operator+(const T& i, const Vector2<T>& vec) {
	return Vector2<T>(i + vec.x, i + vec.y);
}
template <typename T>
Vector2<T> operator-(const T& i, const Vector2<T>& vec) {
	return Vector2<T>(i - vec.x, i - vec.y);
}
template <typename T>
Vector2<T> operator*(const T& i, const Vector2<T>& vec) {
	return Vector2<T>(i * vec.x, i * vec.y);
}
template <typename T>
Vector2<T> operator/(const T& i, const Vector2<T>& vec) {
	return Vector2<T>(i / vec.x, i / vec.y);
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return Vector2<T>(vec1.x + vec2.x, vec1.y + vec2.y);
}
template <typename T>
Vector2<T> operator-(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return Vector2<T>(vec1.x - vec2.x, vec1.y - vec2.y);
}
template <typename T>
Vector2<T> operator*(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return Vector2<T>(vec1.x * vec2.x, vec1.y * vec2.y);
}
template <typename T>
Vector2<T> operator/(const Vector2<T>& vec1, const Vector2<T>& vec2) {
	return Vector2<T>(vec1.x / vec2.x, vec1.y / vec2.y);
}

typedef Vector2<int> Vec2;
typedef Vector2<float> Vec2f;