#include "polygon_graphic.h"

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "src/base/graphics/base_graphic.h"
#include "src/base/graphics/polygon/polygon_context.h"

const float vertices[] = {
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     -0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
     0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
};
const unsigned int indices[] = {
    0, 2, 1,  // первый треугольник
    0, 2, 3   // второй треугольник
};

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


struct PolygonCtx{
    GLuint program;
    unsigned int vao, vbo, ebo;
    float* vertices;
    unsigned int* indices;
};


int initPolygon(Context* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: Context is NULL\n", __func__);
        return 0;
    }

    initGraphics(ctx);
    PolygonCtx* p_ctx = initPolygonCtx();
    if (!p_ctx) {
        fprintf(stderr, "[ERROR] %s: Failed to initialize PolygonCtx\n", __func__);
        return 0;
    }
    setGraphicMode(getGraphicCtx(ctx), p_ctx);

    GLuint vs = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (!compile_program(getGraphicCtx(ctx), vs, fs)) {
        fprintf(stderr, "[ERROR] %s: Shader program compilation failed\n", __func__);
        return 0; 
    }

    // Создание VBO и VAO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    if (VAO == 0 || VBO == 0 || EBO == 0) {
        fprintf(stderr, "[ERROR] %s: OpenGL buffer generation failed\n", __func__);
        return 0;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setVAO(getGraphicCtx(ctx), VAO);
    setVBO(getGraphicCtx(ctx), VBO);
    setEBO(p_ctx, EBO);

    return 1;
}


int uploadPolygonBuffer(
        GraphicCtx* ctx,
        const float *vertices, size_t vsize,
        const unsigned int *indices, size_t isize
) {
    if (!vertices || !indices || !ctx) {
        fprintf(stderr, "[ERROR] %s: One of fields is NULL\n", __func__);
        return 0;
    }

    glBindVertexArray(getVAO(ctx));
    glBindBuffer(GL_ARRAY_BUFFER, getVBO(ctx));
    glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(float), vertices, GL_DYNAMIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return 1;
}

int process(GraphicCtx* ctx) {
    time_t now = time(NULL);
    int fr = now % 10 - 5;
    float next[24];
    memcpy(next, vertices, sizeof(vertices));
    for (int i = 0; i < 4; i++) { 
        next[6 * i] += fr * 0.1;
        next[6 * i + 1] += fr * 0.1;
    }
    uploadPolygonBuffer(ctx, next, 24, indices, 6);
    return 1;
}

int drawPolygon(Context* ctx) {
    GraphicCtx* g_ctx = getGraphicCtx(ctx);
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: Failed to retrieve GraphicCtx from Context\n", __func__);
        return 0;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    if (!setupRatio(ctx)) {
        fprintf(stderr, "[ERROR] %s: setupRatio failed\n", __func__);
        return 0; 
    }
    if (!process(g_ctx)) {
        fprintf(stderr, "[ERROR] %s: process failed\n", __func__);
        return 0;
    }
    glUseProgram(getProgram(g_ctx));
    glBindVertexArray(getVAO(g_ctx));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 1;
}

