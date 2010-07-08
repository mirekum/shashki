# main target
all: shashki

# release version
shashki: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -lpthread -g0 -O3 -o $@

# object files
%.o: %.cpp
	g++ -c -MD $<
include $(wildcard *.d)

# delete temporary files
clean:
	rm -f *.o *.d *~ shashki


# package installation
#install:
#    cp shashki $(DESTDIR)/usr/bin/
#    cp shashki.desktop $(DESTDIR)/usr/share/applications/hildon/



