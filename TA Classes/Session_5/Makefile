CC = gcc
CFLAGS = -Wall

TARGET = ABC
SRC = ABC.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
  $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
  $(CC) $(CFLAGS) -c -o $@ $<

clean:
  rm -f $(OBJ) $(TARGET)
