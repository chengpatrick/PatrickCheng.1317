// 4252lab3.cpp
//Author: Patrick Cheng
//compilation command: g++ -o lab3 lab3.cpp
//then type lab3 to run the code

//project name: calculator
//Adding and subtracting numbers with an arbitrary large number of decimal digits

#include <iostream>
#include <algorithm>

using namespace std;

const int l = 10;

// check to see if the char num entered is valid or not
bool checkValidNum(char *num, int digit);

//addition for the numbers
void arrayAddition(int A[], int B[],int ans[],int digitA,int digitB,int& digitAns);

//subtraction for the numbers
void arraySubtraction(int A[], int B[], int ans[], int digitA, int digitB, int& digitAns);

//Function to reverse array
void reverseArray(int arr[], int start, int end);

//Function to compare array, return arr1 will always be greater or equal to arr2
void compareArray(int arr1[],int arr2[]);

/* check to see if the char num entered is valid or not */
bool checkValidNum(char *num, int digit) {
    int i = 0;
    bool lead_zero = true;
    bool error = false;

    while (i < digit) {
        //cout << sizeof(num) << endl;
        //cout << "in loop num is: " << num << endl;
        if (lead_zero) {
            if (num[i] - '0' < 1 || num[i] - '0' > 9) {
                error = true;
            }
        }
        else {
            if (num[i] - '0' < 0 || num[i] - '0' > 9) {
                error= true;
            }
        }
        lead_zero = false;
        i++;
    }

    return !error;
}

/* addition for the numbers*/
void arrayAddition(int A[], int B[],int ans[],int digitA,int digitB,int& digitAns) {
    int tempAns[l];
    int revA[l], revB[l];

    for (int i = 0; i < digitA; i++) {
        revA[i] = A[i];
    }
    for (int i = 0; i < digitB; i++) {
        revB[i] = B[i];
    }
    //array of the reverses
    reverseArray(revA, 0, digitA-1);
    reverseArray(revB, 0, digitB- 1);

    /*
    cout << "rev a is ";
    for (int i = 0; i < digitA; i++) {
        cout << revA[i];
    }
    cout << endl;

    cout << "rev b is ";
    for (int i = 0; i < digitB; i++) {
        cout << revB[i];
    }
    cout << endl;
    */

    int temp, i;
    int min = std::min(digitA, digitB), max = std::max(digitA, digitB);
    bool isOver = false;

    
    for (i = 0; i < min; i++) {
        temp = revA[i] + revB[i];
        if (isOver==true) {
            temp++;
            isOver = false;
        }
        if (temp > 9) {
            isOver = true;
            temp -= 10;
        }
        ans[i] = temp;
    }

    for (i = min; i < max; i++){
        if (digitA > digitB) {
            temp = revA[i];
        }
        else {
            temp = revB[i];
        }
        if (isOver == true) {
            temp++;
            isOver = false;
        }
        if (temp > 9) {
            isOver = true;
            temp -= 10;
        }
        ans[i] = temp;
    }

    if (isOver == true) {
        ans[max] = 1;
        max++;
    }
    reverseArray(ans, 0, max-1);
    digitAns = max;
}

/* subtraction for the numbers*/
void arraySubtraction(int A[], int B[], int ans[], int digitA, int digitB, int& digitAns) {
    int tempAns[l];
    int revA[l], revB[l];


        //for subtraction, revA is always greater or equal to revB
        for (int i = 0; i < digitA; i++) {
            revA[i] = A[i];
        }
        for (int i = 0; i < digitB; i++) {
            revB[i] = B[i];
        }
    //array of the reverses
    reverseArray(revA, 0, digitA - 1);
    reverseArray(revB, 0, digitB - 1);

    /*
    cout << "rev a is ";
    for (int i = 0; i < digitA; i++) {
        cout << revA[i];
    }
    cout << endl;

    cout << "rev b is ";
    for (int i = 0; i < digitB; i++) {
        cout << revB[i];
    }
    cout << endl;
    */

    int temp, i;
    int min = std::min(digitA, digitB), max = std::max(digitA, digitB);
    bool isUnder = false;


    for (i = 0; i < min; i++) {
        temp = revA[i] - revB[i];
        if (isUnder == true) {
            temp--;
            isUnder = false;           
        }
        if (temp <0) {
            isUnder = true;
            temp += 10;
        }
        ans[i] = temp;
    }

    for (i = min; i < max; i++) {
        if (digitA > digitB) {
            temp = revA[i];
        }
        else {
            temp = revB[i];
        }
        if (isUnder == true) {
            temp--;
            isUnder = false;
            if (temp < 1)max--;
        }
        if (temp < 0) {
            isUnder = true;
            temp += 10;
        }
        ans[i] = temp;
    }

    if (isUnder == true) {
        cout << "max is " << ans[max] << endl;
        ans[max] --;
        max--;
    }

    i = max;
    while (max > 1 && ans[i-1] == 0) {
        max--;
        i--;
    }

    reverseArray(ans, 0, max - 1);
    digitAns = max;
}

