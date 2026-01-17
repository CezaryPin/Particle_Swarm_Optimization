CC = gcc

CFLAGS = -Wall -Wextra -I./mapGen/Perlin_Noise_Generator

LDFLAGS = -L./mapGen/Perlin_Noise_Generator -lperlin -lm


PERLIN_LIB = mapGen/Perlin_Noise_Generator/libperlin.a


SRCS = main.c utils.c pso.c map.c logger.c
OBJS = $(SRCS:.c=.o)
TARGET = out.exe


$(TARGET): $(PERLIN_LIB) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)


$(PERLIN_LIB):
	$(MAKE) -C mapGen/Perlin_Noise_Generator


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET) $(OBJS)
	$(MAKE) -C mapGen/Perlin_Noise_Generator clean