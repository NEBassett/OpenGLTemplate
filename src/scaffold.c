#include "scaffold.h"

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static char *readFileIntoString(const char *file, int *oSize)
{
    FILE *fp;
    long size;
    char *str = NULL;
    
    fp = fopen(file, "rb");
    if(!fp)
    {
	perror("Failed to open file");
	return str;
    }
    
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    str = (char*) malloc(size + 1);
    if(str == NULL)
    {
	perror("Allocation failed");
	return str;
    }
    
    fread(str, 1, size, fp);
    str[size] = '\0';
    fclose(fp);
    if(oSize != NULL)
	*oSize = size;
    return str;
}


static int compileShaderFromFile(const char *file, GLuint shader, GLenum shaderType)
{
    GLint length, success;
    GLchar *src = (GLchar*)readFileIntoString(file, (int*)(&length));
    const GLchar **rSrc = (const GLchar**)&src;
    
    if(src == NULL)
	return -1;
    
    glShaderSource(shader, 1, rSrc, (GLint*)(&length));
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
	GLint shaderErrorLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shaderErrorLength);
	char *string = (char*)malloc(shaderErrorLength);
	if (string == NULL)
	{
	    perror("Allocation failed");
	    return -1;
	}
	glGetShaderInfoLog(shader, shaderErrorLength, &shaderErrorLength, string);
	printf("%s\n", string);
	free(string);
    }
    
    free(src);
    return 0;
}

// simple vertex / fragment shader
int compileProgramFromPaths(GLuint *prog, const char *vsSource, const char *fsSource)
{
    GLuint vs, fs;

    *prog = glCreateProgram();
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
  
    if (compileShaderFromFile(vsSource, vs, GL_VERTEX_SHADER) != 0)
    {
	perror("Vertex shader compilation failed");
	return -1;
    }
  
    if (compileShaderFromFile(fsSource, fs, GL_FRAGMENT_SHADER) != 0)
    {
	perror("Fragment shader compilation failed");
	return -1;
    }

    glAttachShader(*prog, vs);
    glAttachShader(*prog, fs);
    glLinkProgram(*prog);

    GLint success;
    glGetProgramiv(*prog, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
      GLint programErrorLength;
      glGetProgramiv(*prog, GL_INFO_LOG_LENGTH, &programErrorLength);
      char *string = malloc(programErrorLength);
      glGetProgramInfoLog(*prog, programErrorLength, &programErrorLength, string);
      printf("%s\n", string);
      free(string);
      glDeleteProgram(*prog);
    }
    
    return 0;
}

void GLAPIENTRY messageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam)
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

int initContext(GLFWwindow *window)
{
  if(!glfwInit())
    {
      return -1;
    }

  window = glfwCreateWindow(1920, 1080, "Renderer", NULL, NULL);
  if(!window)
    {
      glfwTerminate();
      return -1;
    }
  
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
      return -1;
    };
}
