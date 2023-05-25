g++ */*.c */*.cpp -o main.exe
main.exe

Cliente
gcc -c BBDD/bbdd.c -o bbdd.o
gcc -c BBDD/sqlite3.c -o bbdd.o
g++ -c cliente.cpp -o main.o
g++ main.o bbdd.o -o Cliente.exe -lws2_32
Cliente.exe

Servidor
gcc */*.c servidor.c -o main.exe -lws2_32

Cliente Nuestro
gcc -c BBDD/funcionesBD.c -o bbdd.o
gcc -c BBDD/sqlite3.c -o bbdd.o
g++ -c Client-Server/cliente.cpp -o main.o
g++ main.o bbdd.o -o Cliente.exe -lws2_32
Cliente.exe


Servidor Nuestro
gcc -c BBDD/funcionesBD.c -o bbdd.o
gcc -c BBDD/sqlite3.c -o sqlite3.o
g++ -c Client-Server/servidor.cpp -o main2.o
g++ main2.o bbdd.o -o Servidor.exe -lws2_32
Servidor.exe



Servidor
md o
md o\servidor
gcc -c BBDD/funcionesBD.c -o o/servidor/bbdd.o
gcc -c BBDD/sqlite3.c -o o/servidor/sqlite3.o
gcc -c Client-Server/utilidades.c -o o/servidor/utilidades.o
gcc -c Logger/logger.c -o o/servidor/logger.o
gcc -c Empresa/cine.c -o o/servidor/cine.o
gcc -c Empresa/peli.c -o o/servidor/peli.o
gcc -c Empresa/sala.c -o o/servidor/sala.o
gcc -c Empresa/sesion.c -o o/servidor/sesion.o
gcc -c Usuario/user.c -o o/servidor/user.o
g++ -c Servidor/servidor.cpp -o o/servidor/servidor.o
g++ o/servidor/*.o -o server.exe -lws2_32
server.exe






Definitivos

Cliente
gcc -c BBDD/funcionesBD.c -o bbdd.o
gcc -c BBDD/sqlite3.c -o bbdd.o
g++ -c Cliente/cliente.cpp -o main.o
g++ main.o bbdd.o -o Cliente.exe -lws2_32
Cliente.exe

Servidor
gcc */*.c -o Servidor.exe -lws2_32
Servidor.exe