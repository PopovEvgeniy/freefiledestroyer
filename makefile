install:
	@echo Installation in progress. Please wait
	@gcc freefiledestroyer.c -g0 -O0 -o /bin/freefiledestroyer
	@chmod ugo+rx /bin/freefiledestroyer
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/freefiledestroyer
	@echo Uninstallation was successfully complete