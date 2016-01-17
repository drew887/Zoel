CC:= g++
CXXFLAGS:= -Wall -g -Wextra -std=c++0x -lopenal
.PHONY: clean docs
obj:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.cpp)))
dep:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.d)))
Target:= $(notdir $(CURDIR))

all: $(Target)
$(Target): $(obj:.cpp=.o)
	$(CC) $**.o -o $(Target) $(CXXFLAGS)

%.o : %.cpp
	$(CC) $(CXXFLAGS) -MMD -c $< -o $@

-include $(dep)

clean:
	@rm -f $(Target) *.o *.d
	@clear
