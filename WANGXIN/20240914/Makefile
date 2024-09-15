SRC=main.c
SRC+=queue.c process.c pthread_mail.c log.c  recv.c net.c sqlite.c http.c get_http.c urldeconde.c
OBJ = a.out
$(OBJ):$(SRC)
	gcc $(SRC) -o$(OBJ) -g -pthread -lm -lsqlite3

clean:
	rm $(OBJ)
	
