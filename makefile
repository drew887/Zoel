##--This makefile was hastily put together by Andrew Timothy Mcdonald
##--Sat Aug 04, 2012 03:41PM, Added -lopenal to add the audio handling through OpenAL  
##--Wed Aug 08, 2012 12:41AM, Removed some pointless commands that weren't actually doing anything 
##--Wed Aug 08, 2012 00:49AM, Switched $(CC) -o $(Target) $(ofile) and now compiles on first call with no need to call make twice
CC:= g++
CXXFLAGS:= -Wall -g -lopenal
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
	@rm -f $(Target) $(Target).exe *.o lib$(Target).a
	@clear
	@ls
