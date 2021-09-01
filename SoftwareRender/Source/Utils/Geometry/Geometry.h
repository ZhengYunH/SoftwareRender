#pragma once
#include "../Math/Vector.h"
#include "../Math/Matrix.h"

#define	ABSTRACT __declspec(novtable)

namespace ZYH
{
	class Renderer;

	enum class RENDER_MODE
	{
		SOLID,
		WIRE_FRAME
	};

	struct Vertex
	{
		Vector3 point;
		Vector4 color;
	};

	class RenderObject
	{
	public:
		RenderObject(Renderer* render);
		virtual void Draw(Renderer* render, RENDER_MODE renderType) = 0;
	};

	class PrimitivesRenderObject : RenderObject
	{
	public:
		PrimitivesRenderObject(Renderer* render, const std::vector<Vector3>& vertices, const std::vector<uint32_t>& indexs)
			: RenderObject(render)
			, mVertices_(vertices)
			, mIndexs_(indexs)
		{}

		virtual void Draw(Renderer* render, RENDER_MODE renderType=RENDER_MODE::WIRE_FRAME) override;

	private:
		std::vector<Vector3>	mVertices_;
		std::vector<uint32_t>	mIndexs_;
	};
}