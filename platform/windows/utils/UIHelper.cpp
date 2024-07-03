#include "UIHelper.h"

namespace geosketchpad
{
	SINGLE_INSTANCE_IMPLEMENT(UIHelper);

	void UIHelper::RegisterUpdateUIHandler(
		const rci::DirectedAcyclicGraphSPTR& graph_sp,
		const rci::CompilerSPTR& compiler,
		const rci::ColorAttachmentSPTRS& color_attachments,
		const rci::DepthStencilAttachmentSPTR& depth_stencil_attachment,
		rci::RenderHandle&& handler
	)
	{
        std::string vertex_code = R"(
@vertex
fn vs_main(@location(0) position: vec2f) -> @builtin(position) vec4<f32> {
    return vec4f(position, 1.0, 1.0);
}
    )";

        std::string fragment_code = R"(
@fragment
fn fs_main() -> @location(0) vec4f {
    return vec4f(1.0, 1.0, 1.0, 1.0);
}
    )";

        rci::RenderNodeDesc desc{};

        desc.vertex_code = vertex_code;
        desc.fragment_code = fragment_code;
        desc.color_attachments = color_attachments;
        desc.depth_stencil_attachment = depth_stencil_attachment;

        // assign attributes
        desc.attributes = std::make_shared<rci::Props>();
        desc.attributes->Append("position", std::vector<float> {
            -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f
        });

        // enable depth stencil mode
        desc.dispatch = std::make_shared<rci::DispatchRenderProp>(6);

        // create command
        update_ui_node_ = compiler->CompileRenderNode(std::move(desc));

#ifdef __WIN32__
        update_ui_node_->Hook(std::move(handler));
#endif 
	}

    void UIHelper::UpdateUI(const rci::DirectedAcyclicGraphSPTR& graph_sp)
    {
        if (update_ui_node_) {
            graph_sp->AddNode(update_ui_node_);
        }
    }

}