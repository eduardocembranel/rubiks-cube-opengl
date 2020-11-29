#include <iostream>

#include <texture.hpp>
#include <stb_image.h>

Texture::Texture(const std::string &filePath, GLenum format) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
            GL_LINEAR_MIPMAP_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(filePath.c_str(), &width, &height, 
            &nrChannels, 0);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
                format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture: " << filePath << "\n";
    }
    stbi_image_free(image);
}

Texture::Texture(const Texture &texture) : id(texture.id), width(texture.width),
        height(texture.height), nrChannels(texture.nrChannels) {

}

unsigned int Texture::getId() const {
    return id;
}

void Texture::bind(unsigned int texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}
