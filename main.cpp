/* Header Files */
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
using namespace std;

/* Template Class Vector */
template<class T>
class Vector {
    private:
        T *vect;
        T *temp;
        int size;
    public:
        Vector() {
            vect = new T[1];
            size = 1;
        }
        void push_back(T val) {
            vect[size - 1] = val;
            size++;
            temp = new T[size];
            for(int i = 0; i < size - 1; i++) {
                temp[i] = vect[i];
            }
            delete[] vect;
            vect = temp;
        }
        void clear() {
            delete[] vect;
            vect = new T[1];
            size = 1;
        }
        void print() {
            for(int i = 0; i < size - 1; i++) {
                cout << vect[i] << " ";
            }
            cout << endl;
        }
        int find(T val) {
            int res = -1;
            for(int i = 0; i < size - 1; i++) {
                if(!vect[i].compare(val)) {
                    res = i;
                    break;
                }
            }
            return res;
        }
        bool compare(string password, int index) {
            return password.compare(vect[index]);
        }
        int vSize() {
            return (size - 1);
        }
        T get(int i) {
            return vect[i];
        }
};

/* Structure for Date */
struct Date {
    int day, month, year;
};

/* Base Class For Inheritance */
class Complaint {
    private:
        string desc, room, rollno, temp;
        int type, c_id, status;
        Date c_date;

        /* Object for File Handling */
        fstream comp, c_temp;

        /* Template Class Object */
        Vector<string> complains[7], stud[2];
        int c_it;
    protected:
        int choice;
    public:
        /* Inline Function */
        inline Complaint();

        /* Static Variables */
        static int who_is_logged;
        static string logged_roll;

