SRC=main.c
SRC+=queue.c process.c pthread_mail.c log.c picture.c utf.c framebuffer.c
OBJ = a.out
$(OBJ):$(SRC)
	gcc $(SRC) -o$(OBJ) -g -pthread -lm

clean:
	rm $(OBJ)
	
