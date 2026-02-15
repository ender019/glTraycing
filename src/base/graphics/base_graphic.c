#include "base_graphic.h"

#include <stdio.h>

#include "src/base/window/window.h"

GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    // Проверка ошибок
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf("Shader compilation error: %s\n", info_log);

    }
    
    return shader;
}

// Callback для изменения размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    printf("Размер окна изменен: %d x %d\n", width, height);
}


int compile_program(Context* ctx, GLuint vs, GLuint fs) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        printf("Program linking error: %s\n", info_log);
        return 0;
    }
    
    glDetachShader(program, vs);
    glDeleteShader(vs);
    glDetachShader(program, fs);
    glDeleteShader(fs);

    setProgram(ctx, program);

    return 1;
}

int initGraphics(Context* ctx) {
    // ====== ВАЖНО: ИНИЦИАЛИЗАЦИЯ GLAD ======
    if (!gladLoadGL(glfwGetProcAddress)) {
        fprintf(stderr, "Ошибка инициализации GLAD\n");
        glfwTerminate();
        return 0;
    }
    // =======================================
    
    // Теперь OpenGL функции доступны
    printf("OpenGL версия: %s\n", glGetString(GL_VERSION));
    printf("Вендор: %s\n", glGetString(GL_VENDOR));
    setWindowResizeCallback(ctx, framebuffer_size_callback);

    return 1;
}

int setupRatio(Context* ctx) {
    GLFWwindow* window = getCtxWindow(ctx);
    if (window == NULL) {
        return 0;
    }
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    int uni_loc = glGetUniformLocation(getProgram(ctx), "window_d");
    glUniform1f(uni_loc, (float)fb_height / fb_width);
    return 1;
}

