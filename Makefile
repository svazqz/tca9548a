LIBRARY := tca9548a
BUILD_DIR ?= build
CC ?= cc
AR ?= ar
CFLAGS ?= -O2
WARNINGS := -std=c11 -Wall -Wextra -Wpedantic
INCLUDES := -Iinclude
SOURCE := src/$(LIBRARY).c
OBJECT := $(BUILD_DIR)/$(LIBRARY).o
ARCHIVE := $(BUILD_DIR)/lib$(LIBRARY).a
TEST := $(BUILD_DIR)/test_$(LIBRARY)
SOFT_I2C_HEADER := soft_i2c/include/soft_i2c.h
INCLUDES += -Isoft_i2c/include
TEST_INPUTS := $(SOURCE) tests/test_$(LIBRARY).c tests/mock_i2c.c tests/mock_i2c.h include/$(LIBRARY).h $(SOFT_I2C_HEADER)

.PHONY: all test clean
all: $(ARCHIVE)

$(BUILD_DIR):
	mkdir -p "$@"

$(ARCHIVE): $(OBJECT)
	$(AR) rcs "$@" "$<"

$(SOFT_I2C_HEADER):
	git submodule update --init -- soft_i2c
	test -f "$@"

$(OBJECT): $(SOURCE) include/$(LIBRARY).h $(SOFT_I2C_HEADER) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) $(WARNINGS) -c "$<" -o "$@"

$(TEST): $(TEST_INPUTS) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(INCLUDES) $(CFLAGS) $(WARNINGS) $(LDFLAGS) $(filter %.c,$^) $(LDLIBS) -lm -o "$@"

test: $(TEST)
	"$(TEST)"

clean:
	$(RM) "$(OBJECT)" "$(ARCHIVE)" "$(TEST)"
