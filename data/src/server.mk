TARGET_SERVER ?= server.out

BUILD_DIR_SERVER ?= ../../build

SRC_DIRS_SERVER ?= ./server ./common
########################################################################################
##
########################################################################################
SRCS_SERVER := $(shell find $(SRC_DIRS_SERVER) -name *.cpp -or -name *.c -or -name *.s)
OBJS_SERVER := $(SRCS_SERVER:%=$(BUILD_DIR_SERVER)/%.o)
DEPS_SERVER := $(OBJS_SERVER:.o=.d)
########################################################################################
##
########################################################################################
INC_DIRS_SERVER := $(shell find $(SRC_DIRS_SERVER) -type d)
INC_FLAGS_SERVER := $(addprefix -I,$(INC_DIRS_SERVER))
CPPFLAGS_SERVER ?= $(INC_FLAGS_SERVER) -MMD -MP
########################################################################################
##
########################################################################################
LDFLAGS_SERVER = -lSDL2 -Wl,-rpath,/usr/local/lib

$(BUILD_DIR_SERVER)/$(TARGET_SERVER): $(OBJS_SERVER)
	$(CXX) $(OBJS_SERVER) -o $@ $(LDFLAGS_SERVER)
########################################################################################
##
########################################################################################
CXXFLAGS = -g
$(BUILD_DIR_SERVER)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS_SERVER) $(CXXFLAGS) -c $< -o $@
########################################################################################
##
########################################################################################
-include $(DEPS_SERVER)
MKDIR_P ?= mkdir -p
