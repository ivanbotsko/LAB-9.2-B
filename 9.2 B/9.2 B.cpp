#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;

enum Speciality { CS, INF, ME, PI, TN };
string specialityStr[] = { "Комп'ютерні науки", "Інформатика", "Механіка та енергетика", "Прикладна інформатика", "Телекомунікації та радіотехніка" };

struct Student {
    string surname;
    unsigned course;
    Speciality speciality;
    int physics;
    int math;
    union {
        int programming;
        int numericalMethods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade);

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    string surname;
    unsigned course;
    double avgGrade;
    cout << "Введіть прізвище студента: "; cin >> surname;
    cout << "Введіть курс: "; cin >> course;
    cout << "Введіть середній бал: "; cin >> avgGrade;

    int idx = BinSearch(s, N, surname, course, avgGrade);
    if (idx != -1)
        cout << "Студент " << surname << " знаходиться на " << course << " курсі." << endl;
    else
        cout << "Студент " << surname << " не знайдено на " << course << " курсі." << endl;

    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "Введіть дані про " << i + 1 << "-го студента:" << endl;
        cin.get(); // Очищення буфера введення для коректного введення прізвища
        cin.sync(); 

        cout << " Прізвище: "; getline(cin, s[i].surname);
        cout << " Курс: "; cin >> s[i].course;
        cout << " Оберіть спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Механіка та енергетика, 3 - Прикладна інформатика, 4 - Телекомунікації та радіотехніка): ";
        cin >> speciality;
        s[i].speciality = (Speciality)speciality;
        cout << " Оцінка з фізики: "; cin >> s[i].physics;
        cout << " Оцінка з математики: "; cin >> s[i].math;
        switch (s[i].speciality) {
        case CS:
            cout << " Оцінка з програмування: "; cin >> s[i].programming;
            break;
        case INF:
            cout << " Оцінка з чисельних методів: "; cin >> s[i].numericalMethods;
            break;
        case ME:
        case PI:
        case TN:
            cout << " Оцінка з педагогіки: "; cin >> s[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "=================================================================================================================================================================" << endl;
    cout << "| " << setw(2) << "№" << " |" << setw(15) << "Прізвище" << " |" << setw(6) << "Курс" << " |" << setw(25) << "Спеціальність" << " |" << setw(8) << "Фізика" << " |" << setw(13) << "Математика" << " |" << setw(15) << "Програмування" << " |" << setw(15) << "Чисельні методи" << " |" << setw(10) << "Педагогіка" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[i].surname
            << "| " << setw(5) << s[i].course << " "
            << "| " << setw(25) << specialityStr[s[i].speciality]
            << "| " << setw(8) << s[i].physics
            << "| " << setw(12) << s[i].math << " ";
        switch (s[i].speciality) {
        case CS:
            cout << "| " << setw(15) << s[i].programming
                << "| " << setw(15) << " "
                << "| " << setw(15) << " " << endl;
            break;
        case INF:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].numericalMethods
                << "| " << setw(15) << " " << endl;
            break;
        case ME:
        case PI:
        case TN:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "====================================================================================================" << endl;
    cout << endl;


}


int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double avg = (s[m].physics + s[m].math + (s[m].speciality == CS ? s[m].programming : (s[m].speciality == INF ? s[m].numericalMethods : s[m].pedagogy))) / 3.0;
        if (s[m].surname == surname && s[m].course == course && avg == avgGrade)
            return m;
        if ((s[m].surname < surname)
            || (s[m].surname == surname && s[m].course < course)
            || (s[m].surname == surname && s[m].course == course && avg < avgGrade)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
