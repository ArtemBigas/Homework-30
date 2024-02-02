# Homework-30

English:Quick sort using thread pools

The main idea: take a quick sort function, without singularity, and place tasks in the main thread.

An array is created and divided into equal parts R in the amount M, which is also the number of tasks. Each matrix array is put through sorting, after which the main one collects everything into a heap.

There are several comments inside the code to test each matrix array

Homework-30 - vector. The same thing, but an array of vector type is used.

Русский:Быстрая сортировка с использованием пулов потоков

Основная идея: взять функцию быстрой сортировки, без сингулярности, а задачи ставить в главном потоке. 

Создается массив, делится на равные части R в количестве M, что также является количеством задач. Каждый массив матрицы пропускается через сортировку, после чего главный собирает всё в кучу.

Внутри кода есть несколько комментарий для тестировки каждого массива матрицы

Homework-30 - vector.Тоже самое, но используется массив типа вектор.
