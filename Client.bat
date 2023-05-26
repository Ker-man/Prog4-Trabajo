gcc -c BBDD/funcionesBD.c -o bbdd.o
gcc -c BBDD/sqlite3.c -o bbdd.o
g++ -c Cliente/cliente.cpp -o main.o
g++ main.o bbdd.o -o Cliente.exe -lws2_32
Cliente.exe
