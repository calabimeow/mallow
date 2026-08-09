COMMON_FILES = mallow.c qtee.c 

windows:
	gcc -std=c99 -shared $(COMMON_FILES) mw_windows.c -o mallow.dll -mwindows
linux:
	gcc -std=c99 -shared -fPIC $(COMMON_FILES) mw_linux.c -o libmallow.so -lm -lX11 -lXext

.PHONY: windows linux all clean
