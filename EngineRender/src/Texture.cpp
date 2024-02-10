#include "Texture.h"
#include <stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <filesystem>

namespace EngineRender
{
    Texture::Texture(EngineLibrary::FileSystem::PathHandle handle, bool containsAlpha) : _handle(handle), _containsAlpha(containsAlpha)
    {
    }

    Texture::~Texture()
    {
    }

    void Texture::Load()
    {
        glGenTextures(1, &_glIndex);
        glBindTexture(GL_TEXTURE_2D, _glIndex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
        int width, height, nrChannels;
        const std::filesystem::path path = _handle.GetFullPath();
        const std::string pathStr = path.string();

        const unsigned int format = _containsAlpha ? GL_RGBA : GL_RGB;

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(pathStr.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture:" << path << std::endl;
        }

        stbi_image_free(data);
    }

    void Texture::Attach(int offset) const
    {
        glActiveTexture(GL_TEXTURE0 + offset);
        glBindTexture(GL_TEXTURE_2D, _glIndex);
    }
}
