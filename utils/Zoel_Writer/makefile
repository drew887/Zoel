CC:= g++
CXXFLAGS:= -Wall -g  -std=c++11
.PHONY: clean
obj:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.cpp)))
dep:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.h)))
Target:= $(notdir $(CURDIR))

all: $(Target)
$(Target): $(obj:.cpp=.o)
	$(CC) $**.o -o $(Target) $(CXXFLAGS)

%.o : %.cpp $(dep)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean: 
	@rm -f $(Target) *.o 
	@clear
	@ls
