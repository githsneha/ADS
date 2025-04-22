#include <iostream>
using namespace std;
// #define max 1000 

int n=0;
int arr[100];


void heapifymax(int arr[], int n, int i)
{
    int p = (i - 1) / 2;
    if (i > 0) {
        if (arr[i] > arr[p]) {
            swap(arr[i], arr[p]);
            heapifymax(arr, n, p);
        }
   }
}

void insert(int arr[], int& n, int Key)
{
    n = n + 1;
    arr[n-1] = Key;
    heapifymax(arr, n, n - 1);
    // n=n+1;
}

void heapifymin(int arr[], int n, int i)
{
    int p = (i - 1) / 2;
    if (i> 0) {
        if (arr[i] < arr[p]) {
            swap(arr[p], arr[i]);
            heapifymin(arr, n, p);
        }
    }
}

void add(int arr1[], int& n, int Key)
{
    n = n + 1;
    arr1[n-1] = Key;
    heapifymin(arr1, n, n - 1);
    // n = n + 1;
}

void print(int arr1[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr1[i] << " ";

    cout << "\n";
}

void del_end() {
    if (n == 0) return;
    n--; 
}

void del_bet(int key){
    int pos= 0;
    for(int i=0;i<n;i++){
        if(arr[i]== key){
            pos=i;
            break;
        }
    }
    int temp=arr[pos];
        arr[pos]= arr[n-1];
        n=n-1;
        heapifymax(arr, n, n - 1);
}


int main()
{
   int c,key;
//    int arr[max] = { 90, 85, 73, 62, 14 };
//    int arr1[max] = { 14,62,73,85,90 };
   int min= 5;
   int m=5;
   do
   {
    
    cout<<"1.Max heap"<<endl;
    cout<<"2.Min heap"<<endl;
    cout<<"3.Delete Node at End"<<endl;
    cout<<"4.Delete Node in Between"<<endl;
    cout<<"5.Delete Root Node"<<endl;
    cout<<"6.Exit"<<endl;
    cout<<"Enter choice: "<<endl;
    cin>>c;
      switch (c)
      {
      case 1:
      cout<<"Enter key to be inserted: ";
      cin>>key;
      insert(arr, n, key);
      print(arr, n);
      break;

      case 2:
      cout<<"Enter key to be inserted: ";
      cin>>key;
      add(arr, n, key);
      print(arr, n);
      break;

     case 3:
     del_end();
     print(arr, n);
     break;


     case 4:
     cout<<"Enter node to delete"<<endl;
     cin>>key;
     del_bet(key);
     print(arr, n);
     break;

     case 5:
     cout<<"Yet to be done"<<endl;
     break;


     case 6:
     cout<<"YExiting..."<<endl;
     break;


      default:
        break;
      }
   } while (c!=6);

   return 0;
}
