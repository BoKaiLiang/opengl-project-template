#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include <glad/glad.h>
#include <stb_image.h>

class Texture final {
public:
	Texture(const std::string& imgPath);
	
	static Texture* Create(const std::string& imgPath);

	~Texture() = default;
	
	static Texture LoadTexture(const std::string& imgPath);

	inline GLuint GetID() const { return m_ID; }
	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; };

private:
	GLuint m_ID = 0;
	int m_Width = 1, m_Height = 1;
	GLuint m_SrcFmt = GL_RED;
	GLuint m_TexFmt = GL_RED;
};

#endif // !_TEXTURE_H_
