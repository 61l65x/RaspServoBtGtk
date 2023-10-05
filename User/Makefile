SRCS= $(wildcard srcs/gtk/*.c srcs/*.c)

all:
	gcc -o exe $(SRCS) `pkg-config --cflags --libs gtk4` -lbluetooth
