#include "renderer/renderer.hpp"
#include "renderer/vertexBuffer.hpp"
#include "renderer/indexBuffer.hpp"
#include "renderer/vertexArray.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//include imGui
#include "vendor/imgui.h"
#include "vendor/imgui_impl_glfw.h"
#include "vendor/imgui_impl_opengl3.h"

//include the test
#include "test/TestClearColor.hpp"
#include "test/TestTexture.hpp"

//enable for the to_string glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <vector>

//readfile
#include <fstream>
#include <sstream>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); //vertical sync (bisa jadi di pake jalan pintas buat)
                         //normalin framerate

    if (glewInit() != GLEW_OK)
        std::cout << "glew error" << std::endl;

    //to know openGL ver
    std::cout << glGetString(GL_VERSION) << std::endl;


    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //initialize imGUI
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsLight();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        //initialize the test
        Test::Test* currentTest = nullptr;
        Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
        currentTest = testMenu;
        testMenu->registerTest<Test::TestClearColor>("test color");
        testMenu->registerTest<Test::TestTexture>("test texture2D");

        //initialize renderer object
        Renderer render;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
            render.clear();

            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest)
            {
                currentTest->onUpdate(0.0f);
                currentTest->onRender();
                ImGui::Begin("test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->onImGui();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        //clean up test
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }
    
    // Cleanup IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}