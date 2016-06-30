#include"user.h"

void user::pIncrease(float money) {
	if (vipPoint >= 0 && vipPoint <= 200)
		vipPoint = vipPoint + (int)money / 5;
	else if (vipPoint > 200 && vipPoint <= 500)
		vipPoint = vipPoint + (int)money / 5 * 3;
	else if (vipPoint > 500)
		vipPoint = vipPoint + (int)money / 5 * 5;
	
}
