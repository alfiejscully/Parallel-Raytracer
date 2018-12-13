#ifndef _RAYHITLIST_H_
#define _RAYHITLIST_H_
// System includes
#include<vector>
#include<memory>

// Included for inheritance
#include "RayHitAble.h"

class Ray;
struct RayHit;

class RayHitList : public RayHitAble
{
private:
	int m_size;

	RayHitAble **m_list;

public:
	RayHitList() {};
	RayHitList(RayHitAble **_i, int _size);

	virtual bool Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit& _rayHit) const;
};
#endif