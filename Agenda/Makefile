#by Young test4
CC :=g++-4.8 -std=c++0x -c -g -I include
bin/Agenda: build/Agenda.o build/Date.o build/Meeting.o build/User.o build/Storage.o build/AgendaService.o build/AgendaUI.o
	g++-4.8 -std=c++0x -g build/Date.o build/Meeting.o build/User.o build/Storage.o build/Agenda.o build/AgendaService.o build/AgendaUI.o -o bin/Agenda.out

build/Agenda.o: src/Agenda.cpp
	$(CC) src/Agenda.cpp -o $@

build/Date.o: src/Date.cpp
	$(CC) src/Date.cpp -o $@
build/Meeting.o: src/Meeting.cpp
	$(CC) src/Meeting.cpp -o $@
build/User.o: src/User.cpp
	$(CC) src/User.cpp -o $@
build/Storage.o: src/Storage.cpp
	$(CC) src/Storage.cpp -o $@
build/AgendaService.o: src/AgendaService.cpp
	$(CC) src/AgendaService.cpp -o $@
build/AgendaUI.o: src/AgendaUI.cpp
	$(CC) src/AgendaUI.cpp -o $@



clean:
	@rm -rf build/*.o
	@rm -rf bin/test.out=;
