//
// Created by ryan on 11/2/21.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>


#include "student.h"

using namespace std;
int RollNotToBeUpdate = 0;
student::student() {
    //create student.dat
    ofstream outFile("student.dat", ios::binary|ios::app);
    outFile.close();
    //create DuplicateCheckFile.txt
    ofstream outDFile("DuplicateCheckingFile.txt", ios::app);
    outDFile.close();
}
void student::getdata() {
    //take input as student data from user
    flag = false;
    cout <<"\n Enter the roll no of the student = ";
    cin >> Roll_no;
    //here we will check for duplication
    if(RollNotToBeUpdate != Roll_no)
        checkForDuplication();
    if(flag == true){
        cout << "Error duplicate record" << endl;
        return; //function returns;
    }
    //flag == false
    cout <<"\n\nEnter the Name of student = ";
    cin.ignore();
    cin.getline(Student_Name, 50);
    cout <<"\nEnter the marks in socialStudies out of 100 : ";
    cin >> Social_Studies_Marks;
    cout <<"\nEnter the marks in statistic out of 100 : ";
    cin >> Statistics_Marks;
    cout <<"\nEnter the marks in Maths out of 100 : ";
    cin >> Maths_Marks;
    cout <<"\nEnter the marks in English out of 100 : ";
    cin >> English_Marks;
    cout <<"Enter the marks in Computer out of 100 : ";
    cin >> Computer_Marks;
    CalculateGrade();
}
void student::checkForDuplication() {
    //check roll no
    int current_RollNo = 0;
    flag = false;
    ifstream infile("DuplicateCheckingFile.txt");
    while(!infile.eof()) {
        infile >> current_RollNo;
        if (current_RollNo == Roll_no) {
            flag = true;
        }//end of while
    }
    infile.close();
    if(flag == false){//no duplication
        //we write in roll no
        ofstream outfile("DuplicateCheckingFile.txt", ios::app);
        outfile << "\n" <<Roll_no;
        outfile.close();
    }

}
void student::CalculateGrade() {
    Student_Percentage = (Social_Studies_Marks + Statistics_Marks+ Maths_Marks + English_Marks + Computer_Marks)/500.0*100.0;
    if(Student_Percentage >= 80)
        Student_Grade='A';
    else if(Student_Percentage >= 70 && Student_Percentage < 80)
        Student_Grade='B';
    else if(Student_Percentage >= 60 && Student_Percentage < 70)
        Student_Grade='C';
    else
        Student_Grade='F';
}//end of calculation
void student::showData() {
    cout<<"\nRoll Number of student = " << Roll_no;
    cout<<"\nName of student = "<<Student_Name;
    cout<<"\nMarks in Social Studies = "<<Social_Studies_Marks;
    cout<<"\nMarks in Statistics = "<<Statistics_Marks;
    cout<<"\nMarks in Math= "<<Maths_Marks;
    cout<<"\nMarks in English = "<<English_Marks;
    cout<<"\nMarks in Computer = "<<Computer_Marks;
    cout<<"\nMarks in Percentage = "<<Student_Percentage;
    cout<<"\nGrade of student ="<<Student_Grade;
}
void student::tubularDisplay() {
    cout<<Roll_no<<setw(4)<<" " <<Student_Name<<setw(12-strlen(Student_Name))<<Social_Studies_Marks<<setw(6)<<Statistics_Marks<<setw(6)<< Maths_Marks<<setw(6)<<English_Marks<<setw(6)<<Computer_Marks<<setw(6)<<Student_Grade<< endl;
}
int student::GetStudentRollNo() {
    return Roll_no;
}

