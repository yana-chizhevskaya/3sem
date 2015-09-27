/* Программа 05-2.с, иилюстрирующая работу с
pip`ом в рамках одного процесса */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
int fd[2];
ssize_t size;
char string[] = "Hello, world!";
char resstring[14];
/* Попытка создать pipe */
if (pipe(fd) < 0) {
/* Если создать pipe не удалось, печатаем об этом
сообщение и прекращаем работу */
printf("Can`t create pipe");
exit(-1);
}

/* Пробуем записать в pipe 14 байт из нашего
массива, т.е. всю строку "Hello, world!" вместе
с признаком конца строки */
size = write(fd[1] , string , 14);
if (size != 14) {
/* Если записалось меньшее количество байт,
сообщаем об ошибке */
printf("Can`t write all string\n");
exit(-1);
}

/* Пробуем прочитать из pip`а 14 байт в другой массив,
т.е. всю записанную строку */
size = read(fd[0] , resstring , 14);
if (size < 0) {
/* Если прочитать не смогли, сообщаем об ошибке */
printf("Can`t read string\n");
exit(-1);
}
/* Печатаем прочитанную строку */
printf("%s\n" , resstring);
/* Закрываем выходной поток */
if (close(fd[1]) < 0) {
printf("Can`t close output stream\n");
exit(-1);
}
if (close(fd[0]) < 0) {
printf("Can`t close input stream\n");
exit(-1);
}

return 0;
}
