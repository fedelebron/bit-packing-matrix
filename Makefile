CXXFLAGS = -std=c++11 -O3 -mpopcnt
RM = rm -f

SRCS = square_bool_matrix.cpp main.cpp 
OBJS = $(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) -o main $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f .depend
	$(CXX) $(CXXFLAGS) -MM $^>>.depend

clean:
	$(RM) $(OBJS) main

include .depend
