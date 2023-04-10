//
// Created by HoJoonEum on 2023/04/10.
//
#pragma once
#ifndef SHADERS_SHADER_H
#define SHADERS_SHADER_H

class Shader {
    unsigned int ID;

    Shader(const char *vertexShaderFileName, const char *fragmentShaderFileName) {
        // Follow steps to create shader program successfully
        // 1. Get the vertex and fragment shader source code as files from file path.
        // Geometry shader is optional.
        // In this step, you should make sure the files are loaded successfully.
        // Unless, throw exception and you should catch it.

        // 2. Once you load the source files for vertex and fragment shaders successfully,
        // you should save them into c_string.

        // For each shader, you do following steps.
        // a. Create shader using glCreateShader
        // b. Link the shader to shader source file with glShaderSource
        // c. Compile the shader with glCompileShader
        // d. Check the compile errors for shader compilation.

        // 3. So you compiled each shader, you link the shaders to shader program.
        // You create shader program with glCreateProgram().
        // Then, attach each shader to the program with glAttachShader().
        // Finally, link the program with glLinkProgram().
        // Last but not least, check compile errors for the program link.

        // 4. To Wrap the construction up, delete each shader no longer needed.
        // With glDeleteShader().
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
