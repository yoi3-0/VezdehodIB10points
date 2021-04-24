#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>


int get_random_number(int min, int max) {
    static const double fraction{ 1.0 / (static_cast<double>(RAND_MAX) + 1.0) };
    return static_cast<int>(rand() * fraction * (max - min + 1.0) + min);
}
bool password_check(const int length, int arr[], std::string str);

void super_check(){
    std::string file_path, str;
    std::cout<<"Введите путь к файлу с паролями. Формат файла - 1 пароль на 1 строку без пробелов";
    std::cin>>file_path;
    std::ifstream file;
    std::ofstream good, bad;
    int lenghtpw, options[3];
    file.open(file_path.c_str());
    if (!file.is_open()) {std::cerr<<"Ошибка открытия файла!"; exit(1);}
    std::cout << "Введите длину пароля: ";
    std::cin >> lenghtpw;
    std::cout << "Введите 1 если хотите использовать верхний регистр, 0 - если нет: ";
    std::cin >> options[0];
    std::cout << "Введите 1 если хотите использовать спецсимволы, 0 - если нет: ";
    std::cin >> options[1];
    std::cout << "Введите 1 если хотите использовать цифры, 0 - если нет: ";
    std::cin >> options[2];
    good.open("goodones.txt"); bad.open("badones.txt");
    while(file>>str)
    {
        password_check(lenghtpw, options,str)?(good<<str<<'\n'):(bad<<str<<"\n");
    }
}

bool password_check(const int length, int arr[], std::string str){
    int res=false;

    if (str.length()!=length) return res;
    for (int i=0;i<str.length();i++) ///Если символы нужны и их нет - норма; Не нужны, но есть - провал
    {
        if (str[i]<='Z' && str[i]>='A') {if (!arr[0])  return res;}
            else if ((str[i]<='/' && str[i]>='!' ) || (str[i]<='@' && str[i]>=':') || (str[i]<='`' && str[i]>='[')
            || (str[i]<='~' && str[i]>='{') ) {if (!arr[1])  return res;}
            else if (str[i]<='9' && str[i]>='0')  {if (!arr[2])  return res;}
    }
    return !res;

}

std::string get_random_password(const int length, int arr[]) {
    std::string password;
    password.resize(length);

    for (int i = 0;  i < password.length(); i++) {
        char symbol[1] = {0};
        switch (rand() % 4) {
            case 0:
                if (arr[0]) {
                    symbol[0] = get_random_number('A', 'Z');
                    break;
                }

            case 1:
                if (arr[1]) {
                    switch (rand() % 4) {
                        case 0:
                            symbol[0] = get_random_number('!', '/');
                            break;
                        case 1:
                            symbol[0] = get_random_number(':', '@');
                            break;
                        case 2:
                            symbol[0] = get_random_number('[', '`');
                            break;
                        case 3:
                            symbol[0] = get_random_number('{', '~');
                            break;
                    }
                    break;
                }

            case 2:
                if (arr[2]) {
                    symbol[0] = get_random_number('0', '9');
                    break;
                }
            case 3:
                symbol[0] = get_random_number('a', 'z');
                break;
        }

        password[i] = symbol[0];
    }
    return password;
}

int main() {
    setlocale(0, "rus");
    srand(time(NULL));
    std::cout << "Действия:" << std::endl <<
              "1 - Проверка пароля на соответствие заданным критериям по словарям" << std::endl <<
              "2 - Генерация пароля по заданным критериям" << std::endl <<
              "3 - Пакетная обработка файла с паролями и выводом результатов." << std::endl;

    while (true) {
        std::cout << "Выберите действие: ";
        int complexity{};
        while (!(std::cin >> complexity) || (complexity < 1 || complexity > 4)) {
            std::cout << "Попробуй ещё раз: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        int lenghtpw, options[3];
        std::string str2;
        switch (complexity) {

            case 1:
                std::cout << "Введите длину пароля: ";
                std::cin >> lenghtpw;
                std::cout << "Введите 1 если хотите использовать верхний регистр, 0 - если нет: ";
                std::cin >> options[0];
                std::cout << "Введите 1 если хотите использовать спецсимволы, 0 - если нет: ";
                std::cin >> options[1];
                std::cout << "Введите 1 если хотите использовать цифры, 0 - если нет: ";
                std::cin >> options[2];
                std::cout<<"Введите пароль\n";
                std::cin>>str2;
                std::cout<<(password_check(lenghtpw, options, str2)?"Удовлетворяет":"Не удовлетворяет");
                break;
            case 2:
                std::cout << "Введите длину пароля: ";
                std::cin >> lenghtpw;
                std::cout << "Введите 1 если хотите использовать верхний регистр, 0 - если нет: ";
                std::cin >> options[0];
                std::cout << "Введите 1 если хотите использовать спецсимволы, 0 - если нет: ";
                std::cin >> options[1];
                std::cout << "Введите 1 если хотите использовать цифры, 0 - если нет: ";
                std::cin >> options[2];
                std::cout << get_random_password(lenghtpw, options);
                break;
                case 3:
                    super_check(); break;
        }
        break;

    }
    return 0;
}