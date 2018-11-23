install:
	@echo Installation in progress. Please wait
	@gcc freefiledestroyer.c -g0 -O0 -o freefiledestroyer
	@chmod ugo+rx freefiledestroyer
	@cp -f -p freefiledestroyer /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/freefiledestroyer
	@echo Uninstallation was successfuly complete