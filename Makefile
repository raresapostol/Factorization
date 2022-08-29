include Makefile.mk


BUILD_NAME = main

PATHB = build/
PATHS = src/

BUILD_SRCS = $(patsubst %.c, %.c, $(call rwildcard, $(PATHS), *.c))
BUILD_OBJS = $(patsubst $(PATHS)%.c, $(PATHB)%.o, ${BUILD_SRCS})
BUILD_DIRS = $(dir $(BUILD_OBJS))

all: clean
all: $(PATHB)
#all: $(PATHB)$(BUILD_NAME).exe

# Create build directory
$(PATHB):
	$(MKDIR) $(PATHB)
	#$(MKDIR) $(BUILD_DIRS)
	g++ -std=c99 -Wall src/main.c -o out.exe

# Build object
$(PATHB)%.o: $(PATHS)%.c
	@echo In Object
	$(CC) -c $(CFLAGS) -o $@ $<

# Build elf
$(PATHB)$(BUILD_NAME).exe: $(BUILD_OBJS)
	$(CC) -o $@ $^
	
clean:
	$(CLEANUP) $(PATHB)
	
.PHONY: clean
.PHONY: all
