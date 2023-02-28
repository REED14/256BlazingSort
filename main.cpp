//This algorithm is similar to the Radix sort
//But might be far more efficient
//It's space complexity is approximately O(4*n)
//It's time complexity is O(10*n)
//(10 in the case of numbers larger than unsigned long long)
//(You can verify time complexity in the number of steps)
#include <bits/stdc++.h>

std::ifstream fin("numbers.txt");
using namespace std;

///Variables thing
uint64_t temp; // here is the value read from the file

long long steps = 0; //the number of steps

unsigned int result[100], x;
//result[] is the array with the indexes of the sorted numbers
//x is the size of the array

uint8_t nums[100][12], sizenum[100], maxnum;
//nums[][] is the matrix with the numbers read in 256 base format
//sizenum[] the array which contains the number of "digits" of
//every number in base 256

///Functions thing

//transform numbers and put them into 256 form matrix
uint8_t get_into_256(uint8_t *num, uint64_t xl){
    uint8_t s=0;
    while(xl){
        num[s]=xl%256;
        xl/=256; s++;
    }
    return s;
}

//transform 256 base number from matrix into base 10 number
uint64_t get_256_to_10(uint8_t *num, uint8_t sn){
    uint8_t i=0;
    uint64_t n = 0;
    for(int i=sn-1; i>=0; i--)
        {n*=256; n+=num[i];}
    return n;
}

//sort base 256 number to the n "digit"
//(this is the complicated part)
bool sorting_on_n(int n){
    //this queue will store a dynamic list
    //of numbers which have the same 256 form digit
    //(I am using a queue to utilise the space efficiently)
    queue<int> added[256];

    //this is what the function will return
    //if elements will be added to queue added
    //on a position that is not 0
    bool has_more_zero = 0;

    //in this stage we will add numbers to the 'added' queue
    //at the queue array index equal to the digit
    /*

    For exemple:
    if our number is:      711414126
    it's 265 form will be: 110 81 103 42 0 0 0 0
    and in the file is the second (index = 2)
    and we sort by the first digit

    Then:

    added[110] <- 2

    */

    //if we sort the numbers by their firs 256 digit
    //the result array will be empty so we can't use it
    if(n==0)
        for(int i=0; i<x; i++){
            added[nums[i][n]].push(i);
            if(nums[i][n]) has_more_zero=1;
            steps++;
        }
    //otherwise we will sort the numbers by their order
    //in the result[] array so that we will take into
    //account the sorting of their previous digits
    else
        for(int i=0; i<x; i++){
            int pusher = result[i];
            added[nums[pusher][n]].push(pusher);
            if(nums[pusher][n]) has_more_zero=1;
            steps++;
        }

    //in the end we will iterate the queue array
    //from 0 to 255 and we will replace the numbers
    //in result array with the indexes from the queues
    int idx = 0;
    for(int i=0; i<=255; i++)
        while(added[i].size()){
            result[idx] = added[i].front();

            //this is for debugging
            cout<<(int)nums[result[idx]][n]<<" ";

            added[i].pop(); idx++;
            steps++;
        }

    //this is for debugging
    cout<<'\n';

    return has_more_zero;
}

int main()
{
    //reading the numbers from the file
    while(fin>>temp){
        //we will calculate the number of digits that they have
        //in 256 base and we will transform them into 256 form
        sizenum[x] = get_into_256(nums[x], temp);

        //we will calculate the maximum number of digits
        if(sizenum[x]>maxnum) maxnum = sizenum[x];
        //x is the number of numbers that we read
        x++;
    }

    cout<<"**********************************\n";
    cout<<"*                                *\n";
    cout<<"*      Just for debugging        *\n";
    cout<<"*                                *\n";
    cout<<"**********************************\n";

    //here we just display the numbers in their 256 form
    //and their base 10 form
    for(int i=0; i<x; i++){
        int j = 0;
        cout<<i<<": ";
        while(nums[i][j]>0){
            cout<<(int)nums[i][j]<<"\t";
            j++;
        }
        for(int k=j; k<maxnum; k++)
            cout<<0<<'\t';
        cout<<"realnum: "<<get_256_to_10(nums[i], sizenum[i])<<'\n';
    }

    cout<<"\n\n";
    cout<<"**********************************\n";
    cout<<"*                                *\n";
    cout<<"*      Rearanging numbers        *\n";
    cout<<"*                                *\n";
    cout<<"**********************************\n";

    //here we sort the numbers by every 256 digit
    //so that, in the end, they will be completely
    //sorted and the result[] array will have the
    //indexes of the numbers sorted
    for(int i=0; i<=maxnum; i++)
        if(!sorting_on_n(i)) break;

    cout<<"\n\n";
    cout<<"**********************************\n";
    cout<<"*                                *\n";
    cout<<"*             Result             *\n";
    cout<<"*                                *\n";
    cout<<"**********************************\n";

    //here we output the numbers in base 10 located at the
    //indexes of result[i]
    cout<<'\n';
    for(int i=0; i<x; i++)
        cout<<get_256_to_10(nums[result[i]], sizenum[result[i]])<<" ";
    cout<<"\n\n"<<"Steps:"<<steps;
    return 0;
}
