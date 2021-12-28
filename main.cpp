#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "student.h"
using namespace std;


//here we will create student class for the system



void intro();
void entry_menu();
void display_all();
int main()
{
    //frame design

    //system("CLS");
    //system("color B1");
    char input;
    int num;
    student std_obj;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    intro();
    do {
        //system("cls");
        intro();
        cout << "\n\n\n\t\t\t\t\t Home Screen \n\n\n";
        cout << "\n\n\t1. Result Calculation System";
        cout << "\n\n\t2. Student Database Management System";
        cout << "\n\n\t3. Exit";
        cout << "\n\n\n\n\n Please Select Your Option (1-3)";
        cin >> input;
        switch (input) {
            case '1':
                //shows result calculation system
                std_obj.Show_Result_Menu();
                break;
            case '2':
                //shows students database management system code
                entry_menu();
                break;
            case '3':
                //user wants to exit the system
                break;
            default: cout << "\a";
        }
    }while(input != '3');
    //std::cout<<"Hello, World!"<<std::endl;

    //system("pause");
    return 0;
}

void intro(){
    cout <<"\n\n\n\n *** Welcome to student database management and result calculation system *** \n\n";
}
void entry_menu(){
    //variable declaration
    char ch;
    int num;
    student std;
    //system("cls");
    //print the menu on the output screen
    cout << "\n\n\n\t\t\tStudent Record Management Menu";
    cout << "\n\n\t1.Create student record";
    cout << "\n\n\t2.Show record of all student";
    cout << "\n\n\t3.Search student record";
    cout << "\n\n\t4.Update student record";
    cout << "\n\n\t5.Delete student record";
    cout << "\n\n\t6.Back to home screen";
    cout << "\n\n\n\n\tPlease enter your option (1-6)";
    //take input from user
    cin >> ch;
    //switch
    switch(ch){
        case '1':
            //create student record
            std.Write_Student_Record_In_File();
            break;
        case '2':
            //show all student record
            display_all();
            break;
        case '3':
            //searching a record of a student
            cout <<"\n\n\tPlease enter the roll no";
            cin >> num;
            std.showStudentRecord(num);
            break;
        case '4':
            //updating student's record
            cout <<"\n\n\tPlease enter the roll no";
            cin >> num;
            std.Update_Student_Record(num);
            break;
        case '5':
            //delete student's record
            cout <<"\n\n\tPlease enter the roll no";
            cin >> num;
            std.Delete_Student_Record(num);
            break;
        case '6':
            //go back to home screen
            break;
        default:
            cout <<"\a";
            entry_menu();
    }
}
void display_all(){
    student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile){
        cout << "File could not opened!!";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tDisplay all records.\n\n";
    while(inFile.read(reinterpret_cast<char*>(&st), sizeof(student))){
        st.showData();
        cout<<"\n\n======================================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}//end of display all records
