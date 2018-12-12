#include "RayHitList.h"
#include "RayHitTable.h"
#include "Ray.h"

RayHitList::RayHitList(RayHitTable ** _i, int _size)
{
	m_list = _i;
	m_size = _size;
}

bool RayHitList::Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit & _rayHit) const
{
	RayHit tempHit;
	bool anythingHit = false;
	double closest = _max;
	for (int i = 0; i < m_size; i++)
	{
		if (m_list[i]->Hit(_ray, _min, closest, tempHit))
		{
			anythingHit = true;
			closest = tempHit.m_position;
			_rayHit = tempHit;
		}
	}
	return anythingHit;
}
