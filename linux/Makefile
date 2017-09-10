all:
	# gcc -DDEBUG -Wall -o xhklib_test xhklib_test.c -I./lib ./lib/xhklib.c -lX11 -lXtst -lXext 
	gcc -Wall -o cdh unix_cdh.c unix_hot_keys.c -I../ ../code_demo_helper.c ../code.c ../code_snippet.c ../copy_code_to_clipboard.c  -I../lib ../lib/xhklib.c -lX11 -lXtst -lXext 
	# gcc -Wall -o xbindwin xbindwin.c -I./lib ./lib/xhklib.c -lX11
debug:
	gcc -g -Wall -o cdh_d unix_cdh.c unix_hot_keys.c -I../ ../code_demo_helper.c ../code.c ../code_snippet.c ../copy_code_to_clipboard.c  -I../lib ../lib/xhklib.c -lX11 -lXtst -lXext 
clean:
	rm -f xhklib_test
	rm -f xbindwin
