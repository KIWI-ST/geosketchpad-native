#include "AttachmentHelper.h"

namespace geosketchpad
{

	SINGLE_INSTANCE_IMPLEMENT(AttachmentHelper);

	const rci::ColorAttachmentSPTRS AttachmentHelper::CreateColorAttachments(
		const rci::CompilerSPTR& compiler,
		const rci::ContextSPTR& context,
		const uint32_t& w,
		const uint32_t& h)
	{
		// create depth texture attachment
		rci::ColorAttachmentSPTRS color_attachments;

		// create texture to present
		rci::Texture2DDesc swapchain_texture_desc{ "[CreateColorAttachments] swapchain texture" };
		swapchain_texture_desc.width = w;
		swapchain_texture_desc.height = h;
		swapchain_texture_desc.multi_sample_format = rci::MULTI_SAMPLE_FORMAT::k1x;
		swapchain_texture_desc.texture_format = (rci::TEXTURE_FORMAT)context->GetPreferredFormat();
		swapchain_texture_desc.is_attachment = true;
		swapchain_texture_desc.view_formats = std::vector<rci::TEXTURE_FORMAT>{ (rci::TEXTURE_FORMAT)context->GetPreferredFormat() };
		rci::Texture2DSPTR swapchain_texture = compiler->CreateTexture2D(std::move(swapchain_texture_desc));

		// create depth stencil attachment
		rci::ColorAttachmentDesc color_attachment_desc("[CreateColorAttachment] color attachment");
		color_attachment_desc.color_texture = swapchain_texture;
		color_attachment_desc.color_attachment_type = rci::COLOR_ATTACHMENT_TYPE::kSwapChain;
		rci::ColorAttachmentSPTR color_attachment = compiler->CreateColorAttachment(std::move(color_attachment_desc));

		color_attachments.emplace_back(color_attachment);
		return color_attachments;
	}

	const rci::DepthStencilAttachmentSPTR AttachmentHelper::CreateDepthStencilAttachment(
		const rci::CompilerSPTR& compiler,
		const rci::ContextSPTR& context,
		const uint32_t& w,
		const uint32_t& h
	)
	{
		// create depth texture attachment
		rci::Texture2DDesc depth_stencil_texture_desc{ "[CreateDepthStenciAttachment] depth stencil texture" };
		depth_stencil_texture_desc.width = w;
		depth_stencil_texture_desc.height = h;
		depth_stencil_texture_desc.multi_sample_format = rci::MULTI_SAMPLE_FORMAT::k1x;
		depth_stencil_texture_desc.texture_format = (rci::TEXTURE_FORMAT)context->GetDepthTextureFormat();
		depth_stencil_texture_desc.is_attachment = true;
		depth_stencil_texture_desc.view_formats = std::vector<rci::TEXTURE_FORMAT>{ (rci::TEXTURE_FORMAT)context->GetDepthTextureFormat() };
		rci::Texture2DSPTR depth_stencil_texture = compiler->CreateTexture2D(std::move(depth_stencil_texture_desc));

		// create depth stencil attachment
		rci::DepthStencilAttachmentDesc depth_stencil_attachment_desc("[CreateDepthStencilAttachment] depth_stencil_attachment");
		depth_stencil_attachment_desc.depth_stencil_texture = depth_stencil_texture;
		depth_stencil_attachment_desc.depth_stencil_mode = rci::DEPTH_STENCIL_FORMAT::kDepthLess;
		rci::DepthStencilAttachmentSPTR depth_stencil_attachment = compiler->CreateDepthStencilAttachment(std::move(depth_stencil_attachment_desc));

		return depth_stencil_attachment;
	}

}