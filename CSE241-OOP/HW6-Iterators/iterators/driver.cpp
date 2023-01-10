#include "pfarray.cpp"

using SPC::PFArray;
using std::cout;
using std::endl;
using std::boolalpha;
using std::find;
using std::for_each;
using std::sort;

int main() {
    PFArray<int> int_array;
    cout<<endl<<endl<<"Empty integer array has been created! Check if array is empty: "<<boolalpha<<int_array.empty()<<endl;
    
    PFArray<char> char_array;
    cout<<"Empty char array has been created! Check if array is empty: "<<boolalpha<<char_array.empty()<<endl;

    int_array.push(9);
    int_array.push(7);

    cout<<endl<<"Numbers '9' and '7' have been pushed into int_array."<<endl<< "Size: "<<int_array.size()<<endl<<"Array: ";
    for (auto i : int_array) cout<<i<<" ";
    cout<<endl<<"Is empty?: "<<boolalpha<<int_array.empty()<<endl;

    char_array.push('a');
    char_array.push('b');
    char_array.push('c');

    cout<<endl<<"Characters 'a', 'b' and 'c' have been pushed into char_array."<<endl<<"Size: "<<char_array.size()<<endl<<"Array: ";
    for (auto c : char_array) cout<<c<<" ";
    cout<<endl<<"Is empty?: "<<boolalpha<<char_array.empty()<<endl<<endl;

    auto iti = int_array.begin();
    int_array.erase(iti);
    cout<<"Erasing the first index of int_array."<<endl<< "Size: "<<int_array.size()<<endl<<"Array: ";
    for (auto i : int_array) cout<<i<<" ";

    auto itc = char_array.begin();
    itc++;
    char_array.erase(itc);
    cout<<endl<<endl<<"Erasing the second index of char_array."<<endl<< "Size: "<<char_array.size()<<endl<<"Array: ";
    for (auto c : char_array) cout<<c<<" ";

    char_array.clear();
    cout<<endl<<endl<<"Clearing all content of char_array..."<<endl<< "Size: "<<char_array.size()<<endl<<"Array: ";
    for (auto c : char_array) cout<<c<<" ";
    cout<<endl<<"Is empty?: "<<boolalpha<<char_array.empty()<<endl<<endl;
    
    cout << "Find '7'in int_array." << endl;
    auto itf = find(int_array.begin(), int_array.end(), 7);
    if (itf == int_array.end()) {
        cout << "Element not found." << endl;
    } else {
        cout << "Element found in the " << distance(int_array.begin(), itf)<<". index." <<endl;
    }

    cout << "Find '11'in int_array." << endl;
    auto itf2 = find(int_array.begin(), int_array.end(), 11);
    if (itf2 == int_array.end()) {
        cout << "Element not found." << endl;
    } else {
        cout << "Element found in the " << distance(int_array.begin(), itf2)<<". index." <<endl;
    }
    
    PFArray<int> int_array2;
    int_array2.push(1);
    int_array2.push(8);
    int_array2.push(12);
    int_array2.push(1);
    int_array2.push(5);
    int_array2.push(6);
    cout<<endl<<"A new int_array2 has been created and has been assigned the values (this part is printed by using for_each): ";
    for_each(int_array2.begin(), int_array2.end(), [](int x) {cout<<x<<" ";});


    cout<<endl<<endl<<"First index of int_array2 (use * operator overloading): "<< *int_array2.begin()<<endl<<endl;
    
    bool is_equal=(int_array.begin()==int_array2.begin());
    cout<<"Is 1st element of int_array equal to 1st element of int_array2?: "<<boolalpha<<is_equal<<endl;

    int_array=int_array2;
    cout<<"int_array after 'int_array = int_array2'  operation: ";
    for (auto i : int_array) cout<<i<<" ";

    is_equal=(int_array.begin()==int_array2.begin());
    cout<<endl<<"Is 1st element of int_array equal to 1st element of int_array2?: "<<boolalpha<<is_equal<<endl<<endl;

    PFArray<double> double_array;
    cout<<"Empty double array has been created!"<<endl;
    double_array.push(1.8);
    double_array.push(7.7);
    double_array.push(9.1);
    double_array.push(5.3);
    double_array.push(6.12);

    cout<<"The double array is: ";
    SPC::PFArray<double>::const_iterator itr =double_array.cbegin();
    for (;itr!=double_array.cend();itr++) cout<<*itr<<" ";
    //*itr=15.8; //this line is to show that const_iterator works, *itr can not be changed.
    cout<<endl<<"The array is set and the values can not be changed as it should be.";

    cout<<endl<<endl<<"Now the program will try to erase an element in an invalid index, program will throw std::out_of_range to handle this error...(Will print 'TEST FAILED' if program fails.)"<<endl<<endl<<endl;
    auto q = char_array.begin();
    q++;
    q++;
    --q;//just to show that -- operator overload works too..
    char_array.erase(q);
    cout<<"TEST FAILED.";
    return 0;
}
