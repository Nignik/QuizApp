// QuizApp.cpp : Defines the entry point for the application.
//

#include "QuizApp.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UserInterface.h"
#include "FilesHandler.h"
#include <iostream>
#include <queue>

#include "Game.h"
#include "SharedResources.h"

SharedResources sharedResources;

QuizApp::QuizApp() : m_Window(nullptr) {}

QuizApp::~QuizApp()
{
	Cleanup();
}

void QuizApp::InitWindow()
{
	glfwSetErrorCallback([](int error, const char* description) {
		std::cerr << "GLFW Error " << error << ": " << description << "\n";
		});

	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_Window = glfwCreateWindow(1280, 720, "Quiz App", nullptr, nullptr);
	if (m_Window == nullptr)
		throw std::runtime_error("Failed to create GLFW window");

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1); // Enable vsync
}

void QuizApp::InitImGui() const
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

}

void QuizApp::InputHandler()
{
	while (m_Window)
	{
		std::string input;
		std::getline(std::cin, input);

		sharedResources.SetInput(input);
	}
}

void QuizApp::MainLoop()
{
	Game game(&sharedResources);
	std::thread inputThread(&QuizApp::InputHandler, this);

	std::string currentPath = "C:/";
	std::string selectedFile;

	std::function<void()> swap = std::bind(&Game::Swap, &game);

	bool initialised = false;
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UI::RenderFileSelector("File selector", currentPath, selectedFile);

		if (initialised)
		{
			UI::RenderSwapButton(swap);
		}
		
		if (!selectedFile.empty())
		{
			if (m_GameThread.joinable())
			{
				game.End();
				m_GameThread.join();
			}

			game.Init(extractCards(getCsvFile(selectedFile)));
			initialised = true;
			m_GameThread = std::thread(&Game::Play, &game);

			std::cout << "Game Started!!!" << '\n';
		}

		selectedFile = "";

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
	}

	if (m_GameThread.joinable())
		m_GameThread.join();

	if (inputThread.joinable())
		inputThread.join();
}

void QuizApp::Cleanup() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}


void QuizApp::Run()
{
	InitWindow();
	InitImGui();
	MainLoop();
}
