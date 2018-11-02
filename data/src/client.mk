TARGET_CLIENT ?= client.out

BUILD_DIR_CLIENT ?= ../../build

SRC_DIRS_CLIENT ?= ./client ./common
########################################################################################
##
########################################################################################
SRCS_CLIENT := $(shell find $(SRC_DIRS_CLIENT) -name *.cpp -or -name *.c -or -name *.s)
OBJS_CLIENT := $(SRCS_CLIENT:%=$(BUILD_DIR_CLIENT)/%.o)
DEPS_CLIENT := $(OBJS_CLIENT:.o=.d)
########################################################################################
##
########################################################################################
INC_DIRS_CLIENT := $(shell find $(SRC_DIRS_CLIENT) -type d)
INC_FLAGS_CLIENT := $(addprefix -I,$(INC_DIRS_CLIENT))
CPPFLAGS_CLIENT ?= $(INC_FLAGS_CLIENT) -MMD -MP
########################################################################################
##
########################################################################################
LDFLAGS_CLIENT = -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lglut -lGLU -Wl,-rpath,/usr/local/lib

$(BUILD_DIR_CLIENT)/$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(CXX) $(OBJS_CLIENT) -o $@ $(LDFLAGS_CLIENT)
########################################################################################
##
########################################################################################
$(BUILD_DIR_CLIENT)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS_CLIENT) $(CXXFLAGS) -c $< -o $@
########################################################################################
##
########################################################################################
-include $(DEPS_CLIENT)
MKDIR_P ?= mkdir -p

