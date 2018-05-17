GTEST_DIR := $(realpath ./tpt/googletest/googletest)
GMOCK_DIR := $(realpath ./tpt/googletest/googlemock)

CXX=g++
CPPFLAGS=-g -std=c++17 -I$./include -isystem$(GTEST_DIR)/include \
	-isystem$(GMOCK_DIR)/include
LDFLAGS=-g
LDLIBS=

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
BIN_SRCS=bin/main.cpp
BIN_OBJS=bin/main.o
TEST_SRCS=$(wildcard ./test/*.cpp)
TEST_OBJS=$(patsubst %.cpp,%.o,$(TEST_SRCS))
TEST_LDFLAGS=-pthread

.PHONY: bin test gtest

build/bin: $(OBJS) $(BIN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

build/test: $(OBJS) $(TEST_OBJS) $(GTEST_DIR)/libgtest.a $(GMOCK_DIR)/libgmock.a
	$(CXX) $(TEST_LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(GTEST_DIR)/libgtest.a:

$(GMOCK_DIR)/libgmock.a:

gtest:
	cd $(GMOCK_DIR) && cmake . && make && cd $(GTEST_DIR) && cmake . && make

run: build/bin
	./build/bin

test: build/test
	./build/test

