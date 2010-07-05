# main target
all: res

# binary program
res: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -lpthread -lcppunit -o $@
# object files
%.o: %.cpp
	g++ -c -MD $<
# files dependences
include $(wildcard *.d)

# delete temporary files
clean:
	rm -f *.o *.d *~ res

