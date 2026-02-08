#include "graphics.h"
#include "glad/gl.h"
#include "src/base/context/context.h"
#include "src/base/window/window.h"

#include <GLFW/glfw3.h>
#include <stdio.h>


// Простые шейдеры (встроенные в код)
const char* vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "uniform float window_d;\n"
    "out vec3 Color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x * window_d, aPos.yz, 1.0);\n"
    "   Color = aColor;\n"
    "}\0";

const char* fragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 Color;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(Color, 1.0f);\n"
    "}\0";


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
        return -1;
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
        return -1;
    }
    // =======================================
    
    // Теперь OpenGL функции доступны
    printf("OpenGL версия: %s\n", glGetString(GL_VERSION));
    printf("Вендор: %s\n", glGetString(GL_VENDOR));
    printf("Рендерер: %s\n", glGetString(GL_RENDERER));

    GLuint vs = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (!compile_program(ctx, vs, fs)) {
        return -1; 
    }
    float vertices[] = {
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 2, 1,  // первый треугольник
        0, 2, 3   // второй треугольник
    };
        
    // Создание VBO и VAO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setVAO(ctx, VAO);
    setVBO(ctx, VBO);
    setEBO(ctx, EBO);
    setWindowResizeCallback(ctx, framebuffer_size_callback);

    return 1;
}

int setupVAO(GLuint VAO, GLuint VBO) {
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 1;
}

int setupVBO(GLuint VBO, float* vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return 1;
}

int setupRatio(Context* ctx) {
    GLFWwindow* window = getCtxWindow(ctx);
    if (window == NULL) {
        return -1;
    }
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    int uni_loc = glGetUniformLocation(getProgram(ctx), "window_d");
    glUniform1f(uni_loc, (float)fb_height / fb_width);
    return 1;
}

int drawing(Context* ctx) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    setupRatio(ctx);
    glUseProgram(getProgram(ctx));
    glBindVertexArray(getVAO(ctx));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return 1;
}

int uploadBuffer(float* buf) {
    if (buf == NULL) {
        return -1; 
    }
    return 1;
}
