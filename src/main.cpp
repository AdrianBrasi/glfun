#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>

int winW = 1280;
int winH = 720;
SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;

bool gameQuit = false;

void getGlVersion() {
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void createGraphicsPipeline() {

}

void vertexSpec() {
    const std::vector<GLfloat> vertexPosition {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER,
        vertexPosition.size() * sizeof(GLfloat), //NOLINT
        vertexPosition.data(),
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //NOLINT

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL IS FUCKED: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "SDL initialized" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        "OpenGL Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        winW, winH, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "WINDOW IS FUCKED: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Window created" << std::endl;
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cerr << "OPENGL CONTEXT IS FUCKED: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "OpenGL context created" << std::endl;
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW IS FUCKED: " << glewGetErrorString(err) << std::endl;
    } else {
        std::cout << "GLEW initialized" << std::endl;
    }

    getGlVersion();

}

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameQuit = true;
        }
    }
}

void preDraw() {

}

void draw() {

}

void mainLoop() {
    while (!gameQuit) { //NOLINT
        handleInput();
        preDraw();
        draw();

        SDL_GL_SwapWindow(window);
    }

}

void cleanup() {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
    std::cout << "Fuck you goodbye" << std::endl;
}


int main() {
    init();
    vertexSpec();
    createGraphicsPipeline();
    mainLoop();
    cleanup();
    return 0;
}
