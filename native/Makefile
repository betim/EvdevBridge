rpi:
	@echo 'Building target: $@'
	@echo 'Invoking: GCC'
	gcc -I/usr/lib/jvm/jdk-7-oracle-armhf/include -I/usr/lib/jvm/jdk-7-oracle-armhf/include/linux -fPIC  -o libevdev.so -shared reader.c
	
	@echo 'Finished building target: $@'
	@echo ' '
	
all:
	@echo 'Building target: $@'
	@echo 'Invoking: GCC'
	gcc -I/usr/lib/jvm/java-7-oracle/include -I/usr/lib/jvm/java-7-oracle/include/linux -fPIC  -o libevdev.so -shared reader.c
	
	@echo 'Finished building target: $@'
	@echo ' '

install:
	mv libevdev.so /usr/lib/
