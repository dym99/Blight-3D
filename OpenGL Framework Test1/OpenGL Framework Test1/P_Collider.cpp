#include "P_Collider.h"

P_Collider::P_Collider(P_Collider_Type _t, float _h, float _w, float _d)
{
	P_type = _t;
	P_height = _h;
	P_width = _w;
	P_depth = _d;

	if (_t == SPHERE)
		P_maxSize = _h;
	else if (_t == BOX)
	{
		float h2 = _h / 2;
		float w2 = _w / 2;
		float d2 = _d / 2;
		P_maxSize = sqrt((h2 * h2) + (w2 * w2) + (d2 * d2));
	}
	else
		P_maxSize = _h;
}
