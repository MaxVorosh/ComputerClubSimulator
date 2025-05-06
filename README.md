# ComputerClubSimulator

## Сборка
Для сборки используется cmake. Один из возможных примеров:

```
mkdir build
cd build
cmake ..
cmake --build .
```
После этого, вы окажетесь в одной папке с бинарником. Его можно запустить командой
```
./ClubSim <filename>
```
Здесь filename - относительный путь до файла с входными данными.

## Примеры работы
В файле [base_example.txt](./examples/base_example.txt) приведён пример корректного файла. После выполнения команды, получаем следующий вывод:
```
./ClubSim ./../examples/base_example.txt
```

```
09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58
2 30 02:18
3 90 08:01
```

В файле [bad_example.txt](./examples/bad_example.txt) приведён пример файла неправильного формата. После выполнения команды, получаем следующий вывод:
```
./ClubSim ./../examples/bad_example.txt
```

```
09:48 5 client1 1
Incorrect type
```

Получили строчку с ошибкой и небольшое сообщение

Больше примеров в папке [examples](./examples)

## Тесты

Для написания unit-тестов используется библиотека doctest. Чтобы запустить тесты, нужно запустить команду:
```
./ClubSimTest
```