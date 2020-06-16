#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include <glad/glad.h>
#include <stb_image.h>

class Texture final {
public:
	Texture(const std::string& imgPath);

	~Texture() = default;

	inline GLuint GetID() const { return m_ID; }

private:
	GLuint m_ID;
};

#endif // !_TEXTURE_H_
