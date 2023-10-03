HMSG = $(shell echo | This version moves servo with HARDWARE pwm signals |)
SMSG = $(shell echo | This version moves servo with SOFTWARE pwm signals |)
MSG = $(shell echo 'make hard' or 'make soft')

all:
	$(info $(MSG))

hard:
	$(info $(HMSG))
	gcc hardPwmMain.c -o exehard `pkg-config --cflags --libs bluez` -lbluetooth -lwiringPi -lpthread
	
soft:
	$(info $(SMSG))
	gcc softPwmMain.c -o exesoft `pkg-config --cflags --libs bluez` -lbluetooth -lwiringPi -lpthread

clean:
	rm exe*

