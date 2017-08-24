all:
	# gcc -DDEBUG -Wall -o xhklib_test xhklib_test.c -I.. ../xhklib.c -lX11 -lXtst -lXext 
	gcc -Wall -o CodeDemoHelper code_demo_helper.c code.c code_snippet.c -I.. ../xhklib.c -lX11 -lXtst -lXext 
	# gcc -Wall -o xbindwin xbindwin.c -I.. ../xhklib.c -lX11
clean:
	rm -f xhklib_test
	rm -f xbindwin
