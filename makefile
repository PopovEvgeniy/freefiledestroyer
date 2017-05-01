install:
	@echo Compiling the program source code. Please wait
	@gcc freefiledestroyer.c -g0 -O0 -o freefiledestroyer
	@echo Compilation successfuly complete
	@chmod ugo+rx freefiledestroyer
	@echo Enter you user password for do last installation step
	@sudo cp -f -p freefiledestroyer /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/freefiledestroyer
	@echo Uninstallation complete