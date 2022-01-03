/*
* SSTF-的運作如下，
 1. 在判斷哪一個request為下一個request時，從queue中最前面3個request中，去找距離最近的request，然後依序完成。
 2. 如果有兩個request距離一樣遠，則按照磁頭移動方向來決定。
 3. 如果無法 決定磁頭移動方向，則選擇cylinder比較小的request。
程式需要輸出(1) 磁頭從目前位置開始，每次移動停留的位置，(2) 總共移動的距離。
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
int sstfAlgo(int , int , vector<int>& );
bool findFirstSlot(int&, vector<int>&, vector<int>&, vector<int>&);
int traceSlot(int&, vector<int>&, vector<int>&);
string fatchFile();
void stringEarse(int, vector<string>& );
int trace(int&, vector<int>& , vector<int>& );


int sstfAlgo(int bound, int head, vector<int>& slot){
    int total = 0;
    vector<int> aws;
    vector<int> firstRequest;
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

bool findFirstSlot(int& head, vector<int>& firstRequest, vector<int>& slot, vector<int>& aws){
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

int traceSlot(int& head, vector<int>& slot, vector<int>& aws){
    int total = abs(head - slot[0]);
    head = slot[0];
    slot.erase(slot.begin());
    aws.push_back(head);
    sort(slot.begin(),slot.end());
    size_t size = slot.size();
    for(auto i=0;i<size;i++){
        total += trace(head, slot, aws);
    }
    return total;
}

int trace(int& head,vector<int>& slot, vector<int>& aws){
    int value=300;
    int tempHead = 0;
    int postion = 0;
    for (auto i = 0; i < slot.size(); ++i) {
        if(value> abs(head - slot[i])){
            value = abs(head - slot[i]);
            postion=i;
            tempHead=slot[i];
        } else
            break;
    }
    head=tempHead;
    aws.push_back(head);
    slot.erase(slot.begin()+postion);
    return value;
}


string fatchFile(){
    string configfile = "./test.txt";
    return configfile;
}

void stringEarse(int count, vector<string>& str){
    for(int i=0;i<count;i++){
        str.pop_back();
    }
}

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
                    stringEarse(count, array);
                    break;
                case 2:
                    head = stoi(array[0]);
                    stringEarse(count, array);
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


int main() {
    vector<int> slot;
    int bound=0;
    int head = 0;
    int total = 0;
    getData(bound, head, slot);
    total = sstfAlgo(bound, head, slot);
    cout<<endl;
    for(auto value:slot){
        cout<<value<<" ";
    }
    cout<<endl<<"total: "<<total;

    return 0;
}