/* Function to reverse array */
void reverseArray(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        //cout << temp << " " << start <<" "<<arr[end]<<" "<<end<< endl;
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

//Function to compare array, return true if arr1 is greater or equal to arr2
bool compareArray(int arr1[], int arr2[], int digitA, int digitB) {
    
    if (digitA > digitB)return true;
    if (digitB > digitA)return false;
    
    for (int i = 0; i < digitA; i++) {
        if (arr1[i] < arr2[i])return false;
    }
    return true;
}

int main()
{
    char input='y';
    bool error_flag = false, aBigger = false;
    int i = 0, digit = 0, sizeA, sizeB;

    while (tolower(input) !='q') {
        char numA[25];
        int A[l];
        char next;
        digit = 0;
        error_flag = false;

        //enter integer A
        cout << "Enter A integer (up to "<<l<<" digits): ";
        cin.get(next);
        while (next != '\n') {
            numA[digit] = next;
            if(digit<l) A[digit] = next - '0';
            digit++;
            cin.get(next);
        }
        numA[digit] = '\0';
        cout << "A= " << numA<<endl;

        if (digit > l) {
            cout << "Too many characters"<<endl;
            error_flag = true;
            goto restart;
        }

        if (digit == 0) {
            cout << "Nothing entered" << endl;
            error_flag = true;
            goto restart;
        }

        //check if number is valid or not
        if (error_flag = !checkValidNum(numA, digit)) {
            cout << "Illegal characters(s)" << endl;
            goto error;
        }

        sizeA = digit;

        char numB[25];
        digit = 0;
        int B[l];

        //enter integer B
        cout << "Enter B integer (up to "<<l<<" digits): ";
        cin.get(next);
        while (next != '\n') {
            numB[digit] = next;
            if(digit<l) B[digit] = next - '0';
            digit++;
            cin.get(next);
        }
        numB[digit] = '\0';
        cout << "B= " << numB << endl;

        if (digit > l) {
            cout << "Too many characters"<<endl;
            error_flag = true;
            goto restart;
        }

        if (digit == 0) {
            cout << "Nothing entered" << endl;
            error_flag = true;
            goto restart;
        }

        //check if number is valid or not
        if (error_flag = !checkValidNum(numB, digit)) {
            cout << "Illegal characters(s)" << endl;
            goto error;
        }

        sizeB = digit;        

        int ansAdd[l + 1], sizeAnsAdd;
        arrayAddition(A, B, ansAdd,sizeA,sizeB,sizeAnsAdd);
        cout << "A+B= +";
        for (int i = 0; i < sizeAnsAdd; i++) {
            cout << ansAdd[i];
        }
        cout << endl;

        aBigger = compareArray(A, B, sizeA, sizeB);
        
        int ansSub[l + 1], sizeAnsSub;
        if (aBigger) {
            arraySubtraction(A, B, ansSub, sizeA, sizeB, sizeAnsSub);
            if (ansSub[0] == 0) {
                cout << "A-B= ";
            }
            else {
                cout << "A-B= +";
            }
        }
        else {
            arraySubtraction(B, A, ansSub, sizeB, sizeA, sizeAnsSub);
            cout << "A-B= -";
        }
        for (int i = 0; i < sizeAnsSub; i++) {
            cout << ansSub[i];
            //if (ansSub[0] == 0)break;
        }
        cout << endl;
        

    error:
        if (error_flag) {
            //cout << "Error" << endl;
            goto restart;
        }

    restart:
        cout << "Q or q to exit: ";
        cin.get(input);
        cin.clear();
        cin.ignore(200, '\n');       
    }

end:
    cout << "Exiting program" << endl;
    return 0;
}
