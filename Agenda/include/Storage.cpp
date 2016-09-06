#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

Storage::Storage() {
	readFromFile();
}

bool Storage::readFromFile(void) {
	using namespace std;
	ifstream m_file(Path::meetingPath)
	ifstream u_file(Path::userPath);
	if (m_file && u_file) {
		string line;
		string u_line, m_line;
		getline(u_file, line);
		while (getline(u_file, u_line)) {
			istringsteam sin(u_line);
			string subs;
			vector<string> str;
			while (getline(sin, subs, ',')) {
				str.push_back(subs);
			}
			User user;
			user.setName(str[0]);
			user.setPassword(str[1]);
			user.setEmail(str[2]);
			user.setPhone(str[3]);
			m_userList.push_front(user);
		}

		getline(m_file, line);
		while (getline(m_file, m_line)) {
			istringsteam sin(m_line);
			string subs;
			vector<string> str;
			while (getline(sin, subs, ',')) {
				str.push_back(subs);
			}
			Meeting meeting;
			meeting.setSponser(str[0]);
			std::vector<std::string> vv;
			std::string cut;
			for (int i =0; i <str[1].length(); ++i) {
				if (str[1][i] != '&') {cut +=str[1][i];}
				else {vv.push_back(cut);
					cut ="";
				}
			}
			vv.push_back(cut);
			meeting.setParticipator(vv);
			Date d1(str[2]);
			Date d2(str[3]);
			meeting.setStartDate(d1);
			meeting.setEndDate(d2);
			meeting.setTitle(str[4]);
			m_meetingList.push_front(meeting);
		}
		return true;
	}
	return false;
}
bool Storage::writeToFile(void) {
	using namespace std;
	ofstream m_file(Path::meetingPath);
	ofstream u_file(Path::userPath);
	if (m_file && u_file) {
		m_file << "\"sponser\",\"participator\",\"sdate\",\"edate\",\"title\"\n";
		int m_len =m_meetingList.size();
		for (int i =0; i <len; ++i) {
			m_file << m_meetingList.front().getSponsor() << ",";
			int j =0;
			vector<string> ppp =m_meetingList.front().getParticipators();
			for (j =0; j <ppp.size() -1; ++j) {
				m_file << ppp[j] << "&";
			}
			m_file << ppp[j] << ",";
			m_file << m_meetingList.front().getStartDate() << ",";
			m_file << m_meetingList.front().getEndDate() << ",";
			m_file << m_meetingList.front().getTitle() << endl;
			m_meetingList.pop_front();
		}
		u_file << "\"name\",\"password\",\"email\",\"phone\"\n";
		int u_len =m_userList.size();
		for (int i =0; i <len; ++i) {
			u_file << m_userList.front().getName() << ",";
			u_file << m_userList.front().getPassword() << ",";
			u_file << m_userList.front().getEmail() << ",";
			u_file << m_userList.front().getPhone() << endl;
			m_userList.pop_front();
		}
		m_file.close();
		u_file.close();
		return true;
	}
	return false;
}

std::shared_ptr<Storage> Storage::getInstance() {
	if (m_instance ==NULL) {
		m_instance =new Storage;
	}
	return m_instance;
}

Storage::~Storage() {
	writeToFile();
}

void Storage::createUser(const User & _user) {
	m_userList.push_front(_user);
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	std::list<User> result;
	std::list<User>::iterator ptr =m_userList.begin();
	for (; ptr !=m_userList.end(); ++ptr) {
		if (filter(*ptr)) result.push_front(*ptr);
	}
	return result;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int sum =0;
	std::list<User>::iterator ptr =m_userList.begin();
	while(ptr !=m_userList.end()) {
		if (filter(*ptr)) {
			switcher(*ptr);
			++sum;
		}
		++ptr;
	}
	return sum;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
	int sum =0;
	std::list<User>::iterator ptr =m_userList.begin();
	while(ptr !=m_userList.end()) {
		bool flag =false;
		if (filter(*ptr)) {
			m_userList.erase(ptr);
			flag =true;
			++sum;
		}
		if (!flag) ++ptr;
	}
	return sum;
}

void Storage::createMeeting(const Meeting & _meeting) {
	m_meetingList.push_front(_meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	std::list<Meeting> result;
	std::list<Meeting>::iterator ptr =m_meetingList.begin();
	for (; ptr !=m_meetingList.end(); ++ptr) {
		if (filter(*ptr)) result.push_front(*ptr);
	}
	return result;
}

int updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int sum =0;
	std::list<Meeting>::iterator ptr =m_meetingList.begin();
	while(ptr !=m_meetingList.end()) {
		if (filter(*ptr)) {
			switcher(*ptr);
			++sum;
		}
		++ptr;
	}
	return sum;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	int sum =0;
	std::list<Meeting>::iterator ptr =m_meetingList.begin();
	while(ptr !=m_meetingList.end()) {
		bool flag =false;
		if (filter(*ptr)) {
			m_meetingList.erase(ptr);
			flag =true;
			++sum;
		}
		if (!flag) ++ptr;
	}
	return sum;
}

bool Storage::sync(void) {
	writeToFile();
}