# Домашнее задание

## 1.

Предположим, что бинарное дерево поиска $T$, в
котором хранится 1000 уникальных элементов, также
является полным деревом. Поэтому, для хранения $T$
используется массив — индексы элементов дерева $T$
назначаются в порядке обхода в ширину, начиная с 0.
Определите индекс третьего наибольшего элемента.

### Замечания

- Под индексом 0 лежит самое маленькое число в массиве

- Максимальное число лежит в конце массива

Решим вначале задачу для удобства для дерева, в котором индексация в массиве начинается с 1, а потом сдвинем ответ на 1 влево

Рассмотрим первые 512 элементов, они образуют идеальное дерево, причем максимальный из них имеет индекс 512

Тогда его правый сын с индексом $2*512+1=1025$ будет максимальным элементом в нашем дереве, а левый будет меньше максимального элемента и элемента с индексом $512$ и будет больше любого другого элемента массива.

Индекс этого элемента $512*2=1024$, а при нумерации дерева с 0 его индекс будет $1023$

## 2.

Код решения в файле [TreeIterator.cpp](TreeIterator.cpp)

на 23 версии плюсов собирается с двумя ворнингами (игнорируем)

пример решения

```
n: 7
type 7 elements: 1 7 2 3 5 4 0
tree successor:
0 1 2 3 4 5 7 
tree predecessor:
7 5 4 3 2 1 0 
type elem to erase: 0
tree successor:
1 2 3 4 5 7 
tree predecessor:
7 5 4 3 2 1 
```