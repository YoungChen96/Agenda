#include "AgendaUI.hpp"
#include <iostream>
#include <iomanip>
const int LONG_W =20;
const int SHORT_W =8;


#define setflags setiosflags
bool flag =true;
AgendaUI::AgendaUI() {
	m_userName ="";
	m_userPassword ="";
	//m_agendaService =new AgendaService;
}
using namespace std;
void AgendaUI::OperationLoop() {  // two operations
	string act;
	if ("" == m_userName) startAgenda();
	else {
			cout << "\n-------------------------Agenda----------------------------\n";
			cout << "Welcome, " << m_userName << "! Please enter your action:\n";
			cout << "o    - log out Agenda\n";
			cout << "dc  - delete Agenda account\n";
			cout << "lu   - list all Agenda user\n";
			cout << "cm   - create a meeting\n";
			cout << "lam  - list all meeting\n";
			cout << "las  - list all sponsor\n";
			cout << "lap  - list all participate meeting\n";
			cout << "qm   - query meeting by title\n";
			cout << "qt   - query meeting by time interval\n";
			cout << "dm   - delete meeting by title\n";
			cout << "da   - delete all meetings\n";
			//cout << "q    - quit Agenda\n";
			cout << "------------------------------------------------------------\n\n";
			cout << endl << "Agenda@" << m_userName << " : # ";
	}
	act =getOperation();
	executeOperation(act);
	/*while (flag)
	{
		if ("" == m_userName) {
			cout << "-------------------------Agenda----------------------------\n";
			cout << "Please enter your action :\n";
			cout << "l    - log in Agenda by user name and password\n";
			cout << "r    - register an Agenda account\n";
			cout << "q    - quit Agenda\n";
			cout << "-----------------------------------------------------------\n";
			cout << "\nAgenda : ~$ ";
			act =getOperation();
			executeOperation(act);
		}
		else if ("" !=m_userName) {
			cout << "-------------------------Agenda----------------------------\n";
			cout << "Welcome, " << m_userName << "! Please enter your action:\n";
			cout << "o    - log out Agenda\n";
			cout << "dc  - delete Agenda account\n";
			cout << "lu   - list all Agenda user\n";
			cout << "cm   - create a meeting\n";
			cout << "lam  - list all meeting\n";
			cout << "las  - list all sponsor\n";
			cout << "lap  - list all participate meeting\n";
			cout << "qm   - query meeting by title\n";
			cout << "qt   - query meeting by time interval\n";
			cout << "dm   - delete meeting by title\n";
			cout << "da   - delete all meetings\n";
			cout << "------------------------------------------------------------\n\n";
			cout << endl << "Agenda@" << m_userName << " : # ";
			act =getOperation();
			executeOperation(act);
		}
	}*/
}

void AgendaUI::startAgenda() {
			cout << "\n-------------------------Agenda----------------------------\n";
			cout << "Please enter your action :\n";
			cout << "l    - log in Agenda by user name and password\n";
			cout << "r    - register an Agenda account\n";
			cout << "q    - quit Agenda\n";
			cout << "-----------------------------------------------------------\n";
			cout << "\nAgenda : ~$ ";
}

string AgendaUI::getOperation() {
	string act;
	cin >> act;
	return act;
}


bool AgendaUI::executeOperation(string act) {
	
		if ("" !=m_userName) {
				if (act == "o") userLogOut();
				if (act == "dc") deleteUser();	
				if (act == "lu") listAllUsers();
				if (act == "cm") createMeeting();
				if (act == "lam") listAllMeetings();
				if (act == "las") listAllSponsorMeetings();
				if (act == "lap") listAllParticipateMeetings();
				if (act == "qm") queryMeetingByTitle();
				if (act == "qt") queryMeetingByTimeInterval();
				if (act == "dm") deleteMeetingByTitle();
				if (act == "da") deleteAllMeetings();
				else {
					cout << "please enter the correct action :\nAgenda : ~$ ";
					cin.clear();
					cin.sync();
					//OperationLoop();
					cin >> act;
					executeOperation(act);
				}
				
		}	
		else {
				if (act == "l") userLogIn();
				else if ("r" ==act) userRegister();
				else if ("q" == act) quitAgenda();
				else {
					cout << "please enter the correct action :\nAgenda : ~$ ";
					cin.clear();
					cin.sync();
					//OperationLoop();
					cin >> act;
					executeOperation(act);
				}
		}
		//OperationLoop();
}

void AgendaUI::userLogIn() {
	//cout << "-----------------------------Agenda--------------------------------\n";
	
		cout << "[log in] [user name] [password]\n";
		cout << "[log in] ";
		string user_n, user_p;
		cin >> user_n;
		cin >> user_p;
		if (m_agendaService.userLogIn(user_n, user_p)) {
			m_userName =user_n;
			m_userPassword =user_p;
			//OperationLoop();
		} else {
			cout << "[error] log in fail!\nBack to Agenda\n"; 
			//OperationLoop();
		}
	
	OperationLoop();
}

