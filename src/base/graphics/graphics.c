#include "graphics.h"
#include "src/base/context/context.h"
#include "src/base/window/window.h"

#include <stdio.h>


// Простые шейдеры (встроенные в код)
const char* vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
         0.0f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f
    };
        
    // Создание VBO и VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setVAO(ctx, VAO);
    setVBO(ctx, VBO);
    setWindowResizeCallback(ctx, framebuffer_size_callback);

    return 1;
}

int drawing(Context* ctx) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(getProgram(ctx));
    glBindVertexArray(getVAO(ctx));
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return 1;
}

int uploadBuffer(float* buf) {
    if (buf == NULL) {
        return -1; 
    }
    return 1;
}
