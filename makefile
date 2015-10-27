CFLAGS = -lssl -lcrypto
TARGET = hash

all: $(TARGET)

$(TARGET): hash.c
	gcc $(CFLAGS) $@.c -o $@
