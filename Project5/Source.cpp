#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

class Student {

private:
    string group;
    vector<string> disciplines;
    int complete_works;
    int debts;
public:
    Student(const string& _group) : group(_group), complete_works(0), debts(0) {}


    vector<string> getDisciplines() const {
        return disciplines;
    }

    void addDiscipline(const string& discipline) {
        if (disciplines.end() == find(disciplines.begin(), disciplines.end(), discipline))
            disciplines.push_back(discipline);
        else
            cout << "Дисциплина \"" << discipline << "\" уже есть у студента" << endl;
    }


    void submitAssignment() {
        complete_works++;
    }

    void failAssignment() {
        debts++;
    }

    void plus_rep() {

        if (debts > 0) {

            debts--;
        }
        else {
            debts = debts;
        }

    }

    void POBEDA() {

        if (complete_works > 0) {

            complete_works--;
        }
        else {
            complete_works = complete_works;
        }
    }

    int getDebts() const {
        return debts;
    }

    string getGroup() const {
        return group;
    }

    int getComplete() const {
        return complete_works;
    }
};

class Teacher {

private:
    string discipline;
    vector<string> groups;

public:
    Teacher(const string& _discipline) : discipline(_discipline) {}

    void addGroup(const string& group) {
        groups.push_back(group);
    }

    vector<string> getGroups() const {
        return groups;
    }

    string getDiscipline() const {
        return discipline;
    }
};

class Group {
private:
    string name;
    vector<Student> students;
    vector<Teacher> teachers;

public:
    Group(const string& _name) : name(_name) {}

    vector<Student>& getStudents() {
        return students;
    }


    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }



    vector<Teacher> getTeachers() const {
        return teachers;
    }

    string getName() const {
        return name;
    }
};

class MPT {

private:

    vector<Teacher> teachers;

public:
    vector<Group> groups;
    void addGroup(const Group& group) {
        groups.push_back(group);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    void assignWork(Student& student) {
        student.submitAssignment();
    }

    void failWork(Student& student) {
        student.failAssignment();
    }

    void showStudentsInClass(Group& group) {
        cout << "Количество студентов в группе " << group.getName() << ": " << group.getStudents().size() << endl;
    }

    void showStudentInfo(const Student& student) {
        cout << "Информация о студенте:" << endl;
        cout << "Группа: " << student.getGroup() << endl;
        cout << "Дисциплины: ";
        for (const auto& discipline : student.getDisciplines()) {
            cout << discipline << ", ";
        }
        cout << endl;
        cout << "Количество практических работ: " << student.getComplete() << endl;
        cout << "Количество долгов: " << student.getDebts() << endl;
    }

    void showAllStudentsInfo() {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                showStudentInfo(student);
                cout << endl;
            }
        }
    }

    void showAllGroups() const {
        cout << "Все группы:" << endl;
        for (const auto& group : groups) {
            cout << group.getName() << endl;
        }
    }

    bool groupExists(const string& groupName) const {
        for (const auto& group : groups) {
            if (group.getName() == groupName) {
                return true;
            }
        }
        return false;
    }

    bool disciplineExists(const string& discipline) {
        for (auto& group : groups) {
            for (auto& student : group.getStudents()) {
                if (find(student.getDisciplines().begin(), student.getDisciplines().end(), discipline) != student.getDisciplines().end())
                    return true;
            }
        }
        return false;
    }

};

int main() {

    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "");

    MPT mpt;

    cout << "\n>>> ДОБРО ПОЖАЛОВАТЬ В МПТ <<<\n";
    string groupName;
    cout << "\nВведите название группы: ";
    cin >> groupName;

    Group group(groupName);

    Student student1(groupName);

    string discipline;
    cout << "Введите дисциплину для группы: ";
    cin >> discipline;
    student1.addDiscipline(discipline);

    Teacher teacher1(discipline);

    string groupForTeacher;

    do {
        cout << "Введите название группы для преподавателя: ";

        cin >> groupForTeacher;

        if (groupForTeacher != groupName) {
            cout << "Группы с таким названием не существует! Пожалуйста, попробуйте ещё раз! \n";
        }

    } while (groupForTeacher != groupName);

    teacher1.addGroup(groupForTeacher);

    group.addStudent(student1);
    group.addTeacher(teacher1);

    mpt.addGroup(group);
    mpt.addTeacher(teacher1);

    char choice;

    do {
        cout << "\nВыберите действие: \n 1 - Назначить работу группе\n 2 - Добавить долг группе\n 3 - Посмотреть количество студентов в группе\n 4 - Показать информацию о группе\n 5 - Добавить студента в группу\n 6 - Добавить новую группу\n 7 - Показать все группы\n 8 - Добавить новую дисциплину\n 9 - Простить долги группе\n s - Отметить практическую работу выполненной\n q - Выйти\n ";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "\nГруппе была назначена новая практическая работа\n ";
            mpt.assignWork(student1);
            break;
        case '2':
            cout << "\nГруппе был добавлен новый долг\n ";
            mpt.failWork(student1);
            break;
        case '3':
            mpt.showStudentsInClass(group);
            break;
        case '4':
            mpt.showStudentInfo(student1);
            break;
        case '5':
        {
            string newStudentGroup;
            cout << "\nВведите название группы для нового студента: ";
            cin >> newStudentGroup;

            if (!mpt.groupExists(newStudentGroup)) {
                cout << "\nГруппа с таким названием не существует!\n" << endl;
            }
            else {
                Student newStudent(newStudentGroup);
                group.addStudent(newStudent);
            }
            break;
        }
        case '6':
        {
            string newGroupName;
            cout << "\nВведите название новой группы: ";
            cin >> newGroupName;

            if (mpt.groupExists(newGroupName)) {
                cout << "\nГруппа с таким названием уже существует!\n" << endl;
            }
            else {
                Group newGroup(newGroupName);
                mpt.addGroup(newGroup);
            }
            break;
        }
        case '7':
            mpt.showAllGroups();
            break;
        case '8':
        {
            string newDiscipline;
            cout << "\nВведите название новой дисциплины: ";
            cin >> newDiscipline;

            student1.addDiscipline(newDiscipline);

            for (Student& student : group.getStudents()) {
                student.addDiscipline(newDiscipline);
            }

            cout << "\nДисциплина успешно добавлена!\n" << endl;

            break;
        }
        case '9':
            cout << "\nГруппе был прощен один долг, Вам кинули респект!";
            student1.plus_rep();
            break;
        case 's':
            student1.POBEDA();
            cout << "\nСтуденты выполнили практическую работу!\n";
            break;
        case 'q':
            cout << "Вы вышли из программы!";
            break;
        default:
            cout << "\nТакого в менюшке нет!!!\n" << endl;
            break;
        }

    } while (choice != 'q');

    return 0;
}