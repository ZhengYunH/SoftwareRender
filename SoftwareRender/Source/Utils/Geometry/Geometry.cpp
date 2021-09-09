#include "Geometry.h"
#include "../../Render/Renderer.h"
#include "../../Render/Culler.h"

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
				vertex1 = Vector3(vertex1.X() / vertex1.Z(), vertex1.Y() / vertex1.Z(), 1.f);
				vertex2 = Vector3(vertex2.X() / vertex2.Z(), vertex2.Y() / vertex2.Z(), 1.f);
				vertex3 = Vector3(vertex3.X() / vertex3.Z(), vertex3.Y() / vertex3.Z(), 1.f);
				
				ViewPortCulling::VectexList vecList = { vertex1 , vertex2, vertex3 };
				ViewPortCulling::SutherlandHodgman(vecList);
				for (size_t vecIdx = 0; vecIdx < vecList.size(); ++vecIdx)
				{
					auto& vertex1 = vecList[vecIdx];
					auto& vertex2 = vecList[(vecIdx + 1) % vecList.size()];
					render->DrawLine(render->GetScreenPoint(vertex1), render->GetScreenPoint(vertex2), color);
				}
			}
		}
		else
		{
			assert(0);
		}
	}
}