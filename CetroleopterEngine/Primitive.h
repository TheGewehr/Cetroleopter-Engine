
#pragma once
#include "glmath.h"
#include "Color.h"
//#include "PhysBody3D.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:
	Primitive();

	void Update();
	virtual void	Render() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;


	Color color;
	mat4x4 transform;
	bool axis,wire;

protected:
	virtual void InnerRender() const;
	PrimitiveTypes type;
};

// ============================================
class CubePrimitive : public Primitive
{
public :
	CubePrimitive();
	CubePrimitive(float sizeX, float sizeY, float sizeZ);

protected:
	void InnerRender() const;
public:
	vec3 size;
};

// ============================================
class SpherePrimitive : public Primitive
{
public:
	SpherePrimitive(float radius = 1.f, float mass = 1.f);

protected:
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class CylinderPrimitive : public Primitive
{
public:
	CylinderPrimitive();
	CylinderPrimitive(float radius, float height);

protected:
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class LinePrimitive : public Primitive
{
public:
	LinePrimitive();
	LinePrimitive(float x, float y, float z);

protected:
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class PlanePrimitive : public Primitive
{
public:
	PlanePrimitive();
	PlanePrimitive(float x, float y, float z, float d);

protected:
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};