#pragma once
class Mesh
{
public:
	virtual void Attach() const = 0;
	virtual unsigned int GetDrawSize() const = 0;
};