void AgendaUI::userRegister() {
	
		cout << "[register] [user name] [password] [email] [phone]\n";
		cout << "[register] ";
		string name, pass, email, phone;
		cin >> name >> pass >> email >> phone;
		if (m_agendaService.userRegister(name, pass, email, phone)) {
			cout << "[register] succeed!\n";
		} else {
			cout << "[error] register fail!\n";
		}
	
	OperationLoop();
}

void AgendaUI::quitAgenda() {
	//~AgendaService();
	m_agendaService.quitAgenda();
	exit(0);
	flag =false;
}

void AgendaUI::userLogOut() {

	m_userName ="";
	m_userPassword ="";

	OperationLoop();
}

void AgendaUI::deleteUser() {
	
		if (m_agendaService.deleteUser(m_userName, m_userPassword))
		{
			m_userName ="";
			m_userPassword ="";
		}

		OperationLoop();
}

void AgendaUI::listAllUsers() { // not
	auto vec =m_agendaService.listAllUsers();
	cout << "\n[list all users]\n";
	cout << endl << setflags(ios::left) << setw(SHORT_W) << "name";
	cout << setflags(ios::left) << setw(LONG_W) << "email";
	cout << setflags(ios::left) << "phone\n\n";
	for (auto iter =vec.begin(); iter !=vec.end(); ++iter) {
		cout << left;
		cout << setflags(ios::left) << setw(SHORT_W) << setflags(ios::left) << iter->getName();
		cout << setflags(ios::left) << setw(LONG_W) << setflags(ios::left) << iter->getEmail();
		cout << setflags(ios::left) << iter->getPhone() << endl;
	}
	OperationLoop();
}

void AgendaUI::createMeeting() {
	cout << "[create meeting] [the number of participators]\n";
	cout << "[create meeting] ";
	int num;
	cin >> num;  
	if (num >0) {
		vector<string> vec;
		for (int i=1; i <=num; ++i) {
			string part;
			cout << "[create meeting] [please enter the participator " << i << "] \n";
			cout << "[create meeting] ";
			cin >> part;
			vec.push_back(part);
		}
		cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(the same)]\n";
		cout << "[create meeting] ";
		string _title, s_date, e_date;
		cin >> _title >> s_date >> e_date;
		if (m_agendaService.createMeeting(m_userName, _title, s_date, e_date, vec)) {
			cout << "[create meeting] succeed!\n";
		} else {
			cout << "[create meeting] error!\nBack to Agenda\n";
		} 
	}
	OperationLoop();

}

void AgendaUI::listAllMeetings() {
	cout << "[list all meetings]\n\n";
	cout << setflags(ios::left) << setw(SHORT_W) << "title";
	cout << setflags(ios::left) << setw(SHORT_W) << "sponsor";
	cout << setflags(ios::left) << setw(LONG_W) << "start time";
	cout << setflags(ios::left) << setw(LONG_W) << "end time";
	cout << setflags(ios::left) << "participators\n";
	//auto u_list =m_agendaService.listAllUsers();
	//for (auto iter =u_list.begin(); iter !=u_list.end(); ++iter) {
		auto m_list =m_agendaService.listAllMeetings(m_userName);
		for (auto ptr =m_list.begin(); ptr!=m_list.end(); ++ptr) {
			cout << setflags(ios::left) << setw(SHORT_W) << ptr->getTitle();
			cout << setflags(ios::left) << setw(SHORT_W) << ptr->getSponsor();
			Date d1 =ptr->getStartDate(), d2 =ptr->getEndDate();
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d1);
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d2);
			auto _part =ptr->getParticipator();
			int i;
			for (i =0; i < _part.size() -1; ++i) {
				cout << setflags(ios::left) << _part[i] << ",";
			}
			cout << _part[i] << endl;
		}
	//}
	OperationLoop();
}

void AgendaUI::listAllSponsorMeetings() {
	cout << "[list all sponsor meetings]\n\n";
	cout << setflags(ios::left) << setw(SHORT_W) << "title";
	cout << setflags(ios::left) << setw(SHORT_W) << "sponsor";
	cout << setflags(ios::left) << setw(LONG_W) << "start time";
	cout << setflags(ios::left) << setw(LONG_W) << "end time";
	cout << setflags(ios::left) << "participators\n";
	auto m_list =m_agendaService.listAllSponsorMeetings(m_userName);
	for (auto ptr =m_list.begin(); ptr!=m_list.end(); ++ptr) {
			cout << setflags(ios::left) << setw(SHORT_W) << ptr->getTitle();
			cout << setflags(ios::left) << setw(SHORT_W) << m_userName;
			Date d1 =ptr->getStartDate(), d2 =ptr->getEndDate();
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d1);
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d2);
			auto _part =ptr->getParticipator();
			int i;
			for (i =0; i < _part.size() -1; ++i) {
				cout << _part[i] << ",";
			}
			cout << _part[i] << endl;
	}
	OperationLoop();
}

