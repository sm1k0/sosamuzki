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
            cout << "���������� \"" << discipline << "\" ��� ���� � ��������" << endl;
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
        cout << "���������� ��������� � ������ " << group.getName() << ": " << group.getStudents().size() << endl;
    }

    void showStudentInfo(const Student& student) {
        cout << "���������� � ��������:" << endl;
        cout << "������: " << student.getGroup() << endl;
        cout << "����������: ";
        for (const auto& discipline : student.getDisciplines()) {
            cout << discipline << ", ";
        }
        cout << endl;
        cout << "���������� ������������ �����: " << student.getComplete() << endl;
        cout << "���������� ������: " << student.getDebts() << endl;
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
        cout << "��� ������:" << endl;
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

    cout << "\n>>> ����� ���������� � ��� <<<\n";
    string groupName;
    cout << "\n������� �������� ������: ";
    cin >> groupName;

    Group group(groupName);

    Student student1(groupName);

    string discipline;
    cout << "������� ���������� ��� ������: ";
    cin >> discipline;
    student1.addDiscipline(discipline);

    Teacher teacher1(discipline);

    string groupForTeacher;

    do {
        cout << "������� �������� ������ ��� �������������: ";

        cin >> groupForTeacher;

        if (groupForTeacher != groupName) {
            cout << "������ � ����� ��������� �� ����������! ����������, ���������� ��� ���! \n";
        }

    } while (groupForTeacher != groupName);

    teacher1.addGroup(groupForTeacher);

    group.addStudent(student1);
    group.addTeacher(teacher1);

    mpt.addGroup(group);
    mpt.addTeacher(teacher1);

    char choice;

    do {
        cout << "\n�������� ��������: \n 1 - ��������� ������ ������\n 2 - �������� ���� ������\n 3 - ���������� ���������� ��������� � ������\n 4 - �������� ���������� � ������\n 5 - �������� �������� � ������\n 6 - �������� ����� ������\n 7 - �������� ��� ������\n 8 - �������� ����� ����������\n 9 - �������� ����� ������\n s - �������� ������������ ������ �����������\n q - �����\n ";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "\n������ ���� ��������� ����� ������������ ������\n ";
            mpt.assignWork(student1);
            break;
        case '2':
            cout << "\n������ ��� �������� ����� ����\n ";
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
            cout << "\n������� �������� ������ ��� ������ ��������: ";
            cin >> newStudentGroup;

            if (!mpt.groupExists(newStudentGroup)) {
                cout << "\n������ � ����� ��������� �� ����������!\n" << endl;
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
            cout << "\n������� �������� ����� ������: ";
            cin >> newGroupName;

            if (mpt.groupExists(newGroupName)) {
                cout << "\n������ � ����� ��������� ��� ����������!\n" << endl;
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
            cout << "\n������� �������� ����� ����������: ";
            cin >> newDiscipline;

            student1.addDiscipline(newDiscipline);

            for (Student& student : group.getStudents()) {
                student.addDiscipline(newDiscipline);
            }

            cout << "\n���������� ������� ���������!\n" << endl;

            break;
        }
        case '9':
            cout << "\n������ ��� ������ ���� ����, ��� ������ �������!";
            student1.plus_rep();
            break;
        case 's':
            student1.POBEDA();
            cout << "\n�������� ��������� ������������ ������!\n";
            break;
        case 'q':
            cout << "�� ����� �� ���������!";
            break;
        default:
            cout << "\n������ � ������� ���!!!\n" << endl;
            break;
        }

    } while (choice != 'q');

    return 0;
}