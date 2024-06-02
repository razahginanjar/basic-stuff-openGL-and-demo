# basic-stuff-openGL-and-demo

 -you need to install vs comunnity or you can used it with ws code
-you need to include all:
src;src\renderer;$(SolutionDir)defendencies\stbi;$(SolutionDir)defendencies\glew-2.1.0\include;$(SolutionDir)defendencies\g-truc-glm-33b0eb9\include;$(SolutionDir)defendencies\imgui-master\include;$(SolutionDir)defendencies\glfw-3.4.bin.WIN32\include

-you need to change the sys to x86 or x32
-you need to add in preprocessor:
GLEW_STATIC;
-you need to add lib:
$(SolutionDir)defendencies\glfw-3.4.bin.WIN32\lib-vc2022;
$(SolutionDir)defendencies\glew-2.1.0\lib\Release\Win32;
- you need add dependencies:
glfw3.lib;Opengl32.lib;User32.lib;Gdi32.lib;Shell32.lib;glew32s.lib;
