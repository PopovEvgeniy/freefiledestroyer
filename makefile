install:
	@echo Installation in progress. Please wait
	@$(CC) freefiledestroyer.c -g0 -O0 -o /bin/freefiledestroyer
	@chmod ugo+rx /bin/freefiledestroyer
	@echo Installation was successfully completed
uninstall:
	@rm -f /bin/freefiledestroyer
	@echo Uninstallation was successfully completed