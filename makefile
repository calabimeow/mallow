flags = -std=c99 -shared

windows:
	gcc $(flags) mallow.c mw_windows.c -o mallow.dll -mwindows
linux:
	gcc $(flags) -fPIC mallow.c mw_linux.c -o libmallow.so -lm -lX11 -lXext

.PHONY: windows linux all clean
