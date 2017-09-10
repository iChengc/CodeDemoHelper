all:
	gcc -Wall -o cdh unix_cdh.c unix_hot_keys.c -I../ ../code_demo_helper.c ../code.c ../code_snippet.c ../copy_code_to_clipboard.c  -I../lib ../lib/xhklib.c -lX11 -lXtst -lXext 
debug:
	gcc -g -Wall -o cdh_d unix_cdh.c unix_hot_keys.c register_hot_key.c -I../ ../code_demo_helper.c ../code.c ../code_snippet.c ../copy_code_to_clipboard.c  -I../lib ../lib/xhklib.c -lX11 -lXtst -lXext 
clean:
	rm -f cdh
	rm -f cdh_d
