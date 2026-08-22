#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>


#define TRUE 1
#define FALSE 0
#define E 0.000001


int abc_(char, double*); // чтение коэффициентов
int input(double *, double *, double *); //обработка ввода
void discriminant(double , double , double, double*); // вычисление дискриминанта
int solver(double , double , double , double ); //счет и вывод корней
int continuE(void); //хочет ли пользователь продолжить
bool is_zero(double); //является ли число нулем
void clear_buffer(void); //очистка мусорной части ввода


