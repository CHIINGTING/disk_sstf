#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
int sstfAlgo(int , int , vector<int>& );
int findFirstSlot(int&, vector<int>, vector<int>&, vector<int>&);
int traceSlot(int&, vector<int>&, vector<int>&);

/* algo a-sstf */
int sstfAlgo(int bound, int head, vector<int>& slot){
    int total = 0;
    vector<int> aws; //the head trace postion
    vector<int> firstRequest; // top 3 data
    for(int i=0;i<3;i++){
        firstRequest.push_back(slot[i]);
    }

    sort(firstRequest.begin(),firstRequest.end());
    total += findFirstSlot(head, firstRequest, slot, aws);
    total += traceSlot(head, slot,aws);

    for(auto value: aws){
        slot.push_back(value);
    }
    return total;
}

// first trace for sstf
int findFirstSlot(int& head, vector<int> firstRequest, vector<int>& slot, vector<int>& aws){
    aws.push_back(head);
    int value = 300;
    int tempHead = 0;
    for(auto i=0;i<firstRequest.size();i++){
        if(value > abs(head-firstRequest[i])){
            value = abs(head-firstRequest[i]);
            tempHead = firstRequest[i];
        }
        else {
            break;
        }
    }
    head = tempHead;
    aws.push_back(head);

    for(auto i=0;i<slot.size();i++){
        if(head == slot[i]){
            slot.erase(slot.begin()+i);
        }
    }
    return value;
}

// last trace for c-scan
int traceSlot(int& head, vector<int>& slot, vector<int>& aws){
    int total = abs(head - slot[0]);
    bool check = head<slot[0];
    vector<int> left;
    vector<int> right;
    head = slot[0];
    slot.erase(slot.begin());
    aws.push_back(head);

    for(auto s:slot){
        if(s<head){
            left.push_back(s);
        } else
            right.push_back(s);
    }
    size_t size = slot.size();
    for(auto i=0;i<size;i++){
        slot.pop_back();
    }

    sort(left.begin(),left.end(),[=](auto a,auto b){
        return a>b;
    });
    sort(right.begin(),right.end(),[=](auto a,auto b){
        return a<b;
    });

    if(check){
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            aws.push_back(head);
        }

        for(int i=0;i<left.size();i++){
            total += abs(head-left[i]);
            head = left[i];
            aws.push_back(head);
        }
    } else{
        for(int i=0;i<left.size();i++) {
            total += abs(head - left[i]);
            head = left[i];
            aws.push_back(head);
        }
        for(int i=0;i<right.size();i++){
            total += abs(head-right[i]);
            head = right[i];
            aws.push_back(head);
        }
    }
    return total;
}

/* get test value */
//get location
string fatchFile(){
    string configfile = "yout test file name"; // /filelocation/filename
    return configfile;
}
//get the test data
void getData(int& bound, int& head, vector<int>& slot){
    vector<string> array;
    string space_delimter=" ";
    string str;
    size_t postion;
    string configfile = fatchFile();
    try {
        int data=0;
        ifstream fin(configfile);
        while (getline(fin, str)){
            int count = 0;
            data++;
            while((postion = str.find(space_delimter))!= string::npos){
                array.push_back(str.substr(0,postion));
                str.erase(0, postion+space_delimter.length());
                count++;
            }
            array.push_back(str.substr(0,postion));
            count++;
            for(string s:array){
            }
            switch (data) {
                case 1:
                    bound = stoi(array[0]);
                    array.pop_back();
                    break;
                case 2:
                    head = stoi(array[0]);
                    array.pop_back();
                    break;
                case 3:
                    for(string s:array){
                        slot.push_back(stoi(s));
                    }
                default:
                    break;
            }
        }
    }catch (std::exception &e) {
        cout<<"exception: " << e.what()<<endl;
    }
}

/* main code */
int main() {
    vector<int> slot;
    int bound=0;
    int head = 0;
    int total = 0;
    getData(bound, head, slot);

    total = sstfAlgo(bound, head, slot);
    cout<<"Positions: ";
    for(auto value:slot){
        cout<<value<<" ";
    }
    cout<<endl<<"total: "<<total;

    return 0;
}
