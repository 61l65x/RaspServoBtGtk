HMSG = $(shell echo !!!! USE SUDO ./EXE !!!! )


all:
	$(info $(HMSG))
	gcc hardPwmMain.c -o exehard `pkg-config --cflags --libs bluez` -lbluetooth -lwiringPi -lpthread
	
clean:
	rm exe*

