CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
FRAMEWORKS = -framework ApplicationServices

mouse-jiggle: mouse-jiggle.cpp
	$(CXX) $(CXXFLAGS) $< $(FRAMEWORKS) -o $@

clean:
	rm -f mouse-jiggle

.PHONY: clean
