#include "src/base/context/context.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

int initWindow(Context* ctx) {
    // Инициализация GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Ошибка инициализации GLFW\n");
        return -1;
    }

    // Настройка GLFW для OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + OpenGL Test", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Ошибка создания окна\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!setCtxWindow(ctx, window)) {
        return -1;
    }
    return 1;
}

int setWindowResizeCallback(Context* ctx, void(clbck)(GLFWwindow*, int, int)) {
    GLFWwindow* window = getCtxWindow(ctx);
    if (!window) {
        return -1;
    }
    if (clbck == NULL) {
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, clbck);
    return 1;
}

int startWindow(Context* ctx, int(work)(Context*)) {
    GLFWwindow* window = getCtxWindow(ctx);
    if (!window) {
        return -1;
    }

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        // Обработка ввода
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        if (!work(ctx)) {
            glfwSetWindowShouldClose(window, 1);
        }
        
        // Обмен буферов и обработка событий
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 1;
}

int destroyWindow(Context* ctx) {
    GLFWwindow* window = getCtxWindow(ctx);
    if (!window) {
        return 0;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}

