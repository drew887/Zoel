##--This makefile was hastily put together by Andrew Timothy Mcdonald
##--Fri Nov 11, 2011,02:10PM, Added OpenGl library to make makefile compatable with OpenGl projects.
##--Tue Nov 15, 2011 06:26PM, Added x11 library to make makefile compatable with x11 windowed projects. 
##--Thu Jun 07, 2012 12:26AM, Removed -GLUT as it was causing an image loading error with engine design
##--Sat Aug 04, 2012 03:41PM, Added -lopenal to add the audio handling through OpenAL  
##--Wed Aug 08, 2012 12:41AM, Removed some pointless commands that weren't actually doing anything 
##--Wed Aug 08, 2012 00:49AM, Switched $(CC) -o $(Target) $(ofile) and now compiles on first call with no need to call make twice
CC:= g++
CXXFLAGS:= -Wall -g
.PHONY: clean main lib win
obj:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.cpp)))
dep:= $(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.h)))
Target:= $(notdir $(CURDIR))

all:	$(obj:.cpp=.o) $(dep)
	@echo "Build Begins...."
	$(CC) $(obj:.cpp=.o) -o $(Target) $(CXXFLAGS)
##	@xterm -T $(Target) -e $(CURDIR)/./$(Target)
	@echo "Build Complete"
win:
	i586-mingw32msvc-g++ $(obj) -Wall -o $(Target).exe 
	@echo "Win done"
lib:	
	@echo "Building project as a linkable library"
	#$(CC) $(obj) $(CXXFLAGS) -fpic -shared -o $(Target).so
	ar -r -s -u -v lib$(Target).a $(obj:.cpp=.o)
##	@ls
ofile:=$(foreach dir,$(CURDIR), $(notdir $(wildcard $(CURDIR)/*.o)))
clean: 
	@rm -f $(Target) $(Target).exe $(ofile) lib$(Target).a
	@clear
	@ls
## $(obj:.cpp=.o) will compile and NOT link all of the .cpp files, and make .o files, which is better for large projects that dont always have to be recompiled.
