#include <iostream>
#include <algorithm> 
#include <string>
#include <map>
using namespace std;

struct Element {
    int serial;
    int value;
    Element(int s = 0, int v = 0) : serial(s), value(v) {}
};


bool compare(const Element& a, const Element& b) {
    return a.value < b.value;
}


int main(){
    int n,Sno;
    printf("Enter no of people: ");
    cin>>n;
    int spend[n],Actual_Exp[n];
    for(int i=0;i<n;i++){
        spend[i]=0;
        Actual_Exp[i]=0;
    }

    map<int, string> peopleNames; // Map to store people's names
    for (int i = 0; i < n; ++i) {
        string name;
        cout << "Enter name for person " << i+1 << ": ";
        cin >> name;
        peopleNames[i] = name;
    }

    //trip begins
    int over=0,amt,np;
    while(over!=1){
        printf("enter Sno of payer for current transaction(1,2..N): ");
        cin>>Sno;
        Sno--;
        printf("enter amount payed by payer: ");
        cin>>amt;
        spend[Sno]+=amt;
        printf("Enter the no people in which  bill is splitted: ");
        cin>>np;
        int arr[np];
        for(int k=0;k<np;k++){
            printf("ADD person no: ");
            cin>>arr[k];
            arr[k]=arr[k]-1;//stores index of person no details with whom bill is split,0indexing
        }
        int contro=amt/np;

        for(int k=0;k<np;k++){
            Actual_Exp[arr[k]]+=contro;
        }

        printf("Is trip over?? 1:yes 0:no ");
        cin>>over;
        if(over==1){
            break;
        }
    }

    int due[n];
    cout<<endl;

    for(int j=0;j<n;j++){
        due[j]=spend[j]-Actual_Exp[j];
    }

    int size;
    size=n;

    Element* array = new Element[size];

    for (int i = 0; i < size; ++i) {
        int serial, value;

        serial=i;
        value=due[i];
        array[i] = Element(serial, value);
    }

    sort(array, array + size, compare);

    int negc=0;
    for (int i = 0; i < size; i++){
        if(array[i].value<0){
            negc++;
        }
        else{
            break;
        }
    }

    int p,end;
    end=size-1;
    for(int j=0;j<negc;j++){

        if((-(array[j].value))>array[end].value){
            cout << "Person " << peopleNames[array[j].serial] << " should give " << (array[end].value) << " Rs to Person " << peopleNames[array[end].serial] << endl;
            array[j].value+=array[end].value;
            array[end].value=0;
            end--;
            j--;
        }
        else if(-(array[j].value)<array[end].value){
            cout << "Person " << peopleNames[array[j].serial] << " should give " << -(array[j].value) << " Rs to Person " << peopleNames[array[end].serial] << endl;
            array[end].value+= (array[j].value);
            array[j].value=0;

        }
        else if((-(array[j].value))==array[end].value){  // both equal
            cout << "Person " << peopleNames[array[j].serial] << " should give " << -(array[j].value) << " Rs to Person " << peopleNames[array[end].serial] << endl;
            array[j].value=0;
            array[end].value=0;

            end--;
        }
    }
}



