#include "Geometry.h"
#include "../../Render/Renderer.h"

namespace ZYH
{
	RenderObject::RenderObject(Renderer* render)
	{
		render->AddRenderObject(this);
	}
	void PrimitivesRenderObject::Draw(Renderer* render, RENDER_MODE renderType)
	{
		auto& camera = render->GetCamera();
		auto& mat = camera.WorldToProj();
		if (renderType == RENDER_MODE::SOLID)
		{
			assert(0);
		}
		else if (renderType == RENDER_MODE::WIRE_FRAME)
		{
			size_t indexSize = mIndexs_.size();
			ZRGB color(255, 0, 0);
			for (size_t idx = 0; idx < indexSize - 2; ++idx)
			{
				auto vertex1 = mat * mVertices_[idx];
				auto vertex2 = mat * mVertices_[(idx + 1)];
				auto vertex3 = mat * mVertices_[(idx + 2)];

				render->DrawLine(render->GetScreenPoint(vertex1), render->GetScreenPoint(vertex2), color);
				render->DrawLine(render->GetScreenPoint(vertex2), render->GetScreenPoint(vertex3), color);
				render->DrawLine(render->GetScreenPoint(vertex3), render->GetScreenPoint(vertex1), color);
			}
		}
		else
		{
			assert(0);
		}
	}
}