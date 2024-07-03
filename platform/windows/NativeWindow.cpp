#include <iostream>
#include <cstdint>
#include <memory>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <format>

#include <stdexcept>
#include <filesystem>

#include <compile/Compiler.h>

#ifdef __WIN32__

#include <webgpu/webgpu.h>
#include <d3dcommon.h>

// 
#include <imgui.h>
#include <backends/imgui_impl_wgpu.h>
#include <backends/imgui_impl_glfw.h>

#endif

static std::vector<std::string> error_messages;
static float_t device_ratio = 1.0f;
static uint16_t w = 1620;
static uint16_t h = 1000;

#pragma region Utils

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) {
		throw std::runtime_error("Error during formatting.");
	}
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
}

#pragma endregion

int main(/*int argc, char* argv[]*/)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		return 1;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(w, h, "RCI Samples", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return 1;
	}
	glfwSetCursorPosCallback(window, mouse_callback);

	rci::ContexDesc context_desc{};
	context_desc.layer = window;
	context_desc.width = w;
	context_desc.height = h;

#ifdef __WIN32__
	HDC hdc = GetDC(NULL);
	int dpix = GetDeviceCaps(hdc, LOGPIXELSX);
	device_ratio = dpix / 96.0f;
	ReleaseDC(NULL, hdc);
	context_desc.error = [](const char* message)
		{
			error_messages.emplace_back(std::string(message));
		};
#endif

	rci::ContextSPTR context = std::make_shared<rci::Context>(std::move(context_desc));
	rci::CompilerSPTR compiler = std::make_shared<rci::Compiler>(context);
	rci::DirectedAcyclicGraphSPTR graph = std::make_shared<rci::DirectedAcyclicGraph>(context);


	glfwDestroyWindow(window);
	glfwTerminate();
}