        /* Virtual Function For Menu*/
        virtual int menu() {
            cout << "--------------- Complaint Management System ---------------" << endl;
            cout << "----- Welcome Guest -----" << endl;
            cout << "1. Create Complaint" << endl;
            cout << "2. Login" << endl;
            cout << "~  Exit" << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << "Enter Your Choice: ";
            cin >> choice;
            return choice;
        }
        void cstatus() {
            cout << "Complaint Status" << endl;
            cout << "1. New" << endl;
            cout << "2. Resolved" << endl;
            cout << "3. Cancelled" << endl;
            cout << "4. Processing" << endl;
            cout << "Updated Status: ";
            cin >> status;
        }
        void category() {
            cout << "Complaint Category" << endl;
            cout << "1. General" << endl;
            cout << "2. Electrical" << endl;
            cout << "3. Plumbing" << endl;
            cout << "4. Carpentary" << endl;
            cout << "Enter category: ";
            cin >> type;
        }
        void create() {
            system("cls");
            category();
            cout << "Enter Today's Date(dd mm yyyy): ";
            cin >> c_date.day >> c_date.month >> c_date.year;
            cout << "Enter Complaint: ";
            getline(cin >> ws, desc);
            cout << "Enter Room No: ";
            cin.ignore();
            getline(cin, room);
            rollno = logged_roll;
            if(who_is_logged == 0) {
                cout << "Enter Roll No: ";
                cin >> rollno;
            }
            status = 1;
            comp.open("complaint.dat", ios::app);
            if(comp) {
                comp << c_id << "\n" << c_date.day << "-" << c_date.month << "-" << c_date.year << "\n";
                comp << type << "\n" << desc << "\n" << room << "\n" << rollno << "\n" << status << "\n";
                cout << "--- Complaint Created Successfully ---";
                comp.close();
                comp.open("complaints-student.dat", ios::app);
                comp << c_id << "\n" << rollno << "\n";
                comp.close();
                if(who_is_logged == 0) {
                    comp.open("student.dat");
                    int i = 0;
                    while(getline(comp, temp)) {
                        if(i % 2  == 0)
                            stud[0].push_back(temp);
                        else
                            stud[1].push_back(temp);
                        i++;
                    }
                    comp.close();
                    c_it = stud[0].find(rollno);
                    if(c_it == -1) {
                        comp.open("student.dat", ios::app);
                        comp << rollno << "\n";
                        comp << rollno.substr(7, 2) << "\n";
                        comp.close();
                    }
                }
                c_id++;
            } else {
                cout << "--- Something Went Wrong! ---";
            }
        }
        void head() {
            cout << setw(15) << "Complaint ID" << setw(15) << "Date" << setw(15) << "Type";
            cout << setw(30) << "Description" << setw(15) << "Room No" << setw(15) << "Roll No";
            cout << setw(15) << "Status" << endl;
        }
        void view() {
            cout << "Enter Complaint ID: ";
            cin >> c_id;
            comp.open("complaint.dat");
            int i = 0;
            while(getline(comp, temp)) {
                if(i == 7)
                    i = 0;
                complains[i].push_back(temp);
                i++;
            }
            comp.close();
            c_it = complains[0].find(to_string(c_id));
            if(c_it != -1) {
                head();
                int index = c_it;
                cout << setw(15) << complains[0].get(index);
                cout << setw(15) << complains[1].get(index);
                if(!complains[2].compare("1", index))
                    cout << setw(15) << "General";
                else if(!complains[2].compare("2", index))
                    cout << setw(15) << "Electrical";
                else if(!complains[2].compare("3", index))
                    cout << setw(15) << "Plumbing";
                else
                    cout << setw(15) << "Carpentary";
                cout << setw(30) << complains[3].get(index);
                cout << setw(15) << complains[4].get(index);
                cout << setw(15) << complains[5].get(index);
                if(!complains[6].compare("1", index)) {
                    cout << setw(15) << "New";
                } else if(!complains[6].compare("2", index)) {
                    cout << setw(15) << "Resolved";
                } else if(!complains[6].compare("3", index)) {
                    cout << setw(15) << "Cancelled";
                } else {
                    cout << setw(15) << "Processing";
                }
            } else {
                cout << "----- No Complaint Found -----" << endl;
            }
        }
        void update(int ciD = 0, int stat = 0) {
            if(ciD == 0) {
                cout << "Enter Complaint ID: ";
                cin >> c_id;
            } else {
                c_id = ciD;
            }
            int i = 0;
            while(i < 7) {
                complains[i].clear();
                i++;
            }
            comp.open("complaint.dat");
            i = 0;
            while(getline(comp, temp)) {
                if(i == 7)
                    i = 0;
                complains[i].push_back(temp);
                i++;
            }
            comp.close();
            c_it = complains[0].find(to_string(c_id));
            if(c_it != -1) {
                if(ciD == 0) {
                    cout << "Current Status: ";
                    int index = c_it;
                    if(!complains[6].compare("1", index)) {
                        cout << "New";
                    } else if(!complains[6].compare("2", index)) {
                        cout << "Resolved";
                    } else if(!complains[6].compare("3", index)) {
                        cout << "Cancelled";
                    } else {
                        cout << "Processing";
                    }
                    cout << endl;
                    cstatus();
                } else {
                    status = stat;
                }
                int lineNo = c_it * 7 + 7;
                int i = 1;
                comp.open("complaint.dat");
                c_temp.open("temp.dat", fstream::out);
                while(getline(comp, temp)) {
                    if(i == lineNo) {
                        c_temp << status << "\n";
                    } else {
                        c_temp << temp << "\n";
                    }
                    i++;
                }
                c_temp.close();
                comp.close();
                remove("complaint.dat");
                rename("temp.dat", "complaint.dat");
            } else {
                cout << "No Complain Found ....." << endl;
            }
        }
        void print() {
            head();
            int i = 0;
            while(i < 7) {
                complains[i].clear();
                i++;
            }
            comp.open("complaint.dat");
            i = 0;
            while(getline(comp, temp)) {
                if(i == 7)
                    i = 0;
                    complains[i].push_back(temp);
                i++;
            }
            comp.close();
            int index = 0;
            while(index < complains[0].vSize()) {
                cout << setw(15) << complains[0].get(index);
                cout << setw(15) << complains[1].get(index);
                if(!complains[2].compare("1", index))
                    cout << setw(15) << "General";
                else if(!complains[2].compare("2", index))
                    cout << setw(15) << "Electrical";
                else if(!complains[2].compare("3", index))
                    cout << setw(15) << "Plumbing";
                else
                    cout << setw(15) << "Carpentary";
                cout << setw(30) << complains[3].get(index);
                cout << setw(15) << complains[4].get(index);
                cout << setw(15) << complains[5].get(index);
                if(!complains[6].compare("1", index)) {
                    cout << setw(15) << "New";
                } else if(!complains[6].compare("2", index)) {
                    cout << setw(15) << "Resolved";
                } else if(!complains[6].compare("3", index)) {
                    cout << setw(15) << "Cancelled";
                } else {
                    cout << setw(15) << "Processing";
                }
                cout << endl;
                index++;
            }
        }
        void print(string logged) {
            head();
            int i = 0;
            while(i < 7) {
                complains[i].clear();
                i++;
            }
            comp.open("complaint.dat");
            i = 0;
            while(getline(comp, temp)) {
                if(i == 7)
                    i = 0;
                complains[i].push_back(temp);
                i++;
            }
            comp.close();
            stud[0].clear();
            stud[1].clear();
            comp.open("complaints-student.dat");
            i = 0;
            while(getline(comp, temp)) {
                if(i % 2 == 0)
                    stud[0].push_back(temp);
                else
                    stud[1].push_back(temp);
                i++;
            }
            i = 0;
            while(i < stud[0].vSize()) {
                if(!logged_roll.compare(stud[1].get(i))) {
                    c_it = complains[0].find(stud[0].get(i));
                    if(c_it != -1) {
                        int index = c_it;
                        cout << setw(15) << complains[0].get(index);
                        cout << setw(15) << complains[1].get(index);
                        if(!complains[2].compare("1", index))
                            cout << setw(15) << "General";
                        else if(!complains[2].compare("2", index))
                            cout << setw(15) << "Electrical";
                        else if(!complains[2].compare("3", index))
                            cout << setw(15) << "Plumbing";
                        else
                            cout << setw(15) << "Carpentary";
                        cout << setw(30) << complains[3].get(index);
                        cout << setw(15) << complains[4].get(index);
                        cout << setw(15) << complains[5].get(index);
                        if(!complains[6].compare("1", index)) {
                            cout << setw(15) << "New";
                        } else if(!complains[6].compare("2", index)) {
                            cout << setw(15) << "Resolved";
                        } else if(!complains[6].compare("3", index)) {
                            cout << setw(15) << "Cancelled";
                        } else {
                            cout << setw(15) << "Processing";
                        }
                        cout << endl;
                    }
                }
                i++;
            }
            if(i == 0)
                cout << "----- No Complaint Found -----" << endl;
            comp.close();
        }
        void cancel() {
            cout << "Enter Complaint ID: ";
            cin >> c_id;
            stud[0].clear();
            stud[1].clear();
            comp.open("complaints-student.dat");
            int i = 0;
            while(getline(comp, temp)) {
                if(i % 2 == 0)
                    stud[0].push_back(temp);
                else
                    stud[1].push_back(temp);
                i++;
            }
            comp.close();
            c_it = stud[0].find(to_string(c_id));
            if(c_it != -1) {
                if(!logged_roll.compare(stud[1].get(c_it))) {
                    char ch;
                    cout << "Are You Sure To Cancel Complaint(Y: Yes, N: No): ";
                    cin >> ch;
                    if(ch == 'Y' || ch == 'y') {
                        update(c_id, 3);
                    }
                }
            } else {
                cout << "----- No Complaint Found -----" << endl;
            }
        }
        void printCategory() {
            category();
            head();
            int i = 0;
            while(i < 7) {
                complains[i].clear();
                i++;
            }
            comp.open("complaint.dat");
            i = 0;
            while(getline(comp, temp)) {
                if(i == 7)
                    i = 0;
                    complains[i].push_back(temp);
                i++;
            }
            comp.close();
            int index = 0;
            while(index < complains[0].vSize()) {
                if(!complains[2].get(index).compare(to_string(type))) {
                    cout << setw(15) << complains[0].get(index);
                    cout << setw(15) << complains[1].get(index);
                    if(!complains[2].compare("1", index))
                        cout << setw(15) << "General";
                    else if(!complains[2].compare("2", index))
                        cout << setw(15) << "Electrical";
                    else if(!complains[2].compare("3", index))
                        cout << setw(15) << "Plumbing";
                    else
                        cout << setw(15) << "Carpentary";
                    cout << setw(30) << complains[3].get(index);
                    cout << setw(15) << complains[4].get(index);
                    cout << setw(15) << complains[5].get(index);
                    if(!complains[6].compare("1", index)) {
                        cout << setw(15) << "New";
                    } else if(!complains[6].compare("2", index)) {
                        cout << setw(15) << "Resolved";
                    } else if(!complains[6].compare("3", index)) {
                        cout << setw(15) << "Cancelled";
                    } else {
                        cout << setw(15) << "Processing";
                    }
                    cout << endl;
                }
                index++;
            }
            if(index == 0) {
                cout << "----- No Complaint Found -----" << endl;
            }
        }

