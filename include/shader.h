#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>

class Shader {
    public:
        Shader(const std::string &, const std::string &);

        void use() const;

        unsigned int getId() const;

        void setBool(const std::string &, bool) const;
        void setInt(const std::string &, int) const;
        void setFloat(const std::string &, float) const;
        void setVec2(const std::string &, const glm::vec2 &) const;
        void setVec2(const std::string &, float, float) const;
        void setVec3(const std::string &, const glm::vec3 &) const;
        void setVec3(const std::string &, float, float, float) const;
        void setVec4(const std::string &, const glm::vec4 &) const;
        void setVec4(const std::string &, float, float, float, float);
        void setMat2(const std::string &, const glm::mat2 &) const;
        void setMat3(const std::string &, const glm::mat3 &) const;
        void setMat4(const std::string &, const glm::mat4 &) const;

    private:
        unsigned int id;

        void checkCompileErrors(unsigned int, const std::string &);
};

#endif //SHADER_H