void student::showStudentRecord(int n) {
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile){//file not open
        cout <<"File could not be opened!";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    //take the roll no and find student record in file
    while (inFile.read(reinterpret_cast<char *>(this), sizeof(student))){
        if(GetStudentRollNo() == n){//the n roll no is found in the file student.dat
            showData();//prints record of current student
            flag = true;//record is found in the file student.dat
        }
    }//end of while loop
    inFile.close();
    if(flag == false){
        cout <<"\n\nrecord does not exist";
        cin.ignore();
        cin.get();

    }
}
void::student::Write_Student_Record_In_File(){
    ofstream outFile;
    outFile.open("student.dat", ios::binary | ios::app);

    getdata();//to get input from user

    if(flag == false){
        outFile.write(reinterpret_cast<char*>(this), sizeof(student));
        outFile.close();
        cout<<"\n\n student record has been created";
    }
    if(flag == true){
        cout <<"record not create due to duplication\n";
        outFile.close();
    }
    cin.ignore();
    cin.get();

}

void student::Update_Student_Record(int n) {
    RollNotToBeUpdate = n;
    bool found = false;
    fstream File;
    File.open("student.dat", ios::binary | ios::in | ios::out);
    if(!File){
        cout <<"File could not be open!";
        cin.ignore();
        cin.get();
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *>(this), sizeof (student));
        if(GetStudentRollNo() == n) {
            showData();
            cout << "\n\nPlease enter the nw details of student" << endl;
            getdata();
            if (flag == false) {//no duplication
                int pos = (-1) * static_cast<int>(sizeof(this));
                File.seekg(pos, ios::cur);
                File.write(reinterpret_cast<char *> (this), sizeof(student));
            }
            found = true;
        }
    }
    File.close();
    if(flag == true){
        cout <<"could not update because this RollNo already exists";
    }
    if(found == false){
        cout <<"\n\n Record Not Found";
    }
    cin.ignore();
    cin.get();

    if(flag == false && found == true && RollNotToBeUpdate != Roll_no){
        Delete_From_Duplicate_File(n);
    }
    RollNotToBeUpdate = 0;
}
void student::Delete_Student_Record(int n) {
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile){
        cout << "\nFile could not open";
        cin.ignore();
        cin.get();
        return;
    }

    ofstream outFile;
    outFile.open("Temp.dat", ios::out);
    inFile.seekg(0, ios::beg);
    while(inFile.read(reinterpret_cast<char *>(this), sizeof (student))){
        if(GetStudentRollNo() != n){
            outFile.write(reinterpret_cast<char *>(this), sizeof (student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout <<"\n\nRecord deleted";
    cin.ignore();
    cin.get();
    Delete_From_Duplicate_File(n);
}

void student::Delete_From_Duplicate_File(int n) {
    int curr_roll_no;
    ifstream inFile("DuplicateCheckingFile.txt");
    ofstream outFile("TempFile.txt");
    inFile.seekg(0, ios::beg);
    while(!inFile.eof()){
        inFile >> curr_roll_no;
        if(curr_roll_no != n){
            outFile<<"\n" <<curr_roll_no;
        }
    }

    inFile.close();
    outFile.close();

    remove("DuplicateCheckingFile.txt");
    rename("TempFile.txt", "DuplicateCheckingFile.txt");

    cin.ignore();
    cin.get();
}

void student::Show_Result_Menu() {
    //declaration
    char ch;
    int rno;
    // print menu
    cout << "\n\n\n\tResult Menu";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\n\t2. Student Report Card";
    cout << "\n\n\n\t3. Back to Main Menu";
    cout << "\n\n\n\tEnter Choice (1-3)";
    cin >> ch;
    switch(ch){
        case '1':
            Display_Class_Result();
            break;
        case '2':
            cout << "\n\n\tEnter the Roll No of the student = ";
            cin >> rno;
            showStudentRecord(rno);
            break;
        case '3':
            break;
        default: cout <<"\a";
    }
}
void student::Display_Class_Result() {
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile){
        cout << "File could not be opened";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\t\tAll Class Result \n\n";
    cout<<"============================================================\n";
    cout<<"R.No    Name     Soc  Stats  M     E     CS    Grade"<< endl;
    cout<<"============================================================\n";

    while(inFile.read(reinterpret_cast<char *>(this), sizeof (student))){
        tubularDisplay();
    }

    inFile.close();
    //clear input buffer
    cin.ignore();
    cin.get();
}
