TARGET = condition_variable
TARGET2 = std_move
TARGET3 = make_shared
TARGET4 = std_future
TARGET5 = std_result_of
all:
	g++ --std=c++11 -lpthread $(TARGET).cpp -o $(TARGET).out
	g++ --std=c++11 $(TARGET2).cpp -o $(TARGET2).out
	g++ --std=c++11 $(TARGET3).cpp -o $(TARGET3).out
	g++ --std=c++11 -lpthread $(TARGET4).cpp -o $(TARGET4).out
	g++ --std=c++11 $(TARGET5).cpp -o $(TARGET5).out
clean:
	rm -rf *.o *.out