void AgendaUI::listAllParticipateMeetings() {
	cout << "[list all participator meetings]\n\n";
	cout << setflags(ios::left) << setw(SHORT_W) << "title";
	cout << setflags(ios::left) << setw(SHORT_W) << "sponsor";
	cout << setflags(ios::left) << setw(LONG_W) << "start time";
	cout << setflags(ios::left) << setw(LONG_W) << "end time";
	cout << setflags(ios::left) << "participators\n";
	auto m_list =m_agendaService.listAllParticipateMeetings(m_userName);
	for (auto ptr =m_list.begin(); ptr!=m_list.end(); ++ptr) {
			cout << setflags(ios::left) << setw(SHORT_W) << ptr->getTitle();
			cout << setflags(ios::left) << setw(SHORT_W) << ptr->getSponsor();
			Date d1 =ptr->getStartDate(), d2 =ptr->getEndDate();
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d1);
			cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d2);
			auto _part =ptr->getParticipator();
			int i;
			for (i =0; i < _part.size() -1; ++i) {
				cout << setflags(ios::left) << _part[i] << ",";
			}
			cout << _part[i] << endl;
	}
	OperationLoop();
}

void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting] [title]\n";
	cout << "[query meeting] ";
	string _title;
	cin >> _title;
	auto m_list =m_agendaService.meetingQuery(m_userName, _title);
	cout << endl;
	cout << setflags(ios::left) << setw(SHORT_W) << "title";
	cout << setflags(ios::left) << setw(SHORT_W) << "sponsor";
	cout << setflags(ios::left) << setw(LONG_W) << "start time";
	cout << setflags(ios::left) << setw(LONG_W) << "end time";
	cout << setflags(ios::left) << "participators\n";
	for (auto iter =m_list.begin(); iter !=m_list.end(); ++iter) {
		cout << setflags(ios::left) << setw(SHORT_W) << iter->getTitle();
		cout << setflags(ios::left) << setw(SHORT_W) << iter->getSponsor();
		Date d1 =iter->getStartDate();
		Date d2 =iter->getEndDate();
		cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d1);
		cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d2);
		auto _part =iter->getParticipator();
			int i;
			for (i =0; i < _part.size() -1; ++i) {
				cout << setflags(ios::left) << left << _part[i] << ",";
			}
			cout << _part[i] << endl;
	}
	OperationLoop();
}

    /**
     * search meetings by timeinterval from storage
     */
void AgendaUI::queryMeetingByTimeInterval(void) {  // not finished
	cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	cout << "[query meeting] ";
	string s_date, e_date;
	cin >> s_date >> e_date;
	auto m_list =m_agendaService.meetingQuery(m_userName, s_date, e_date);
	cout << endl;
	cout << setflags(ios::left) << setw(SHORT_W) << "title";
	cout << setflags(ios::left) << setw(SHORT_W) << "sponsor";
	cout << setflags(ios::left) << setw(LONG_W) << "start time";
	cout << setflags(ios::left) << setw(LONG_W) << "end time";
	cout << setflags(ios::left) << "participators\n";
	for (auto iter =m_list.begin(); iter !=m_list.end(); ++iter) {
		cout << setflags(ios::left) << setw(SHORT_W) << iter->getTitle();
		cout << setflags(ios::left) << setw(SHORT_W) << iter->getSponsor();
		Date d1 =iter->getStartDate();
		Date d2 =iter->getEndDate();
		cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d1);
		cout << setflags(ios::left) << setw(LONG_W) << Date::dateToString(d2);
		auto _part =iter->getParticipator();
			int i;
			for (i =0; i < _part.size() -1; ++i) {
				cout <<_part[i] << ",";
			}
			cout << _part[i] << endl;
	}
	OperationLoop();
}

    /**
     * delete meetings by title from storage
     */
void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting] [title]\n";
	cout << "[delete meeting] ";
	string _title;
	cin >> _title;
	if (m_agendaService.deleteMeeting(m_userName, _title))
		cout << "[delete meeting by title] succeed!\n";
	else cout << "[error] delete meeting fail!\n";
	OperationLoop();
}

    /**
     * delete all meetings that this user sponsored
     */
void AgendaUI::deleteAllMeetings(void) {
	if (m_agendaService.deleteAllMeetings(m_userName))
		cout << "[delete all meetings] succeed!\n";
	OperationLoop();
}

    /**
     * show the meetings in the screen
     */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
	// woc
}