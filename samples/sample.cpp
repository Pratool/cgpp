#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Eigen/Dense>

GLuint VBO;

std::string readFile(std::string &&inputFilePath)
{
    std::fstream input{inputFilePath, std::ios::in | std::ios::ate};

    // Fill string with 0-byte values.
    std::string inputStr(input.tellg(), '\0');
    input.seekg(0);

    if (! input.read(&inputStr[0], inputStr.size()))
        return "";

    input.close();

    return inputStr;
}

void createVertexBuffer()
{
    Eigen::Vector3f vertices[3];

    vertices[0] = Eigen::Vector3f({-1.0f, -1.0f, 0.0f});
    vertices[1] = Eigen::Vector3f({1.0f, -1.0f, 0.0f});
    vertices[2] = Eigen::Vector3f({0.0f, 1.0f, 0.0f});

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void renderCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

static void addShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void compileShaders(
    std::string &&vertexShaderPath, std::string &&fragmentShaderPath)
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0)
    {
        std::clog << "Error compiling shaders." << std::endl;
        exit(1);
    }

    std::string vertexShaderSource = readFile(std::move(vertexShaderPath));
    std::string fragmentShaderSource = readFile(std::move(fragmentShaderPath));

    if ("" == vertexShaderSource || "" == fragmentShaderSource)
    {
        exit(1);
    }

    addShader(ShaderProgram, vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    addShader(ShaderProgram, fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

int main(int argc, char** argv)
{
    // CLI args pass-through.
    glutInit(&argc, argv);

    // Set up window frame.
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Test App");

    // Add callbacks.
    glutDisplayFunc(renderCallback);

    // Must init glew after glut.
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        std::clog << "Error: '" << glewGetErrorString(res) << '\'' << std::endl;
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    createVertexBuffer();

    compileShaders("shader.fs", "shader.vs");

    glutMainLoop();

    return 0;
}
