//
//  main.cpp
//  CalculateError
//
//  Created by Alex on 28/03/2018.
//  Copyright © 2018 Alex. All rights reserved.
//
// ground truth trajectory file:
// 'rgbd_dataset_freiburg1_xyz.bag'
// timestamp tx ty tz qx qy qz qw

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <time.h>
#include <math.h>

using namespace std;
int main(){
int i;
ofstream file("rgb.txt");
for(i=0;i<4540;i++){
    if(i<10)
        file<<"00000"<<i<<" "<<"rgb/00000"<<i<<".png"<<endl;
    else{
        if(i<100){
            file<<"0000"<<i<<" "<<"rgb/0000"<<i<<".png"<<endl;
        }
        else{
            if(i<1000){
                file<<"000"<<i<<" "<<"rgb/000"<<i<<".png"<<endl;
            }
            else{
                file<<"00"<<i<<" "<<"rgb/00"<<i<<".png"<<endl;

            }
        }
    }
    }
    file.close();
    }
/*
int main(){
    double str;
    ifstream in("CameraTrajectory.txt");
    if (!in){
        cout<<"Can Not Read The CameraTrajectory Files, Please Check The Location!"<<endl;
        return 1;
    }
    vector<double> cj0;
    vector<double> cj1;
    vector<double> cj2;
    vector<double> cj3;
    vector<double> cj4;
    vector<double> cj5;
    vector<double> cj6;
    vector<double> cj7;
    int count = 0;
    while(in >> str){
        if(count % 8 == 0){
            cj0.push_back(str);
        }
        if(count % 8 == 1){
            cj1.push_back(str);
        }
        if(count % 8 == 2){
            cj2.push_back(str);
        }
        if(count % 8 == 3){
            cj3.push_back(str);
        }
        if(count % 8 == 4){
            cj4.push_back(str);
        }
        if(count % 8 == 5){
            cj5.push_back(str);
        }
        if(count % 8 == 6){
            cj6.push_back(str);
        }
        if(count % 8 == 7){
            cj7.push_back(str);
        }
        count++;
    }
    
    ifstream inT("groundtruth.txt");
    if (!inT){
        cout<<"Can Not Read The GroundTruth Files, Please Check The Location!"<<endl;
        return 1;
    }
    vector<double> gj0;
    vector<double> gj1;
    vector<double> gj2;
    vector<double> gj3;
    vector<double> gj4;
    vector<double> gj5;
    vector<double> gj6;
    vector<double> gj7;
    count = 0;
    while(inT >> str){
        if(count % 8 == 0){
            gj0.push_back(str);
        }
        if(count % 8 == 1){
            gj1.push_back(str);
        }
        if(count % 8 == 2){
            gj2.push_back(str);
        }
        if(count % 8 == 3){
            gj3.push_back(str);
        }
        if(count % 8 == 4){
            gj4.push_back(str);
        }
        if(count % 8 == 5){
            gj5.push_back(str);
        }
        if(count % 8 == 6){
            gj6.push_back(str);
        }
        if(count % 8 == 7){
            gj7.push_back(str);
        }
        count++;
    }
   // for (vector<double>::iterator it = gj0.begin(); it != gj0.end(); it++){
     //   *it=*it-*gj0.begin();
    //}
    for (int i = 1;i<gj1.size();i++){
        gj1[i]=gj1[i]-gj1[0];
        cout<<gj1[0]<<endl;
    }
    gj1[0]=0;
    for (int i = 1;i<gj2.size();i++){
        gj2[i]=gj2[i]-gj2[0];
    }
    gj2[0]=0;
    for (int i = 1;i<gj3.size();i++){
        gj3[i]=gj3[i]-gj3[0];
    }
    gj3[0]=0;
    for (int i = 1;i<gj3.size();i++){
        gj4[i]=gj4[i]-gj4[0];
    }
    gj4[0]=0;
    for (int i = 1;i<gj5.size();i++){
        gj5[i]=gj5[i]-gj5[0];
    }
    gj5[0]=0;
    for (int i = 1;i<gj6.size();i++){
        gj6[i]=gj6[i]-gj6[0];
    }
    gj6[0]=0;
    for (int i = 1;i<gj7.size();i++){
        gj7[i]=gj7[i]-gj7[0];
    }
    gj7[0]=0;
    vector<int> gjindex;
    double temp=*cj0.begin()-*gj0.begin();
    int temp1=0;
    for(int i=0;i<cj0.size();i++){
        for(int j=temp1;j<gj0.size();j++){
            ////////////////camera's time stamp > ground's time stamp
            if(cj0[i]-gj0[j]>0){
                
                temp=(double)abs(cj0[i]-gj0[j]);}
            else{
                if((double)abs(temp)<(cj0[i]-gj0[j])){
                    gjindex.push_back(j-1);
            //        cout<<j-1<<endl;
                    break;
                }
                else{
                    gjindex.push_back(j);
               //     cout<<j<<endl;
                    break;
                }
            }
        }
    }
    
    //cal RMSE
    double sum1=0;
    for(int i=0;i<cj0.size();i++){
        sum1+=(cj1[i]-gj1[gjindex[i]])*(cj1[i]-gj1[gjindex[i]])/cj0.size();
   //     cout<<gj1[gjindex[i]]<<"        "<<cj1[i]<<endl;
    }
    cout<<sum1;
    
    sum1=sqrt(sum1);
    cout<<sum1<<endl;
    
    
    
    
    
}
*/
