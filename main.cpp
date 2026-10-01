#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <limits>
#include <cstdlib>

using namespace std;

// Вспомогательная функция ввода
// Читает целое число. Если пользователь ввел не число (например, "abc"),
// сбрасывает ошибку потока и просит ввести заново, чтобы программа не зациклилась.
int readInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
        if (cin.eof())                                        // ввод закрыт (Ctrl+D / Ctrl+Z) - выходим
        {                                                     // иначе цикл был бы бесконечным
            exit(0);
        }
        cin.clear();                                          // снимаем флаг ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // выбрасываем мусор из буфера
        cout << "Ошибка: нужно ввести целое число.\n";
    }
}

// Программа 1: Угадай число
int generateSecret()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 100);  // число от 0 до 100 включительно
    return dist(gen);
}

void printGuessHint(int guess, int secret)
{
    if (guess < secret)
        cout << "Загаданное число БОЛЬШЕ.\n";
    else
        cout << "Загаданное число МЕНЬШЕ.\n";
}

void guessNumberGame()
{
    cout << "\n=== Игра \"Угадай число\" ===\n";
    cout << "Я загадал число от 0 до 100. Попробуй угадать!\n";

    int secret = generateSecret();
    int attempts = 0;
    int guess;

    do
    {
        guess = readInt("Твой вариант: ");
        attempts++;
        if (guess != secret)
        {
            printGuessHint(guess, secret);
        }
    } while (guess != secret);

    cout << "Победа! Ты угадал число " << secret
         << " за " << attempts << " попыток(и).\n";
    // Возврат в меню произойдет автоматически: функция завершается
}

// Программа 2: Таблица умножения
const int TABLE_SIZE = 10;

// Заполнение матрицы циклами: элемент [i][j] = (i+1)*(j+1),
// потому что индексы идут с 0, а таблица умножения - с 1.
void fillMultiplicationTable(int table[TABLE_SIZE][TABLE_SIZE])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (int j = 0; j < TABLE_SIZE; j++)
        {
            table[i][j] = (i + 1) * (j + 1);
        }
    }
}

// Вывод матрицы вложенными циклами: внешний - строки, внутренний - столбцы.
void printMultiplicationTable(const int table[TABLE_SIZE][TABLE_SIZE])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (int j = 0; j < TABLE_SIZE; j++)
        {
            cout << setw(4) << table[i][j];  // setw выравнивает столбцы
        }
        cout << '\n';                        // после строки - перенос
    }
}

void multiplicationTableProgram()
{
    cout << "\n=== Таблица умножения ===\n";

    int table[TABLE_SIZE][TABLE_SIZE];  // многомерный массив 10x10
    fillMultiplicationTable(table);     // 1) сначала заполняем
    printMultiplicationTable(table);    // 2) потом выводим
}

// Программа 3: Делители числа
// Возвращает вектор, потому что заранее неизвестно, сколько делителей будет.
vector<int> findDivisors(int number)
{
    vector<int> divisors;
    for (int d = 1; d <= number; d++)
    {
        if (number % d == 0)  // остаток 0 - значит делится нацело
        {
            divisors.push_back(d);
        }
    }
    return divisors;
}

void printDivisors(int number, const vector<int>& divisors)
{
    cout << "Делители числа " << number << ": ";
    for (size_t i = 0; i < divisors.size(); i++)
    {
        cout << divisors[i] << ' ';
    }
    cout << '\n';
}

void divisorsProgram()
{
    cout << "\n=== Вывод делителей числа ===\n";

    int number = readInt("Введите натуральное число: ");
    if (number <= 0)
    {
        cout << "Число должно быть больше нуля.\n";
        return;
    }

    vector<int> divisors = findDivisors(number);
    printDivisors(number, divisors);
}

// Меню
void printMenu()
{
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1 - Игра \"Угадай число\"\n";
    cout << "2 - Таблица умножения\n";
    cout << "3 - Вывод делителей числа\n";
    cout << "0 - Выход\n";
    cout << "==========================\n";
}

int main()
{
    int choice;

    do
    {
        printMenu();
        choice = readInt("Выберите пункт: ");

        switch (choice)
        {
        case 1:
            guessNumberGame();
            break;
        case 2:
            multiplicationTableProgram();
            break;
        case 3:
            divisorsProgram();
            break;
        case 0:
            cout << "Выход из программы. До свидания!\n";
            break;
        default:
            cout << "Нет такого пункта меню, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
