CXX = g++
CXXFLAGS = -std=c++11
OBJS =  main.o utilities.o 
NAME = cuppa_joe

ZIPNAME= Final_Grejuc_Alex.zip
HPP = utilities.hpp 
FILES = ./*

make: 
	$(CXX) $(CXXFLAGS) *.cpp -o $(NAME)

clean:
	rm $(NAME)

zip:
	zip -D $(ZIPNAME) $(FILES)
