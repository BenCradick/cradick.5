CC = cc
CFLAGS = -std=gnu99 -pthread
OBJ = oss userProcess
DEP = List.c VClock.c Resources.c ClockSemaphore.c
ALL: $(OBJ)
$(OBJ): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(DEP)
clean:
	/bin/rm $(OBJ)
