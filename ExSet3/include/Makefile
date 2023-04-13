# Environment variable containing flags to pass to the gnu c++ compiler
# -std=c++2a    Specifies that we want support for a new c++ standard
#               so we can use stuff like the [[likely]] annotation
# -Wall			These
# -Wextra			four
# -Wshadow				flags
# -pedantic     			tell the compiler to be very critical of our 
#				code. Code will be scanned for ambiguities and probable
#               bugs and not just actual syntactical or semantic errors.
# -march=native Tells the compiler that the binary only has to run on
#               the exact machine it was compiled on and not general 
#               machines with similar architecture. (more faster code)
CPPFLAGS = -std=c++20 -Wall -Wextra -Wshadow -pedantic -march=native

# Environment variable containing the names of headers that will be used
# with most executables. Without this, make will not know to recompile
# binaries when headers change.
HEADERS = ./include/vb.hpp

# A fake rule that tells make to not expect to actually create files 
# called "clean" or "debug".
.PHONY: clean debug

main: vbyte.cpp $(HEADERS)
	g++ $(CPPFLAGS) -DNDEBUG -Ofast -o main vbyte.cpp

# Tells make what to do when "make clean" is called.
# Here we simply remove the "query" binary.
clean:
	rm -f main

# Tells make what to do when "make debug" is called.
# Here we compile the binary with different flags to support debugging.
debug: vbyte.cpp $(HEADERS)
	g++ $(CPPFLAGS) -DDEBUG -g -o main vbyte.cpp

# Generic rule that tells make that nothing needs to be done about c++ header files.
%.hpp:
