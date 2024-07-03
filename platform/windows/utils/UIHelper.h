#pragma once

#include <rci.h>

namespace geosketchpad
{

	class UIHelper
	{
		SINGLE_INSTANCE_DECLARE(UIHelper)

	public:

		/**
		* register update UI 
		*/
		void RegisterUpdateUIHandler(
			const rci::DirectedAcyclicGraphSPTR& graph_sp,
			const rci::CompilerSPTR& compiler,
			const rci::ColorAttachmentSPTRS& color_attachments,
			const rci::DepthStencilAttachmentSPTR& depth_stencil_attachment,
			rci::RenderHandle&& handler
		);

		/**
		*/
		void UpdateUI(const rci::DirectedAcyclicGraphSPTR& graph_sp);

	private:
		rci::RenderNodeSPTR update_ui_node_ = nullptr;
	};

}