        /* Destructor */
        ~Complaint() {}
};

/* Consrtuctor (Checking for last complaint id) */
Complaint::Complaint() {
    comp.open("complaint.dat");
    int i = 0;
    c_id = 0;
    while(getline(comp, temp)) {
        if(i % 7 == 0 && !empty(temp))
            c_id = stoi(temp);
        i++;
    }
    c_id++;
    comp.close();
}

/* Forward Declaration of Second Class */
class Student;

/* First Derived Class */
class Admin : public Complaint {
    private:
        fstream admin;
    public:
        friend inline void login(Admin &, Student &);
        friend void logout(Admin &, Student &);
        int menu() {
            cout << "--------------- Complaint Management System ---------------" << endl;
            cout << "----- Welcome Admin -----" << endl;
            cout << "1. View Complaint" << endl;
            cout << "2. Update Complaint Status" << endl;
            cout << "3. Print Complaints" << endl;
            cout << "4. Category Complaints" << endl;
            cout << "5. Logout" << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << "Enter Your Choice: ";
            cin >> choice;
            return choice;
        }
};

/* Second Derived Class */
class Student : public Complaint {
    private:
        fstream student;
    public:
        friend inline void login(Admin &, Student &);
        friend void logout(Admin &, Student &);
        int menu() {
            cout << "--------------- Complaint Management System ---------------" << endl;
            cout << "----- Welcome Student -----" << endl;
            cout << "1. Create Complaint" << endl;
            cout << "2. View All Complaint" << endl;
            cout << "3. Cancel Complaint" << endl;
            cout << "4. Logout" << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << "Enter Your Choice: ";
            cin >> choice;
            return choice;
        }
};

