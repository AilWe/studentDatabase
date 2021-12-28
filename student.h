//
// Created by ryan on 11/2/21.
//

#ifndef STUDENTDATABASE_STUDENT_H
#define STUDENTDATABASE_STUDENT_H
class student{
private:
    char Student_Name[50];
    int Roll_no;
    int Social_Studies_Marks, Statistics_Marks, Maths_Marks, English_Marks, Computer_Marks;
    double Student_Percentage;
    char Student_Grade;
    bool flag;//input roll no
    void CalculateGrade();

public:
    student();
    void getdata();
    void checkForDuplication();
    void showData();
    void tubularDisplay();
    int GetStudentRollNo();
    void showStudentRecord(int);
    void Write_Student_Record_In_File();
    void Update_Student_Record(int);
    void Delete_Student_Record(int);
    void Delete_From_Duplicate_File(int);
    void Show_Result_Menu();
    void Display_Class_Result();


};//shows the end of class
#endif //STUDENTDATABASE_STUDENT_H
