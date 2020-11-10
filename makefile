# All Targets
all: cTrace

# Tool invocations
# Executable "cTrace" depends on the files bin/Session.o and bin/Agent.o and bin/Graph.o and bin/main.o and bin/Tree.o.
cTrace: bin/Session.o bin/Agent.o bin/Graph.o bin/main.o bin/Tree.o
	@echo 'Building target: cTrace'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/Session.o bin/Agent.o bin/Graph.o bin/main.o bin/Tree.o
	@echo 'Finished building target: cTrace'
	@echo ' '

# Depends on the source and header files
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/Session.o src/Session.cpp

# Depends on the source and header files
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/Agent.o src/Agent.cpp

# Depends on the source and header files
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/Graph.o src/Graph.cpp

# Depends on the source and header files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/main.o src/main.cpp

# Depends on the source and header files
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -c -Iinclude -o bin/Tree.o src/Tree.cpp

#Clean the build directory
clean: 
	rm -f bin/*
