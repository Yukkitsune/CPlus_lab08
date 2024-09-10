
#include <iostream>
#include <string>
#include <vector>

struct Employee { // Информационное поле - сотрудник
    std::string fio;
    std::string date;
    std::string position;
    double salary;
};
struct listItem { // Структура для задания элемента двусвязного списка
    Employee employee;
    listItem* pNext;
    listItem* pPrev;// Указатель на следующий и предыдущий элемент соответственно
};
struct List { // Задаём список с указателем на первый элемент
    listItem* pFirst; 
};
void addInList(List& list, listItem* p, bool flag = true) { // flag = true Добавляем в начало списка
    if (list.pFirst == 0) { // Если указатель на первый элемент равен 0
        list.pFirst = p->pNext = p->pPrev = p;
    }
    else {
        p->pNext = list.pFirst; // Сдвигаем указатели
        p->pPrev = list.pFirst->pPrev;
        list.pFirst->pPrev->pNext = p;
        list.pFirst->pPrev = p;
        if (flag) list.pFirst = p; // Элемент стал первый
    }
}
void addAfter(listItem* pEnd, listItem* p) { // Добавляем элементы в конец списка
    p->pNext = pEnd->pNext; // Сдвигаем указатели
    p->pPrev = pEnd;
    pEnd->pNext->pPrev = p;
    pEnd->pNext = p;
}
listItem* remove(List& list, listItem* p) { // Извлекаем элементы из списка
    if (list.pFirst == 0 || p == 0) return 0; // Если список пуст, возвращаем 0
    if (list.pFirst->pNext == list.pFirst) { // Список состоит из одного элемента, возвращаем его
        if (p == list.pFirst) {
            list.pFirst = 0;
            return p;
        }
        else return 0;
    }
    if (p == list.pFirst) // Извлекаемый элемент первый
        list.pFirst = list.pFirst->pNext; // Второй будет первым
    p->pPrev->pNext = p->pNext; // Сдвигаем указатели
    p->pNext->pPrev = p->pPrev;
    return p; // Извлекаем элемент
}
void print(List list) { // Выводим список
    listItem* p = list.pFirst;
    do
    {
        std::cout << std::endl <<"Full Name: "<< p->employee.fio << " Date: " << p->employee.date << " Position: " << p->employee.position << " Salary (rubles): " << p->employee.salary;
        p = p->pNext;
    } while (p != list.pFirst);
}
int main(int argc, const char* argv[]) {
    setlocale(LC_ALL, "Russian");
    List list = { 0 };
    listItem* p; // Указатель на listItem
    // Ввод списка
    char a; // Символ, необходимый для завершения ввода сотрудников
    bool flag = true;

    do {
        
        p = new listItem;   // Храним сотрудников
        std::cout << "Enter full name of the employee: "; // Здесь и далее ввод информации о сотрудниках
        if (flag == false) {
            std::cin.ignore();
        }
        std::getline(std::cin, p->employee.fio);
        std::cout << "Enter date of the employee: ";
        std::getline(std::cin, p->employee.date);
        std::cout << "Enter position of the employee: ";
        std::getline(std::cin, p->employee.position);
        std::cout << "Enter salary of the employee (rubles): ";
        std::cin >> p->employee.salary;
        std::cin.ignore();
        flag = false;
        addInList(list, p, false); // Добавляем сотрудников в начало списка
        std::cout << "Press 'k' button to continue" << std::endl; // Чтобы продолжить, пользователь вводит 'k'
        a = getchar(); // Пользователь вводит букву
    } while ((a == 'K') || (a == 'k')); // Если k - продолжаем, иначе идем дальше
    std::cout << "Before sort: ";
    print(list);
    //Сортировка пузырьком
    bool temp; // Флаг для того, чтобы понять, что замена сделана
    do {
        temp = false;
        listItem* p1 = list.pFirst; // Указатель на элемент
        listItem* p2 = list.pFirst->pNext; // Указатель на следующий элемент
        do {
            if (p1->employee.fio > p2->employee.fio) { // Сортировка по фамилии
                p1 = remove(list, p1); // Извлекаем p1
                if (p1 == 0) { // Если его не существует, выводим ошибку
                    std::cout << "List error :(";
                    system("pause");
                    return 0;
                }
                addAfter(p2, p1); // Меняем элементы местами
                p2 = p1->pNext;
                temp = true; // Замена сделана
            }
            else { // Элементы не меняем
                p1 = p2;
                p2 = p2->pNext;
            }
        } while (p2 != list.pFirst); // Идем, пока указатель на следующий элемент не станет первым      
    } while (temp);
    std::cout << std::endl;
    std::cout << "After sort: ";
    print(list); // Выводим список после сортировки
    return 0;
}
