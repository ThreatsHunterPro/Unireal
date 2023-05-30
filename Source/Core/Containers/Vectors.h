#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

struct Vector2
{

#pragma region Fields

	float x;
	float y;

#pragma endregion

#pragma region Constructors

	Vector2()
	{
		x = y = 0.0f;
	}
	Vector2(const float& _value)
	{
		x = y = _value;
	}
	Vector2(const float& _x, const float& _y)
	{
		x = _x;
		y = _y;
	}
	Vector2(const vec2& _vector)
	{
		x = _vector.x;
		y = _vector.y;
	}

#pragma endregion

#pragma region Operators

	FORCEINLINE bool operator >= (const Vector2& _vector) const
	{
		return x >= _vector.x
			&& y >= _vector.y;
	}
	FORCEINLINE bool operator <= (const Vector2& _vector) const
	{
		return x <= _vector.x
			&& y <= _vector.y;
	}
	FORCEINLINE bool operator == (const Vector2& _vector) const
	{
		return x == _vector.x
			&& y == _vector.y;
	}
	FORCEINLINE bool operator != (const Vector2& _vector) const
	{
		return x != _vector.x
			&& y != _vector.y;
	}

	FORCEINLINE Vector2 operator - (const Vector2& _vector) const
	{
		return Vector2(x - _vector.x, y - _vector.y);
	}
	FORCEINLINE Vector2 operator + (const Vector2& _vector) const
	{
		return Vector2(x + _vector.x, y + _vector.y);
	}
	FORCEINLINE Vector2 operator -= (const Vector2& _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		return *this;
	}
	FORCEINLINE Vector2 operator += (const Vector2& _vector)
	{
		x += _vector.x;
		y += _vector.y;
		return *this;
	}
	FORCEINLINE Vector2 operator * (const float _value) const
	{
		return Vector2(x * _value, y * _value);
	}
	FORCEINLINE Vector2 operator * (const Vector2& _vector) const
	{
		return Vector2(x * _vector.x, y * _vector.y);
	}
	FORCEINLINE Vector2 operator *= (const float _value)
	{
		x *= _value;
		y *= _value;
		return *this;
	}

	//TODO IMPLEMENT

#pragma endregion

};

struct Vector3
{

#pragma region Fields

	float x;
	float y;
	float z;

#pragma endregion

#pragma region Constructors

	Vector3()
	{
		x = y = z = 0.0f;
	}
	Vector3(const float _value)
	{
		x = y = z = _value;
	}
	Vector3(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	/*Vector3(const Rotator& _rotator)
	{
		x = _rotator.pitch;
		y = _rotator.yaw;
		z = _rotator.roll;
	}*/
	Vector3(const vec3& _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
	}

#pragma endregion

#pragma region Operators

	FORCEINLINE bool operator >= (const Vector3& _vector) const
	{
		return x >= _vector.x
			&& y >= _vector.y
			&& z >= _vector.z;
	}
	FORCEINLINE bool operator <= (const Vector3& _vector) const
	{
		return x <= _vector.x
			&& y <= _vector.y
			&& z <= _vector.z;
	}
	FORCEINLINE bool operator == (const Vector3& _vector) const
	{
		return x == _vector.x
			&& y == _vector.y
			&& z == _vector.z;
	}
	FORCEINLINE bool operator != (const Vector3& _vector) const
	{
		return x != _vector.x
			&& y != _vector.y
			&& z != _vector.z;
	}

	FORCEINLINE Vector3 operator - (const Vector3& _vector) const
	{
		return Vector3(x - _vector.x, y - _vector.y, z - _vector.z);
	}
	FORCEINLINE Vector3 operator + (const Vector3& _vector) const
	{
		return Vector3(x + _vector.x, y + _vector.y, z + _vector.z);
	}
	FORCEINLINE Vector3 operator -= (const Vector3& _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;
		return *this;
	}
	FORCEINLINE Vector3 operator += (const Vector3& _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;
		return *this;
	}
	FORCEINLINE Vector3 operator * (const float _value) const
	{
		return Vector3(x * _value, y * _value, z * _value);
	}
	FORCEINLINE Vector3 operator * (const Vector3& _vector) const
	{
		return Vector3(x * _vector.x, y * _vector.y, z * _vector.z);
	}
	FORCEINLINE Vector3 operator *= (const float _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		return *this;
	}

	//TODO IMPLEMENT

#pragma endregion

#pragma region Getters

	FORCEINLINE static Vector3 ZeroVector() { return Vector3(0.0f); }
	FORCEINLINE static Vector3 OneVector() { return Vector3(1.0f); }
	FORCEINLINE static Vector3 ForwardVector() { return Vector3(1.0f, 0.0f, 0.0f); }
	FORCEINLINE static Vector3 BackwardVector() { return Vector3(-1.0f, 0.0f, 0.0f); }
	FORCEINLINE static Vector3 LeftVector() { return Vector3(0.0f, -1.0f, 0.0f); }
	FORCEINLINE static Vector3 RightVector() { return Vector3(0.0f, 1.0f, 0.0f); }
	FORCEINLINE static Vector3 UpVector() { return Vector3(0.0f, 0.0f, 1.0f); }
	FORCEINLINE static Vector3 DownVector() { return Vector3(0.0f, 0.0f, -1.0f); }
	FORCEINLINE vec3 ToVec3() const { return vec3(x, y, z); } 

#pragma endregion
};

struct Vector4
{

#pragma region Fields

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};

#pragma endregion
	
#pragma region Constructors

