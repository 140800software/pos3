#pragma once
#include<string>
using namespace std;
class user {
private:
	string userPoint;	
	string isVip="false"; 
	int vipPoint=0;//会议积分
public:
	string name;
	user*next=NULL;
	user(string userP,string na,string isV) {
		userPoint = userP;
		name = na;
		isVip = isV;
	}
	string getName() {
		return name;
	}
	string getIsVip() {
		return isVip;//返回是否是会员
	}
	int getVipPoint() {
		return vipPoint;
	}
	void pIncrease(float );

};
