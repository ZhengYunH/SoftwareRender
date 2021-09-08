#pragma once
#include <vector>
#include <functional>
#include "../Utils/Math/Vector.h"

namespace ZYH
{
	// FrustumCulling

	namespace ViewPortCulling
	{
		typedef std::vector<Vector3> VectexList;

		void SutherlandHodgman(VectexList&);
		bool IsAllVerticesInside(const VectexList&);
		inline bool IsInside(const Vector3& point) { return !(point.X() > 1.f || point.X() < -1.f || point.Y() > 1.f || point.Y() < -1.f); }

		void ViewPortCulling(VectexList& points)
		{
			SutherlandHodgman(points);
		}

		void SutherlandHodgman(VectexList& points)
		{
			if (IsAllVerticesInside(points))
				return;
			VectexList culledPoints;
			bool isLastPointOutside = false;
			
			std::vector<std::function<bool(const Vector3&)>> judgeFuncs =
			{
				[](const Vector3& point) {return point.X() > -1.f; },
				[](const Vector3& point) {return point.Y() < 1.f; },
				[](const Vector3& point) {return point.X() < 1.f; },
				[](const Vector3& point) {return point.Y() > -1.f; },
			};

			std::vector<std::function<float(const Vector3&, const Vector3&)>> weightFuncs =
			{
				[](const Vector3& s, const Vector3& p) {return (-1.f - s.X()) / (p.X() - s.X()); },
				[](const Vector3& s, const Vector3& p) {return (1.f - s.Y()) / (p.Y() - s.Y()); },
				[](const Vector3& s, const Vector3& p) {return (1.f - s.X()) / (p.X() - s.X()); },
				[](const Vector3& s, const Vector3& p) {return (-1.f - s.Y()) / (p.Y() - s.Y()); },
			};

			for (size_t funcIdx = 0; funcIdx < judgeFuncs.size(); ++funcIdx)
			{
				auto& judgeFunc = judgeFuncs[funcIdx];
				auto& weightFunc = weightFuncs[funcIdx];
				culledPoints.clear();
				auto pointSize = points.size();
				isLastPointOutside = !judgeFunc(points[pointSize - 1]);
				for (size_t pointIdx = 0; pointIdx < pointSize; ++pointIdx)
				{
					auto& currPoint = points[pointIdx];
					if (judgeFunc(currPoint)) // inside
					{
						if (isLastPointOutside)
						{
							isLastPointOutside = false;
							// calculate intersect point
							auto& lastPoint = points[(pointIdx + pointSize - 1) % pointSize];
							float weight = weightFunc(lastPoint, currPoint);
							culledPoints.push_back(lastPoint * (1 - weight) + currPoint * weight);
						}
						culledPoints.push_back(currPoint);
					}
					else
					{
						if (!isLastPointOutside) // last point inside
						{
							isLastPointOutside = true;
							// calculate intersect point
							auto& lastPoint = points[(pointIdx + pointSize - 1) % pointSize];
							float weight = weightFunc(lastPoint, currPoint);
							culledPoints.push_back(lastPoint * (1 - weight) + currPoint * weight);
						}
					}
				}
				points.swap(culledPoints);
			}
		}

		bool IsAllVerticesInside(const VectexList& points)
		{
			for (auto& point : points)
			{
				if (IsInside(point))
					return false;
			}
			return true;
		}
	}
	// BackSideCulling
}
