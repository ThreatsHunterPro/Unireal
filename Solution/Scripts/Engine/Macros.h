#define INLINE			__inline
#define FORCEINLINE		__forceinline
#define SUPER			__super

#define CHECK_PTR(ptr, ...)	if (!ptr) return VA_ARGS
#define MAX	std::max

#include "../Libraries/List.h"
#include "../Libraries/Vectors.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glad.h>

#include <Scripts/common/shader.hpp>
#include <Scripts/common/texture.hpp>
#include <Scripts/common/controls.hpp>
#include <Scripts/common/objloader.hpp>
#include <Scripts/common/vboindexer.hpp>
#include <Scripts/common/text2D.hpp>

using namespace std;
using namespace glm;