	Vector4()
	{
		x = y = z = w = 0.0f;
	}
	Vector4(const float& _value)
	{
		x = y = z = w = _value;
	}
	Vector4(const float& _x, const float& _y, const float& _z, const float& _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	Vector4(const vec4& _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
		w = _vector.w;
	}

#pragma endregion

#pragma region Operators

	FORCEINLINE bool operator >= (const Vector4& _vector) const
	{
		return x >= _vector.x
			&& y >= _vector.y
			&& z >= _vector.z
			&& w >= _vector.w;
	}
	FORCEINLINE bool operator <= (const Vector4& _vector) const
	{
		return x <= _vector.x
			&& y <= _vector.y
			&& z <= _vector.z
			&& w <= _vector.w;
	}
	FORCEINLINE bool operator == (const Vector4& _vector) const
	{
		return x == _vector.x
			&& y == _vector.y
			&& z == _vector.z
			&& w == _vector.w;
	}
	FORCEINLINE bool operator != (const Vector4& _vector) const
	{
		return x != _vector.x
			&& y != _vector.y
			&& z != _vector.z
			&& w != _vector.w;
	}

	FORCEINLINE Vector4 operator - (const Vector4& _vector) const
	{
		return Vector4(x - _vector.x, y - _vector.y, z - _vector.z, w - _vector.w);
	}
	FORCEINLINE Vector4 operator + (const Vector4& _vector) const
	{
		return Vector4(x + _vector.x, y + _vector.y, z + _vector.z, w + _vector.w);
	}
	FORCEINLINE Vector4 operator -= (const Vector4& _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;
		w -= _vector.z;
		return *this;
	}
	FORCEINLINE Vector4 operator += (const Vector4& _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;
		w += _vector.w;
		return *this;
	}
	FORCEINLINE Vector4 operator * (const float _value) const
	{
		return Vector4(x * _value, y * _value, z * _value, w * _value);
	}
	FORCEINLINE Vector4 operator * (const Vector4& _vector) const
	{
		return Vector4(x * _vector.x, y * _vector.y, z * _vector.z, w * _vector.w);
	}
	FORCEINLINE Vector4 operator *= (const float _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		w *= _value;
		return *this;
	}

#pragma endregion

};

struct Rotator
{

#pragma region Fields

	float pitch;
	float yaw;
	float roll;

#pragma endregion

#pragma region Constructors

	Rotator()
	{
		pitch = yaw = roll = 0.0f;
	}
	Rotator(float _value)
	{
		pitch = yaw = roll = _value;
	}
	Rotator(float _pitch, float _yaw, float _roll)
	{
		pitch = _pitch;
		yaw = _yaw;
		roll = _roll;
	}
	Rotator(const vec3& _vector)
	{
		pitch = _vector.x;
		yaw = _vector.y;
		roll = _vector.z;
	}

#pragma endregion

#pragma region Operators

	FORCEINLINE bool operator >= (const Rotator& _rotator) const
	{
		return pitch >= _rotator.pitch && yaw >= _rotator.yaw && roll >= _rotator.roll;
	}
	FORCEINLINE bool operator <= (const Rotator& _rotator) const
	{
		return pitch <= _rotator.pitch && yaw <= _rotator.yaw && roll <= _rotator.roll;
	}
	FORCEINLINE Rotator operator - (const Rotator& _rotator) const
	{
		return Rotator(pitch - _rotator.pitch, yaw - _rotator.yaw, roll - _rotator.roll);
	}
	FORCEINLINE Rotator operator + (const Rotator& _rotator) const
	{
		return Rotator(pitch + _rotator.pitch, yaw + _rotator.yaw, roll + _rotator.roll);
	}
	FORCEINLINE Rotator operator -= (const Rotator& _rotator)
	{
		pitch -= _rotator.pitch;
		yaw -= _rotator.yaw;
		roll -= _rotator.roll;
		return *this;
	}
	FORCEINLINE Rotator operator += (const Rotator& _rotator)
	{
		pitch += _rotator.pitch;
		yaw += _rotator.yaw;
		roll += _rotator.roll;
		return *this;
	}
	FORCEINLINE Rotator operator * (const float _value) const
	{
		return Rotator(pitch * _value, yaw * _value, roll * _value);
	}
	FORCEINLINE Rotator operator *= (const float _value)
	{
		pitch *= _value;
		yaw *= _value;
		roll *= _value;
		return *this;
	}

	//TODO IMPLEMENT

	#pragma endregion

};

struct Transform
{

#pragma region Fields

	Vector3 location;
	Rotator rotation;
	Vector3 scale;

#pragma endregion

#pragma region Constructors

	Transform()
	{
		location = Vector3(0.0f);
		rotation = Rotator(0.0f);
		scale = Vector3(0.0f);
	}
	Transform(const Vector3& _location, const Rotator& _rotation, const Vector3& _scale)
	{
		location = _location;
		rotation = _rotation;
		scale = _scale;
	}

#pragma endregion

#pragma region Operators

	FORCEINLINE bool operator >= (const Transform& _transform) const
	{
		return location >= _transform.location
			&& rotation >= _transform.rotation
			&& scale >= _transform.scale;
	}
	FORCEINLINE bool operator <= (const Transform& _transform) const
	{
		return location <= _transform.location
			&& rotation <= _transform.rotation
			&& scale <= _transform.scale;
	}
	FORCEINLINE Transform operator - (const Transform& _transform) const
	{
		return Transform(location - _transform.location, rotation - _transform.rotation, scale - _transform.scale);
	}
	FORCEINLINE Transform operator + (const Transform& _transform) const
	{
		return Transform(location + _transform.location, rotation + _transform.rotation, scale + _transform.scale);
	}
	FORCEINLINE Transform operator -= (const Transform& _transform)
	{
		location -= _transform.location;
		rotation -= _transform.rotation;
		scale -= _transform.scale;
		return *this;
	}
	FORCEINLINE Transform operator += (const Transform& _transform)
	{
		location += _transform.location;
		rotation += _transform.rotation;
		scale += _transform.scale;
		return *this;
	}
	FORCEINLINE Transform operator * (const float _transform) const
	{
		return Transform(location * _transform, rotation * _transform, scale * _transform);
	}
	FORCEINLINE Transform operator *= (const float _transform)
	{
		location *= _transform;
		rotation *= _transform;
		scale *= _transform;
		return *this;
	}

	//TODO IMPLEMENT

#pragma endregion
};