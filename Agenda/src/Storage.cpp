#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

Storage::Storage() {
	readFromFile();
	m_dirty =false;
}

bool del(std::string& str) {
	int len =str.length();
	if (len <3) return false;
	str =str.substr(1, len -2);
	return true;
}
bool Storage::readFromFile(void) {
	using namespace std;
	m_dirty =false;
	ifstream u_file(Path::userPath);
	if (!u_file.good()) return false;

		//string line;
	/*while (!u_file.eof()) {
		string u_line;
		u_file >> u_line;
		if (!u_line.length()) break;
		string sub;
		vector<string> str;
		for (int i =0; i <u_line.length(); ++i) {
			if (u_line[i] !='\"') {
				sub +=u_line[i];
			} else {
				str.push_back(sub);
				sub ="";
				i =i +1;
			}
		}
	}*/
		string u_line;

		//getline(u_file, line);
		while (getline(u_file, u_line)) {
			if (u_line =="") break;   // try
			istringstream _sin(u_line);
			string subs;
			vector<string> str;
			while (getline(_sin, subs, ',')) {
				str.push_back(subs);
			}
			if (str.size() <4) return false;
			User user;
			if (false ==(del(str[0]) && del(str[1]) && del(str[2]) && del(str[3]))) return false;
			user.setName(str[0]);
			user.setPassword(str[1]);
			user.setEmail(str[2]);
			user.setPhone(str[3]);
			m_userList.push_back(user);
		}

		u_file.close();


	ifstream m_file(Path::meetingPath);
	if (!m_file.good()) return false;
	string m_line;
		//getline(m_file, line);
		while (getline(m_file, m_line)) {
			if (m_line == "") break;
			istringstream _sin(m_line);
			string subs;
			vector<string> str;
			while (getline(_sin, subs, ',')) {
				str.push_back(subs);
			}
			Meeting meeting;

			if (false ==del(str[0])) return false;
			meeting.setSponsor(str[0]);

			std::vector<std::string> vv;
			std::string cut ="";
			if (false ==del(str[1])) return false;
			string part_str =str[1];
			for (int i =0; i <part_str.length(); ++i) {
				if (part_str[i] != '&') {cut +=part_str[i];}
				else {vv.push_back(cut);
					cut ="";
				}
			}
			vv.push_back(cut);
			meeting.setParticipator(vv);

			if (del(str[2]) == false) return false;
			Date d1(str[2]);
			if (false ==del(str[3])) return false;
			Date d2(str[3]);
			meeting.setStartDate(d1);
			meeting.setEndDate(d2);
			if (false ==del(str[4])) return false;
			meeting.setTitle(str[4]);
			m_meetingList.push_back(meeting);
		}
		m_file.close();
		return true;
}

bool Storage::writeToFile(void) {
	using namespace std;
	
	ofstream u_file(Path::userPath, ios::trunc);
	ofstream m_file(Path::meetingPath, ios::trunc);
	if (!m_file.good()) return false;

		//m_file << "\"sponser\",\"participator\",\"sdate\",\"edate\",\"title\"\n";
		//int len =m_meetingList.size();
		for (auto iter =m_meetingList.begin(); iter !=m_meetingList.end(); ++iter) {
			//auto _fro =m_meetingList.front();
			m_file << "\"" <<iter->getSponsor() << "\"" << ",";
			int j =0;
			
			vector<string> ppp =iter->getParticipator();
			m_file << "\"";
			for (j =0; j <ppp.size() -1; ++j) {
				m_file << ppp[j] << "&";
			}
			m_file << ppp[j] << "\"" << ",";
			m_file << "\"" << Date::dateToString(iter->getStartDate()) << "\"" << ",";
			m_file << "\"" << Date::dateToString(iter->getEndDate()) << "\"" << ",";
			m_file << "\"" << iter->getTitle() << "\"" << endl;
			//m_meetingList.pop_front();
		}
		m_file.close();

		if (!u_file.good()) return false;
		//u_file << "\"name\",\"password\",\"email\",\"phone\"\n";

		for (auto ptr =m_userList.begin(); ptr !=m_userList.end(); ++ptr) {
			//auto _fro =m_userList.front();
			u_file <<"\"" << ptr->getName() <<"\"" << ",";
			u_file <<"\"" << ptr->getPassword() <<"\"" << ",";
			u_file <<"\"" << ptr->getEmail() <<"\"" << ",";
			u_file <<"\"" << ptr->getPhone() <<"\"" << endl;
			//m_userList.pop_front();
		}
		u_file.close();
		m_dirty =false;
		return true;
}


std::shared_ptr<Storage> Storage::m_instance =nullptr;
std::shared_ptr<Storage> Storage::getInstance() {
	if (m_instance ==NULL) {
		m_instance = std::shared_ptr<Storage>(new Storage());
	}
	return m_instance;
}

Storage::~Storage() {
	if (m_dirty)
	writeToFile();
}

void Storage::createUser(const User & _user) {
	m_userList.push_front(_user);
	m_dirty =true;
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	std::list<User> result;
	auto ptr =m_userList.begin();
	for (; ptr !=m_userList.end(); ++ptr) {
		if (filter(*ptr)) result.push_front(*ptr);
	}
	return result;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int sum =0;
	auto ptr =m_userList.begin();
	while(ptr !=m_userList.end()) {
		if (filter(*ptr)) {
			switcher(*ptr);
			++sum;
		}
		++ptr;
	}
	return sum;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) { // delete meeting
	int sum =0;
	std::list<User>::iterator ptr =m_userList.begin();
	while(ptr !=m_userList.end()) {
		if (filter(*ptr)) {
			ptr = m_userList.erase(ptr);   // check it
			++sum;
			m_dirty =true;
		}
		++ptr;
	}
	//if (!sum) m_dirty =true;
	return sum;
}

void Storage::createMeeting(const Meeting & _meeting) {
	m_meetingList.push_front(_meeting);
	m_dirty =true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	std::list<Meeting> result;
	auto ptr =m_meetingList.begin();
	for (; ptr !=m_meetingList.end(); ++ptr) {
		if (filter(*ptr)) result.push_front(*ptr);
	}
	return result;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int sum =0;
	std::list<Meeting>::iterator ptr;
	ptr =m_meetingList.begin();
	while(ptr !=m_meetingList.end()) {
		if (filter(*ptr)) {
			switcher(*ptr);
			++sum;
			m_dirty =true;
		}
		++ptr;
	}
	return sum;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int sum =0;
	std::list<Meeting>::iterator ptr =m_meetingList.begin();
	while(ptr !=m_meetingList.end()) {
		if (filter(*ptr)) {
			ptr =m_meetingList.erase(ptr);
			m_dirty =true;
			++sum;
		}
		++ptr;
	}
	return sum;
}

bool Storage::sync(void) {
	if (m_dirty)
	writeToFile();
}