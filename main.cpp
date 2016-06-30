#include<iostream>
#include<fstream>
#include <iomanip>
#include<time.h>
#include"acount good.h"
#include"user.h"
using namespace std;

int main() {
	user* getUserList();
	link* getFinalList();
	link*head = getFinalList();
	link*p = head;	
	
	ifstream ifile("商品列表文件.txt");
	string jud;
	string nam;
	while (ifile >> jud) {
		if (jud == "user:") {
			ifile >> nam;
		}			
	}
	user *uhead=getUserList();
	user*u=uhead;
	bool us;
	int c;
	while (u) {
		if (u->getName() == nam) {
			if (u->getIsVip() == "true") {
				us = true;c = u->getVipPoint();
			}
				
			else
				us = false;
			break;
		}
		u = u->next;
	}
	cout << "***商店购物清单***" << endl;
	if (us) {
		cout << "会员编号：" << nam << "\t会员积分：" << c << endl;
		cout << "----------------------" << endl;
	}
		
	cout << "打印时间：";
	struct tm newtime;
	char am_pm[] = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	if (newtime.tm_hour > 12)        // Set up extension. 
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	if (newtime.tm_hour > 12)        // Convert from 24-hour 
		newtime.tm_hour -= 12;    // to 12-hour clock. 
	if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.
		newtime.tm_hour = 12;

	// Convert to an ASCII representation. 
	err = asctime_s(timebuf, 26, &newtime);
	if (err)
	{
		printf("Invalid argument to asctime_s.");
		exit(1);
	}
	printf("%.19s %s\n", timebuf, am_pm);
	cout << "----------------------" << endl;
	acountGood*pt;	
	bool s=false;
	float total=0,sub=0;
	int count;
	string name;
	int i=0;
	while(p) {
		pt = p->item;//指针pt初始化
		if (pt->getPromotion() == 1&&pt->getCount()!=0) {
			s = true;
			sub =sub+ pt->getDecreaseMoney();
			name = pt->getName();
			count = pt->getDecreaseCount();

		}
		if (pt->getDiscount() != 1 || pt->getVipDiscount()) {
			sub = sub + (1 - pt->getDiscount()*pt->getVipDiscount())*pt->getPrice()*pt->getCount();
		}
		cout << "名称：" << pt->getName() << ",数量：" << pt->getCount() << pt->getUnit() << ",单价：" << setprecision(2) << std::fixed<< pt->getPrice() << ",小计：" << pt->intatal(u->getIsVip())<<endl;
		total = total + pt->intatal(u->getIsVip());
		p=p->next;
	}
	p = head;	
	if (s) {
		cout << "----------------------" << endl;
		cout << "挥泪赠送商品：" << endl;

		while (p) {
			if ((p->item)->getPromotion()) {
				cout << "名称：" << (p->item)->getName() << ",数量：" << (p->item)->getDecreaseCount() << endl;
			}
			p = p->next;
		}
	}
	cout << "----------------------" << endl;
	cout << "总计："<<total << endl;
	if(sub!=0)
		cout << "节省：" << sub << endl;
	cout << "**********************" << endl;
	while (head->next != NULL)
	{
		p = head->next;
		head->next = p->next;
		delete p->item;
		delete p;
	}
	p = head;
	head = NULL;
	delete p;
	while (uhead->next != NULL)
	{
		u = uhead->next;
		uhead->next = u->next;
		delete u;
	}
	u = uhead;
	uhead = NULL;
	delete u;
	system("pause");
	


	return 0;
}

link* getList() {
	string jud;
	link*head = NULL;
	link*p = NULL;

	ifstream ifile("商品索引文件.txt");
	if (ifile >> jud) {

		string barcode;
		while (ifile >> barcode) {
			
			string  name, unit;
			bool promotion = 0;
			float price, discount = 1,vipDiscount=1;
		

			while (ifile >> jud) {
				if (jud == "name:") {
					ifile >> name;
				
					continue;
				}
				else if (jud == "unit:") {
					ifile >> unit;
				
					continue;
				}
				else if (jud == "price:") {
					ifile >> price;
					
					continue;
				}
				else if (jud == "promotion:") {
					string a;

					ifile >> a;
					if (a == "true")
						promotion = 1;
					
					
					continue;
				}
				else if (jud == "discount:") {
					ifile >> discount;
					
					continue;
				}
				else if (jud == "vipDiscount:") {
					ifile >> vipDiscount;

					continue;
				}
				else if (jud == "},") {//生成节点
					if (head == NULL) {
						link*ptr = new link(barcode);
						ptr->item= new acountGood(name, unit, price, discount,vipDiscount, promotion);
			
						head = ptr;
						p = head;
						
						break;

					}
					else {
						link*ptr = new link(barcode);
						ptr->item = new acountGood(name, unit, price, discount,vipDiscount, promotion);
						p->next = ptr;
						p = p->next;
						
						break;

					}
				}

			}


		}

	}
	ifile.close();
	return head;

}
link* getFinalList() {
	link* getList();
	link* head = getList();
	link* p = head;
	link*fhead=NULL;
	link*pt = fhead;
	string jud;
	ifstream ifile("商品列表文件.txt");
	
	while (ifile >> jud) {
		
		p = head;
	int judg = 1;
		while (p) {
			if (p->barcode == jud) {
				
				if (fhead == NULL) {
					
					link*ptr = new link(p->barcode);
					fhead = ptr;
					pt = fhead;
					acountGood*pw = p->item;
					pt->item = new acountGood(pw->getName(), pw->getUnit(), pw->getPrice(), pw->getDiscount(), pw->getVipDiscount(), pw->getPromotion());

					continue;
				}
				pt = fhead;
			
				while (pt) {
					
					if (pt->barcode == jud) {
						acountGood*pw = pt->item;
						pw->increase();
						judg = 0;
					
						break;

					}
					else
						pt = pt->next;
				}
				
				if (judg) {
					pt = fhead;
					while (pt->next)
						pt = pt->next;
					link*ptr = new link(p->barcode);
					acountGood*pw = p->item;
					ptr->item = new acountGood(pw->getName(), pw->getUnit(), pw->getPrice(), pw->getDiscount(), pw->getVipDiscount(), pw->getPromotion());
					pt->next = ptr;
					(pt->next)->item = ptr->item;
					pt = pt->next;
					(pt->item)->increase();
					
					


				}
			}
		
				p = p->next;
		}

	}
	ifile.close();
	while (head->next != NULL)
	{
		p = head->next;
		head->next = p->next;
		delete p->item;
		delete p;
	}
	p = head;
	head = NULL;
	delete p;
		
	return fhead;
}
user* getUserList() {
	ifstream ifile("user.txt");
	user*head = NULL;
	user*p=NULL;
	string jud;
	if (ifile >> jud) {
		
		string userPoint;
		while (ifile >>userPoint ) {

			string  name, isVip;
			while (ifile >> jud) {
				if (jud == "name:") {
					ifile >> name;

					continue;
				}
				else if (jud == "isVip:") {
					ifile >> isVip;

					continue;
				}
			
				
				else if (jud == "},") {//生成节点
					if (head == NULL) {
						
						user*ptr = new user(userPoint, name, isVip);
						head = ptr;
						p = head;
						break;

					}
					else {
						user*ptr = new user(userPoint, name, isVip);
						p->next = ptr;
						p = p->next;
						break;

					}

				}

			}

		}

	}

	return head;
}
