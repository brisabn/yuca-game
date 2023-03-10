TARGET		:= program

# OS specific variables

ifeq ($(OS),Windows_NT)
	SYSTEM	= win
	SUFFIX	= .exe
	RUN		= libs/sfml-win/bin/${TARGET}${SUFFIX}
	OUT_DIR	= libs/sfml-win/bin/
	MKDIR	= @if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
else
	SYSTEM	= linux
	SUFFIX	=
	RUN		= export LD_LIBRARY_PATH=libs/sfml-linux/lib && ./${TARGET}${SUFFIX}
	OUT_DIR	= 
	MKDIR	= @mkdir -p $(@D)
endif


# recursive wildcard function by John Graham-Cunning
# https://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))


# common variables

CC			:= g++
CXXFLAGS	:= -std=c++11 -g -Wall
LDFLAGS		:= -Llibs/sfml-${SYSTEM}/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -Llibs/box2d/${SYSTEM} -lbox2d
BUILD		:= ./build
INCLUDE		:= -I . -I include -I engine/include -I libs/sfml-${SYSTEM}/include -I libs/box2d/include

SRC			:= $(call rwildcard, src, *.cpp) $(call rwildcard, engine, *.cpp)
OBJECTS		:= $(SRC:%.cpp=$(BUILD)/%.o)
DEPENDS		:= $(SRC:%.cpp=$(BUILD)/%.d)


# build targets

all: $(TARGET)

-include $(DEPENDS)

$(BUILD)/%.o: %.cpp
	${MKDIR}
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

$(TARGET): $(OBJECTS)
	${MKDIR}
	$(CXX) $(CXXFLAGS) -o ${OUT_DIR}$(TARGET)${SUFFIX} $^ $(LDFLAGS)


# phony targets

.PHONY: run install

install:

run:
	${RUN}
