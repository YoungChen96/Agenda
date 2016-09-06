#include "Date.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"
#include <iostream>
#include <vector>
using namespace std;
void test_Date() {
	int y, m, d, h, min;
	Date date1("1996-05-29/23:07");
	Date date2;
	Date date3(1995, 12, 30, 02, 32);
	cout << Date::dateToString(date1) << endl;
	date2.setMonth(2);
	cout << Date::dateToString(date2) << endl << Date::dateToString(date3) << endl;
	cout << date2.getYear() << endl << date1.getMonth();
	date2 =Date::stringToDate("2002-03-31/23:00");
	date3.setMonth(13);
	
	cout << Date::isValid(date3) << endl << Date::dateToString(date2) << endl;
	cout << (date2 > date3) << endl;
	cout << (date2 <=date3) << (date2 ==date3)<< endl;
	int time_;
	/*cin >> time_;
	string str;
	cin >> str;
	while (time_--) {
		date2 =Date::stringToDate(str);
		cout << Date::dateToString(date2) << endl;
		cin >> str;
	}*/
}
void test_User() {
	cout << endl << "user:\n";
	User user1;
	User user2("chen", "123456", "@qq.com", "110");
	User user3(user2);
	cout << user2.getName() << endl << user2.getPhone() <<endl;
	user1.setPassword("123");
	cout << user1.getPassword() << endl;
}
void test_Meeting() {
	cout << endl << "meeting:\n";
	Meeting m1;
	vector<string> par, par2;
	par.push_back("li");
	par.push_back("Chen");
	Date d1(2001, 2, 20, 3, 4);
	Date d2(d1);
	Meeting m2("ming", par, d1, d2, "sb");
	
	cout << m2.getSponsor() << endl;
	m2.setSponsor("lala");
	Meeting m3(m2);
	cout << m3.getSponsor() << endl;
	par2 =m3.getParticipator();
	par2.push_back("ds");
	m3.setParticipator(par2);
	m3.isParticipator("ds");
	cout << m1.getTitle() << endl;
}

void  test_storage() {
	auto hi =Storage::getInstance();
	// write
	auto usr = hi->queryUser([](const User& t_user)->bool {
		return true;
		});
	auto met = hi->queryMeeting([](const Meeting& _meeting)->bool {
		return true;
	});
	/*User uuu("dasd", "re", "fdg","ewq");
	vector<string> vvv;
	vvv.push_back("chen");
	vvv.push_back("Young");

	Date d1(122,2,3,4,3);
	Date d2(2345,3,4,4,4);
	Meeting nnn("hj",vvv, d1,d2,"bj");
	hi->createMeeting(nnn);
	hi->createUser(uuu);*/


	// read
	
	
	User u1 =usr.front();
	// usr.pop_front();
	cout << u1.getName();
	//u1 =usr.front();
	cout << endl << u1.getPhone() << endl;

	
	Meeting mmm =met.front();
	cout << endl << mmm.getSponsor() << mmm.getTitle() << endl;
	mmm =met.back();
	Date dd =mmm.getStartDate();
	cout << Date::dateToString(dd) << endl;


}
int main() {
	test_User();
	test_Date();
	test_Meeting();
	test_storage();
}