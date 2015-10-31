CFLAGS = -lssl -lcrypto
TARGET = soap
SOURCE = $(wildcard *.c)
OBJECTS = $(filter-out $(TARGET).o,$(SOURCE:.c=.o))

all: $(TARGET)

$(TARGET): soap.c $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $@.c -o $@


$(OBJECTS): $(@:.o=.c)

clean:
	@rm -f $(OBJECTS) $(TARGET)
