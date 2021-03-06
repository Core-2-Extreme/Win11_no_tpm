#---------------------------------------------------------------------------------
.SUFFIXES:

#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
SOURCES		:=	source
INCLUDES	:=	include
CXX			:=  i686-w64-mingw32-g++
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-march=core2 -mtune=core2
CFLAGS	:= -static -Wall -O2 $(ARCH)
CXXFLAGS	:= $(CFLAGS) -fno-exceptions -std=gnu++11
#---------------------------------------------------------------------------------

all:
	@echo Building exe... 
	@cd $(SOURCES); $(CXX) main.cpp $(CXXFLAGS) -o ../$(TARGET).exe

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(TARGET).exe
