CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -pthread
CC_FLAGS := -std=c++0x -Wall -pthread

Cloud: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^ -ldl

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf obj/*.o

config:
	useradd eroscloud
	mkdir /etc/eroscloud/
	mkdir /etc/eroscloud/sites-enabled/
	mkdir /etc/eroscloud/sites-available/
	chown -R eroscloud:eroscloud /etc/eroscloud/
	cp conf/example-site /etc/eroscloud/sites-available/
	
setup:
	#Fedora 17 32 Bit
	yum install gcc
	yum install gcc-c++
	yum install glib
