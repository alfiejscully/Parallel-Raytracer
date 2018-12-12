#ifndef _RAYHITLIST_H_
#define _RAYHITLIST_H_
// System includes
#include<vector>
#include<memory>

// Included for inheritance
#include "RayHitTable.h"

class Ray;
struct RayHit;

class RayHitList : public RayHitTable
{
private:
	int m_size;

	RayHitTable **m_list;

public:
	RayHitList() {};
	RayHitList(RayHitTable **_i, int _size);

	virtual bool Hit(const std::shared_ptr<Ray> _ray, float _min, float _max, RayHit& _rayHit) const;
};
#endif