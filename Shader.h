//
// Created by HoJoonEum on 2023/04/10.
//
#pragma once
#ifndef SHADERS_SHADER_H
#define SHADERS_SHADER_H

#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include "glad/include/glad/glad.h"

class Shader {
    unsigned int ID;

    Shader(const char *vertexShaderFileName, const char *fragmentShaderFileName) {
        // Follow steps to create shader program successfully
        // 1. Get the vertex and fragment shader source code as files from file path.
        // Geometry shader is optional.
        // In this step, you should make sure the files are loaded successfully.
        // Unless, throw exception and you should catch it.
            std::string vertexShaderCode;
            std::string fragmentShaderCode;
            std::ifstream vertexShaderFile;
            std::ifstream fragmentShaderFile;
            vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit)
            fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit)
        try {
            // Open each file.
            vertexShaderFile.open(vertexShaderFileName);
            fragmentShaderFile.open(fragmentShaderFileName);
            // Read each file into string buffer.
            std::stringstream vertexStream, fragmentStream;
            vertexStream << vertexShaderFile.rdbuf();
            fragmentStream << fragmentShaderFile.rdbuf();
            // Once reading buffer is end, Close the files.
            vertexShaderFile.close();
            fragmentShaderFile.close();
            // And now, assign code as string from string stream.
            vertexShaderCode = vertexStream.str();
            fragmentShaderCode = fragmentStream.str();
        }
        catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        // 2. Once you load the source files for vertex and fragment shaders successfully,
        // you should save them into c_string which is char buffer.
        const char* vSCode = vertexShaderCode.c_str();
        const char* fSCode = fragmentShaderCode.c_str();
        // For each shader, you do following steps.
        // a. Create shader using glCreateShader
        unsigned int vShader, fShader;
        vShader = glCreateShader();
        fShader = glCreateShader();
        // b. Link the shader to shader source file with glShaderSource
        glShaderSource(vShader,1,vertexShaderCode,NULL);
        glShaderSource(fShader,1,fragmentShaderCode,NULL);
        // c. Compile the shader with glCompileShader
        glCompileShader(vShader);
        glCompileShader(fShader);
        // d. Check the compile errors for shader compilation.
        checkCompileErrors(vShader, "VERTEX");
        checkCompileErrors(fShader, "FRAGMENT");
        // 3. So you compiled each shader, you link the shaders to shader program.
        // You create shader program with glCreateProgram().
        ID = glCreateProgram()
        // Then, attach each shader to the program with glAttachShader().
        glAttachShader(ID, vShader);
        glAttachShader(ID, fShader);
        // Finally, link the program with glLinkProgram().
        glLinkProgram(ID);
        // Last but not least, check compile errors for the program link.
        checkCompileErrors(ID, "PROGRAM");
        // 4. To Wrap the construction up, delete each shader no longer needed.
        // With glDeleteShader().
        glDeleteShader(vShader);
        glDeleteShader(fShader);
    }
    // For the ease of use, you can add few public functions.

    // activate the shader program.
    void use() {
        glUserProgram(ID);
    }

    // utility uniform functions
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    // helper functions
    void setInt(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, bool value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

private:
    // utility functions for checking shader compilation and linking errors.
    void checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- ---------------------------- -- " << std::endl;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- ---------------------------- -- " << std::endl;
            }
        }
    }
};

#endif //SHADERS_SHADER_H
