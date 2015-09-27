/* Программа, осуществляющая однонаправленную 
связь через FIFO между процессом-родителем и
процессом-ребенком */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MaxStringSize = 1024;
const char * string = "Hello, world!";
const char * name = "aaa.fifo";

int main() {
int fd , result , size;
char resstring[MaxStringSize];

/* Обнуляем маску создания файлов текущего процесса
для того, чтобы права доступа у создаваемого FIFO
точно соответствовали параметру вызова mknod() */
umask(0);

/* Попытаемся создать FIFO с именем aaa.fifo в текущей 
директории */
if (mknod(name , S_IFIFO | 0666 , 0) < 0) {
/* Если создать FIFO не удалось, печатаем об
этом сообщение и прекращаем работу */
printf("Can`t create FIFO\n");
exit(-1);
}

/*Порождаем новый поток */
if ( (result = fork()) < 0) {
/* Если создать процесс не удалось, сообщаем
об этом и завершаем работу */
printf("Can`t fork child\n");
exit(-1);
} else if (result > 0) {
/* Мы находимся в родительском процессе, который
будет передавать информацию процессу-ребенку. В
этом процессе открываем FIFO на запись */
if ( (fd = open(name , O_WRONLY)) < 0) {
/* Если открыть FIFO не удалось, печатаем об этом
гневное сообщение и прекращаем работу */
printf("Can`t open FIFO for writing\n");
exit(-1);
}

/* Пробуем записать в FIFO 14 байт, т.е. всю
уже ставшую родной нам строку "Hello, world!" 
вместе с признаком конца строки */
size = write(fd , string , strlen(string) + 1);
if (size != strlen(string) + 1) {
/* Если записалось меньшее количество байт, то
сообщаем об ошибке и завершаем работу */
printf("Can`t write all string to FIFO\n");
exit(-1);
}
/* Закрываем входной поток данных и на этом
родитель засыпает...навсегда */
close(fd);
printf("Parent exit\n");
} else {
/* Мы находимся в дочернем процессе, который
будет получать информацию от процесса-родителя.
Открываем FIFO на чтение */
// if ( (fd = open(name , O_RDONLY)) < 0) {
/*Если открыть FIFO не удалось, печатаем буквы
и прекращаем работу */
// printf("Can`t open FIFO for reading\n");
// exit(-1);
// }

/* Пробуем прочитать из FIFO 14 байт в массив,
т.е. всю записанную строку */
size = read(fd , resstring , strlen(string) + 1);
if (size < 0) { 
/* Если прочитать не смогли, сообщаем об ошибке
и завершаем работу */
printf("Can`t read string\n");
exit(-1);
}
/* Печатаем прочитанную строку */ 
printf("%s\n" , resstring);
/* Закрываем входной поток и завершаем работу */
close(fd);
}
return 0;
}
