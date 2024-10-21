CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++11 -pthread -g

BUILD_DIR=build

PROGRAM1_SOURCES=program_1/main.cpp program_1/input_thread.cpp program_1/processing_thread.cpp program_1/buffer.cpp program_1/socket_client.cpp
PROGRAM1_EXECUTABLE=program1

PROGRAM2_SOURCES=program_2/main.cpp program_2/socket_server.cpp program_2/data_processor.cpp
PROGRAM2_EXECUTABLE=program2

all: $(PROGRAM1_EXECUTABLE) $(PROGRAM2_EXECUTABLE)

$(PROGRAM1_EXECUTABLE): $(PROGRAM1_SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

$(PROGRAM2_EXECUTABLE): $(PROGRAM2_SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

run_program1: $(PROGRAM1_EXECUTABLE)
	./$<

run_program2: $(PROGRAM2_EXECUTABLE)
	./$<

clean:
	rm -f $(PROGRAM1_EXECUTABLE) $(PROGRAM2_EXECUTABLE)

.PHONY: all clean run_program1 run_program2