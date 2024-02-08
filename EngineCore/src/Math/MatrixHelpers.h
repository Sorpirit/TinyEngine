#pragma once

#include <glm/glm.hpp>


class MatrixHelpers
{
public:
    static glm::vec3 GetTranslation(const glm::mat4& matrix);
    static glm::vec3 GetForward(const glm::mat4& matrix);
    static glm::vec3 GetUp(const glm::mat4& matrix);
    static glm::vec3 GetRight(const glm::mat4& matrix);
};
