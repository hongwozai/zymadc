TARGET = $(notdir $(shell pwd))

SUBDIR = src test

CC = g++

CFLAGS  = -g3 -Wall -Iinc -lstdc++ -std=c++11 -Isrc
LDFLAGS =

SRCS  = $(wildcard $(addsuffix /*.cpp, $(SUBDIR)))
SRCS += $(wildcard $(addsuffix /*.c,   $(SUBDIR)))
DEPS := $(patsubst %.c, %.deps, $(patsubst %.cpp, %.deps, $(SRCS)))
OBJS := $(patsubst %.c, %.o,    $(patsubst %.cpp, %.o,    $(SRCS)))

ifeq ("$(SRCS)", " ")
exit:
endif

# fake target
.PHONY: all run clean coverage release debug echo test exit

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)
	rm -rf $(DEPS)

test: CFLAGS += -UNDEBUG
test: LDFLAGS += -lgtest -lpthread
test: run

coverage: CFLAGS  += --coverage
coverage: LDFLAGS += --coverage
coverage: all

release: CFLAGS += -O2
release: all

ifneq ("$(MAKECMDGOALS)", "clean")
include $(DEPS)
endif

# real target
echo:
	@echo $(SRCS)
	@echo $(DEPS)
	@echo $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $^ $(LDFLAGS)

%.deps: %.cpp
	@set -e ; \
	$(CC) $(CFLAGS) -MM $< > $@; \
	sed -E -i "s,(.*):,$(dir $@)\1:,g" $@;

%.deps: %.c
	@set -e ; \
	$(CC) $(CFLAGS) -MM $< > $@; \
	sed -E -i "s,(.*):,$(dir $@)\1:,g" $@;

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
