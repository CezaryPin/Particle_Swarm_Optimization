CC = gcc

CFLAGS = -Wall -Wextra -I./Perlin_Noise_Generator

LDFLAGS = -L./Perlin_Noise_Generator -lperlin -lm


PERLIN_LIB = Perlin_Noise_Generator/libperlin.a


SRCS = new_map_gen.c
OBJS = $(SRCS:.c=.o)
TARGET = map.exe


$(TARGET): $(PERLIN_LIB) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)


$(PERLIN_LIB):
	$(MAKE) -C Perlin_Noise_Generator


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET) $(OBJS)
	$(MAKE) -C Perlin_Noise_Generator clean