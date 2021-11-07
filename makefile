CC = g++ -std=c++11
proj2.x: test_list.o
	$(CC) -o proj2.x test_list.o
test_list.o: test_list.cpp List.hpp
	$(CC) -c test_list.cpp
