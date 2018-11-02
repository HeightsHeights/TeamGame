BUILD_DIR ?= ./build

all:
	cd "$(PWD)/data/src" && make -f client.mk && make -f server.mk

.PHONY: clean
 clean:
	$(RM) -r $(BUILD_DIR)
