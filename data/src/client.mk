TARGET ?= client.out

BUILD_DIR ?= ../../build

SRC_DIRS ?= ./client ./common
########################################################################################
##
########################################################################################
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
########################################################################################
##
########################################################################################
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
########################################################################################
##
########################################################################################
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
########################################################################################
##
########################################################################################
CXXFLAGS = -g -D_UNENABLE_NETWORK
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
########################################################################################
##
########################################################################################
-include $(DEPS)
MKDIR_P ?= mkdir -p