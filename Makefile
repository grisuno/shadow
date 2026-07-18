CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = shadow
SRC = shadow.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

serve:
	python3 server.py

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean serve run