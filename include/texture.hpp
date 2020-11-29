#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture {
    public:
        Texture(const std::string &, GLenum);
        Texture(const Texture &);
        unsigned int getId() const;
        void bind(unsigned int = 0);
        
    private:
        unsigned int id;
        int width;
        int height;
        int nrChannels;
};

#endif //!TEXTURE_HPP
