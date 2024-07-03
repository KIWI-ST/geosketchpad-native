#pragma once

#include <rci.h>

namespace geosketchpad
{

	class AttachmentHelper
	{
		SINGLE_INSTANCE_DECLARE(AttachmentHelper)

	public:

		/**
		* create color attachments 
		*/
		const rci::ColorAttachmentSPTRS CreateColorAttachments(
			const rci::CompilerSPTR& compiler,
			const rci::ContextSPTR& context,
			const uint32_t& w,
			const uint32_t& h
		);

		/**
		* create depth stencil attachment
		*/
		const rci::DepthStencilAttachmentSPTR CreateDepthStencilAttachment(
			const rci::CompilerSPTR& compiler,
			const rci::ContextSPTR& context,
			const uint32_t& w,
			const uint32_t& h
		);

	};

}