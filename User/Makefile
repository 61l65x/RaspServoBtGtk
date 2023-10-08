SRCS= $(wildcard srcs/gtk_windows/loadUser/*.c srcs/gtk_windows/*.c srcs/gtk_windows/saveUser/*.c srcs/*.c)

all:
	gcc -o exe $(SRCS) `pkg-config --cflags --libs json-c gtk4` -lbluetooth -lcjson
