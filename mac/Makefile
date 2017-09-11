all:
	# gcc -DDEBUG -Wall -o xhklib_test xhklib_test.c -I./lib ./lib/xhklib.c -lX11 -lXtst -lXext 
	gcc mac_key.c -L. -lHotkeyRegisterMac
	# gcc -Wall -o xbindwin xbindwin.c -I./lib ./lib/xhklib.c -lX11
clean:
	rm -f xhklib_test
	rm -f xbindwin
