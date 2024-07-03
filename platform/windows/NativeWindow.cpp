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

#include <rci.h>
#include <d3dcommon.h>

// imgui
#include <imgui.h>
#include <backends/imgui_impl_wgpu.h>
#include <backends/imgui_impl_glfw.h>

// utils
#include "utils/AttachmentHelper.h"
#include "utils/UIHelper.h"

#endif

static uint16_t w = 1620;
static uint16_t h = 1000;
static uint16_t fps = 0;
static float_t device_ratio = 1.0f;

static std::vector<std::string> output_messages;
static std::vector<std::string> error_messages;

static const char* selected_item = "02_Cube3D";

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

static bool init_imgui(GLFWwindow* window, const rci::ContextSPTR& context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO();
	ImGui_ImplGlfw_InitForOther(window, true);

	ImGui_ImplWGPU_InitInfo info = {};
	info.NumFramesInFlight = 3;
	info.Device = context->GetGpuDevice();
	info.RenderTargetFormat = context->GetPreferredFormat();
	info.DepthStencilFormat = context->GetDepthTextureFormat();
	ImGui_ImplWGPU_Init(&info);

	return true;
}

static void release_imgui()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplWGPU_Shutdown();
}

static void update_imgui(const rci::ContextSPTR& context, const WGPURenderPassEncoder& render_pass_encoder)
{
	ImGui_ImplWGPU_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	const char* items[] = {

		// basic demo
		"Compute",
		"DrawCount",
		"DrawIndexed",
		"FBO",
		"MapBuffer",
		"MorphUniformBuffer",
		"SSBO",
		"Texture1D",
		"Texture2D",
		"Texture2DArray",
		"Texture2DSampler",
		"Texture3D",
		"TextureCube",
		"TextureCubeArray",
		"Uniform",

		// complex demo
		"01_TextureCombined",
		"02_Cube3D",
		"03_CameraMove"
	};

	ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;
	ImGuiStyle& style = ImGui::GetStyle();
	float w = ImGui::CalcItemWidth();
	float spacing = style.ItemInnerSpacing.x;
	float button_sz = ImGui::GetFrameHeight();
	ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
	ImGui::GetFont()->Scale = device_ratio;
	ImGui::Begin("Examples", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize
	);
	ImGui::Text("fps:");
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), std::to_string(fps).c_str());
	ImGui::NewLine();
	ImGui::Text("select example:");
	if (ImGui::BeginCombo("##combo", selected_item))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
			bool is_selected = (selected_item == items[n]);
			if (ImGui::Selectable(items[n], is_selected)) {
				selected_item = items[n];
			}
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	ImGui::End();

	// error message
	{
		if (!error_messages.empty()) {
			ImGui::SetNextWindowSize(ImVec2(w / 4, h / 4));
			ImGui::SetNextWindowPos(ImVec2(0, h / 4));
			ImGui::Begin("error messages", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
			for (const auto& error_message : error_messages) {
				ImGui::Text(error_message.c_str());
			}
			ImGui::End();
		}
		error_messages.clear();
	}

	// output message
	{
		if (!output_messages.empty()) {
			ImGui::SetNextWindowSize(ImVec2(w / 2, h / 2));
			ImGui::SetNextWindowPos(ImVec2(w / 4, h / 4));
			ImGui::Begin("output messages", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
			for (const auto& output_message : output_messages) {
				ImGui::Text(output_message.c_str());
			}
			ImGui::End();
		}
		output_messages.clear();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), render_pass_encoder);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//camera.ProcessKeyboard(RIGHT, deltaTime);
	}
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

	// create depth stencil attachment
	rci::DepthStencilAttachmentSPTR depth_stencil_attachment = geosketchpad::AttachmentHelper::GetInstance().CreateDepthStencilAttachment(
		compiler,
		context,
		w,
		h
	);

	// create color attachments
	rci::ColorAttachmentSPTRS color_attachments = geosketchpad::AttachmentHelper::GetInstance().CreateColorAttachments(
		compiler,
		context,
		w,
		h
	);

	using UpdateDAGHandle = std::function<void(
		const rci::DirectedAcyclicGraphSPTR& graph,
		const rci::CompilerSPTR& compiler,
		const rci::ColorAttachmentSPTRS& color_attachments,
		const rci::DepthStencilAttachmentSPTR& depth_stencil_attachment,
		const uint16_t& w,
		const uint16_t& h,
		std::vector<std::string>& output_messages
		)>;

	// register/update render/compute nodes
	std::unordered_map<std::string, UpdateDAGHandle> demo_node_map;

#ifdef __WIN32__
	init_imgui(window, context);
	auto hook = [&context](const WGPURenderPassEncoder& encoder)
		{
			update_imgui(context, encoder);
		};
	geosketchpad::UIHelper::GetInstance().RegisterUpdateUIHandler(
		graph,
		compiler,
		color_attachments,
		depth_stencil_attachment,
		std::move(hook)
	);
#endif

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// input
		process_input(window);

#ifdef __WIN32__
		geosketchpad::UIHelper::GetInstance().UpdateUI(graph);
#endif

		const auto& itr = demo_node_map.find(selected_item);
		if (itr != demo_node_map.end()) {
			const auto& handler = itr->second;
			handler(graph, compiler, color_attachments, depth_stencil_attachment, w, h, output_messages);
		}

		// re-generate command buffer
		// submit in each frame
		// union compute node + render node
		graph->Build();

		// aux information
		fps = graph->GetFPS();
	}

#ifdef __WIN32__
	release_imgui();
#endif

	glfwDestroyWindow(window);
	glfwTerminate();
}