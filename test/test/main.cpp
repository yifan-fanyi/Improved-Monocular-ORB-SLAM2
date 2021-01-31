//
//  main.cpp
//  test
//
//  Created by Alex on 08/03/2018.
//  Copyright © 2018 Alex. All rights reserved.
//


///////////////////////////////////////////////////
//LK optical flow
#include<opencv2/opencv.hpp>
#define ClocksPerSec 1000000;

const int MAX_CORNERS = 1000;
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "KMeans.h"
using namespace std;

int main()
{
    
    
    IplImage *imgA = cvLoadImage("1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    IplImage *imgB = cvLoadImage("2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if(!imgA){
        cout << "could not open photo" << endl;
        return 0;
    }
    if(!imgB){
        cout << "could not open photo" << endl;
        return 0;
    }
   
    
    CvSize img_sz = cvGetSize(imgA);
    int win_size = 10;
    IplImage *imgC = cvLoadImage("1.png", CV_LOAD_IMAGE_UNCHANGED);
    
    IplImage *eig_image = cvCreateImage(img_sz, IPL_DEPTH_32F,1);
    IplImage *tmp_image = cvCreateImage(img_sz, IPL_DEPTH_32F, 1);
    
    int corner_count = MAX_CORNERS;
    CvPoint2D32f *cornersA = new CvPoint2D32f[MAX_CORNERS];
    double StartTime,EndTime1,CostTime1,EndTime2,CostTime2;      //to calculate the runtime
    StartTime = clock();
    cvGoodFeaturesToTrack(
                          imgA,
                          eig_image,
                          tmp_image,
                          cornersA,
                          &corner_count,
                          0.01,
                          5.0,
                          0,
                          3,
                          0,
                          0.04
                          );

    cvFindCornerSubPix(
                       imgA,
                       cornersA,
                       corner_count,
                       cvSize(win_size, win_size),
                       cvSize(-1, -1),
                       cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03)
                       );
 
    EndTime2 = clock();
    CostTime2 = (EndTime2 - StartTime) / ClocksPerSec;
    
    //int corner_count = 500;
    //CvPoint2D32f *cornersA = new CvPoint2D32f[MAX_CORNERS];
    char features_found[MAX_CORNERS];
    float features_errors[MAX_CORNERS];
    CvSize pyr_sz = cvSize(imgA->width + 8, imgB->height / 3);
    IplImage *pyrA = cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    IplImage *pyrB = cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
    CvPoint2D32f *cornersB = new CvPoint2D32f[MAX_CORNERS];
    

    cvCalcOpticalFlowPyrLK(
                           imgA,
                           imgB,
                           pyrA,
                           pyrB,
                           cornersA,
                           cornersB,
                           corner_count,
                           cvSize(win_size, win_size),
                           5,
                           features_found,
                           features_errors,
                           cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3),
                           0
                           );
    double vecth[corner_count],veclen[corner_count];
    double driftx[corner_count], drifty[corner_count], drift[2*corner_count];
    int k=0;
    for (int i = 0; i < corner_count; ++i)
    {
    
        CvPoint p0 = cvPoint(cvRound(cornersA[i].x), cvRound(cornersA[i].y));
        CvPoint p1 = cvPoint(cvRound(cornersB[i].x), cvRound(cornersB[i].y));
        
        
        veclen[i]=((p0.x-p1.x)*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y));
       
        vecth[i]=((p0.y-p1.y)/(p0.x-p1.x+0.0001));
      //  cout<<vecth[i]<<"       "<<veclen[i]<<endl;
        driftx[i]=cornersA[i].x - cornersB[i].x;
        drift[k]=cornersA[i].x - cornersB[i].x;
        k++;
        drifty[i]=cornersA[i].y - cornersB[i].y;
        drift[k]=cornersA[i].y - cornersB[i].y;
        k++;
    }
    
    
    
    
    
    
    const int size = corner_count; //Number of samples
    const int dim = 2;   //Dimension of feature
    const int cluster_num = 5; //Cluster number
    KMeans* kmeans = new KMeans(dim,cluster_num);
    int* labels = new int[size];
    kmeans->SetInitMode(KMeans::InitUniform);
    
    kmeans->Cluster(drift,size,labels);
    
    int count[cluster_num]={0};
    for(int i=0;i<size;i++){
        count[labels[i]]++;
 //       cout<<labels[i]<<endl;
    }
    int max=count[0],temp=0;
    for(int i=1;i<cluster_num;i++){
        if(count[i]>max){
            max=count[i];
            temp=i;
        }
    }
   // cout<<max<<temp<<endl;
    
 //   for (int i = 0; i < corner_count; ++i)
 //   {
     //   CvPoint p0 = cvPoint(cvRound(cornersA[i].x), cvRound(cornersA[i].y));
       // CvPoint p1 = cvPoint(cvRound(cornersB[i].x), cvRound(cornersB[i].y));
        //cout<<labels[i]<<"      "<<vecth[i]<<"       "<<veclen[i]<<endl;
       // cout<<labels[i]<<"      "<<cornersA[i].x<<"      "<<cornersA[i].y<<"        "<<cornersB[i].x<<"      "<<cornersB[i].y<<endl;
   //     if(labels[i]==temp){
     //       cvLine(imgC, p0, p1, CV_RGB(0, 0, 255),2);
            // cout<<vecth[i]<<"       "<<veclen[i]<<endl;

       //     cout<<driftx[i]<<"       "<<drifty[i]<<endl;
            
   //     }
     //   else{
      //      cvLine(imgC, p0, p1, CV_RGB(250, 128, 0),2);
            
       // }
  //  }
 //   cout<<"/////////////////////////////"<<endl;

    for (int i = 0; i < corner_count; ++i)
    {
        CvPoint p0 = cvPoint(cvRound(cornersA[i].x), cvRound(cornersA[i].y));
        CvPoint p1 = cvPoint(cvRound(cornersB[i].x), cvRound(cornersB[i].y));
        //cout<<labels[i]<<"      "<<vecth[i]<<"       "<<veclen[i]<<endl;
        // cout<<labels[i]<<"      "<<cornersA[i].x<<"      "<<cornersA[i].y<<"        "<<cornersB[i].x<<"      "<<cornersB[i].y<<endl;
        if(labels[i]==temp){
            cvLine(imgC, p0, p1, CV_RGB(255, 0, 0),2);
        //    cout<<labels[i]<<"      "<<vecth[i]<<"       "<<veclen[i]<<endl;
            
        }
        else{
            cvLine(imgC, p0, p1, CV_RGB(0, 0, 255),2);
           // cout<<vecth[i]<<"       "<<veclen[i]<<endl;
      //      cout<<driftx[i]<<"       "<<drifty[i]<<endl;

        }
    }
    
    
    
    
    
    
    EndTime1 = clock();
    CostTime1 = (EndTime1 - StartTime) / ClocksPerSec;
    
    //run time
    //CLOCKS_PER_SEC is 1000 000 while using Xcode
    cout<<"The during time is: "<< CostTime1 <<" seconds\n"<<endl;
     cout<<"The during time is: "<< CostTime2 <<" seconds\n"<<endl;
    cvNamedWindow("ImageA", 0);
    cvNamedWindow("ImageB", 0);
    cvNamedWindow("LKpyr_OpticalFlow", 0);
    cvShowImage("ImageA", imgA);
    cvShowImage("ImageB", imgB);
    cvShowImage("LKpyr_OpticalFlow", imgC);
    cvWaitKey(0);
    
    return 0;
}

