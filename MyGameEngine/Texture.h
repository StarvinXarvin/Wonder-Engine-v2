#pragma once

#include "Graphic.h"
#include "types.h"

#include <string>
#include <vector>
#include <memory>

using namespace std;

#define CHECKERTEXT_HEIGHT 100
#define CHECKERTEXT_WIDTH 100

class Texture
{
private:
	unsigned int _id;

public:
	using Ptr = shared_ptr<Texture>;

	explicit Texture(const string& path);
	Texture(Texture&& tex) noexcept;
	Texture();
	void bind() const;
	~Texture();

	unsigned int getID() { return _id; }

private:
	Texture(const Texture&) = delete;
	Texture operator=(const Texture&) = delete;
};