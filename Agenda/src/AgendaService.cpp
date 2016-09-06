#include "AgendaService.hpp"
#include "User.hpp"

AgendaService::AgendaService() {
	m_storage.reset();
	m_storage =Storage::getInstance();
}

AgendaService::~AgendaService() {
	// m_storage->Storage::~Storage();
}

bool AgendaService::userLogIn(const std::string username, const std::string password) {
	auto target =m_storage->queryUser([=](const User& usr)->bool {
		if (usr.getName() ==username && usr.getPassword() == password) return true;
		else return false;
	});
	if (target.size()) return true;
	
	return false;
}

bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
	User user;
	user.setName(userName);

	auto target =m_storage->queryUser([user](const User & t)->bool {
		if (user.getName() == t.getName()) return true;
		return false;
	});
	if (target.size()) {
		return false;
	}
	user.setPassword(password);
	user.setEmail(email);
	user.setPhone(phone);
	m_storage->createUser(user);
	return true;
}

bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	/*User usr;
	usr.setName(userName);
	auto target =m_storage->queryUser([usr](const User & t)->bool {
		if (usr.getName() == t.getName()) return true;
		return false;
	});  // check if  the name exist
	if (!target.size()) return false;*/
	m_storage->deleteMeeting([=] (const Meeting & meet)->bool {
		return (userName == meet.getSponsor() || meet.isParticipator(userName));
	});

	return m_storage->deleteUser([=](const User& usr)->bool {
		if (userName == usr.getName() && password == usr.getPassword()) return true;
		return false;
	});
}

std::list<User> AgendaService::listAllUsers(void) const {
	return m_storage->queryUser([](const User & t)->bool {
		return true;
	});  // return all user
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> part) {
	Meeting meet;
	meet.setSponsor(userName);
	meet.setParticipator(part);
	meet.setTitle(title);
	meet.setStartDate(startDate);
	meet.setEndDate(endDate);

	if (startDate >=endDate) return false;  // check time
	
	auto meet0 =m_storage->queryMeeting([=](const Meeting & mmm)->bool {
		if (mmm.getTitle() == title) return true;
		else return false;
	});
	if (meet0.size()) return false;  // check title

	auto meeting1 =m_storage->queryMeeting([=](const Meeting & spon)->bool {
		if (userName ==spon.getSponsor()) {
			if (spon.getStartDate() <=startDate && spon.getEndDate() > startDate) {
				return true;
			} else if (spon.getEndDate() >=endDate && spon.getStartDate() <endDate) {
				return true;
			} else return false;
		} else return false;
	}); 
	if (meeting1.size()) return false;  // check if sponsor


	auto meeting2 =m_storage->queryMeeting([=](const Meeting & meet)->bool {

		auto ptr =part.begin();
		for (; ptr !=part.end(); ++ptr) {
			if (meet.isParticipator(*ptr)) {
				if ((meet.getStartDate() <=startDate && meet.getEndDate() >startDate) ||
					(meet.getStartDate() <endDate && meet.getEndDate() >=endDate)) return true;
			}
		} return false;
	});
	if (meeting2.size()) return false;  // check partici

	for (int i =0; i <part.size(); ++i) {
		if (part[i] ==userName) return false;
	}



	m_storage->createMeeting(meet);
	return true;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {

	auto met_list =m_storage->queryMeeting([=](const Meeting& _meet)->bool {
		if (userName == _meet.getSponsor() && title ==_meet.getTitle()) return true;
		return false;
	});   // check title and name
	return met_list;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
	Date d1(startDate);
	Date d2(endDate);
	auto met_list =m_storage->queryMeeting([=](const Meeting& _meet)->bool {
		if ((userName == _meet.getSponsor() || _meet.isParticipator(userName)) && (d1 <=_meet.getStartDate() &&
			_meet.getStartDate() <=d2)) return true;
		if ((userName == _meet.getSponsor() || _meet.isParticipator(userName)) && (d1 <=_meet.getEndDate() &&
			_meet.getEndDate() <= d2)) return true;
		return false;
	});   // check title and name
	return met_list;
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	auto m_list = m_storage->queryMeeting([userName](const Meeting & meet)->bool {
		if (meet.getSponsor() ==userName) return true;

		if (meet.isParticipator(userName)) return true;
		return false;
	}); // all meeting taken part in
	return m_list;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	auto m_list = m_storage->queryMeeting([userName](const Meeting & meet)->bool {
		if (userName ==meet.getSponsor()) return true;
		return false;
	});  // all by hom
	return m_list;
}


std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
	auto _list = m_storage->queryMeeting([userName](const Meeting& meet)->bool {
		if (meet.isParticipator(userName)) return true;
		return false;
	});  // all part
	return _list;
}

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {


	int sum =m_storage->deleteMeeting([=](const Meeting& meet)->bool {
		if (title == meet.getTitle() && userName == meet.getSponsor())
			return true;
		else return false;
	}); // by title & name
	if (sum) return true;
	return false;
}

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
bool AgendaService::deleteAllMeetings(const std::string userName) {
	int sum =m_storage->deleteMeeting([userName] (const Meeting& meet)->bool {
		if (userName == meet.getSponsor())
			return true;
		return false;
	}); // by title & name
	if (sum) return true;
	return false;
}
 
void AgendaService::startAgenda(void) {
}

    /**
     * quit Agenda service
     */
void AgendaService::quitAgenda(void) {
	m_storage->sync();
	//delete m_storage;
}