/* Friend Function */
void login(Admin &A, Student &S) {
    system("cls");
    cout << "--------------- Complaint Management System ---------------" << endl;
    string username, password, u;
    Vector<string> ad[2];
    Vector<string> stud[2];
    int it;
    cout << "Enter Username: ";
    cin >> username;
    int i = 0;
    A.admin.open("admin.dat");
    while(getline(A.admin, u)) {
        if(i % 2 == 0)
            ad[0].push_back(u);
        else
            ad[1].push_back(u);
        i++;
    }
    A.admin.close();
    i = 0;
    S.student.open("student.dat");
    while(getline(S.student, u)) {
        if(i % 2 == 0)
            stud[0].push_back(u);
        else
            stud[1].push_back(u);
        i++;
    }
    S.student.close();
    it = ad[0].find(username);
    if(it != -1) {
        cout << "Enter Password: ";
        cin >> password;
        if(!ad[1].compare(password, it)) {
            cout << "Admin Logged In Successfully";
            Complaint::who_is_logged = 1;
        } else {
            cout << "Wrong Admin Password.... Back to Main Menu";
        }
    } else {
        it = stud[0].find(username);
        if(it != -1) {
            cout << "Enter Password: ";
            cin >> password;
            if(!stud[1].compare(password, it)) {
                Complaint::logged_roll = username;
                cout << "Student Logged In Successfully";
                Complaint::who_is_logged = 2;
            } else {
                cout << "Wrong Password.... Back to Main Menu";
            }
        } else {
            cout << "User Not Found..... Back to Main Menu";
        }
    }
}

/* Friend Function */
void logout(Admin &A, Student &S) {
    if(Complaint::who_is_logged == 1) {
        cout << "Admin Logged out";
    } else {
        cout << "Student Logged Out";
    }
    Complaint::who_is_logged = 0;
}

/* Static Variables Definition */
int Complaint::who_is_logged = 0;
string Complaint::logged_roll = "";

/* Main Function */
int main() {
    Admin A;
    Student S;
    Complaint C;
    int i = 1;
    while(i) {
        system("cls");
        Complaint *obj;
        int log = Complaint::who_is_logged;
        string role = Complaint::logged_roll;
        if(log == 0) {
            obj = &C;
        } else if(log == 1) {
            obj = &A;
        } else {
            obj = &S;
        }
        int choice = obj->menu();
        switch(choice) {
            case 1:
                if(log == 0 || log == 2) {
                    obj->create();
                } else {
                    obj->view();
                }
                break;
            case 2:
                if(log == 0) {
                    login(A, S);
                } else if(log == 1) {
                    obj->update();
                } else {
                    obj->print(role);
                }
                break;
            case 3:
                if(log == 1) {
                    obj->print();
                } else if(log == 2) {
                    obj->cancel();
                } else {
                    i = 0;
                }
                break;
            case 4:
                if(log == 1) {
                    obj->printCategory();
                } else if(log == 2) {
                    logout(A, S);
                } else {
                    i = 0;
                }
                break;
            case 5:
                if(log == 1) {
                    logout(A, S);
                    break;
                }
            default:
                if(log != 0) {
                    cout << "Please Choose Correctly" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                } else {
                    cout << "\n--------------- Thanks For Visiting Us ---------------" << endl;
                    i = 0;
                }
        }
        cout << endl;
        system("pause");
    }

    return 0;
}