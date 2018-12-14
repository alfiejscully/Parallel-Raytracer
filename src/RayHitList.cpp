#include "RayHitList.h"
#include "RayHitAble.h"
#include "Ray.h"

RayHitList::RayHitList(RayHitAble ** _i, int _size)
{
	m_list = _i;
	m_size = _size;
}

bool RayHitList::Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit & _rayHit) const
{
	RayHit hit;
	bool hitAnything = false;
	double closest = _max;
	for (int i = 0; i < m_size; i++)
	{
		if (m_list[i]->Hit(_ray, _min, closest, hit))
		{
			hitAnything = true;
			closest = hit.m_position;
			_rayHit = hit;
		}
	}
	return hitAnything;
}
