#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "../Macros.h"

void computeMatricesFromInputs(GLFWwindow* _window = nullptr);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif