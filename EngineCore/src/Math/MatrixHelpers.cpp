#include "MatrixHelpers.h"

glm::vec3 MatrixHelpers::GetTranslation(const glm::mat4& matrix)
{
    return {matrix[3]};
}

glm::vec3 MatrixHelpers::GetForward(const glm::mat4& matrix)
{
    return {matrix[2]};
}

glm::vec3 MatrixHelpers::GetUp(const glm::mat4& matrix)
{
    return {matrix[1]};
}

glm::vec3 MatrixHelpers::GetRight(const glm::mat4& matrix)
{
    return {matrix[0]};
}