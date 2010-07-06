# main target
all: res

# release
res: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -lpthread -lcppunit -g0 -O3 -o $@

# debug
debug: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -lpthread -lcppunit -g3 -O0 -o $@

# object files
%.o: %.cpp
	g++ -c -MD $<
include $(wildcard *.d)

# delete temporary files
clean:
	rm -f *.o *.d *~ res

