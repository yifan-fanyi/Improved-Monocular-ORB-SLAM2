//
//  main.cpp
//  generate_rgb
//
//  Created by Alex on 2018/4/23.
//  Copyright © 2018 Alex. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <time.h>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
     ofstream file("rgb.txt");
    for(int i = 0; i < 4541; i++)
    {
        if(i <10)
            file<<"00000"<<i<<"  rgb/00000"<<i<<".png"<<endl;
        else{
            if(i <100)
                file<<"0000"<<i<<"  rgb/0000"<<i<<".png"<<endl;
            else{
                if(i<1000)
                    file<<"000"<<i<<"  rgb/000"<<i<<".png"<<endl;
                else{
                    file<<"00"<<i<<"  rgb/00"<<i<<".png"<<endl;
                }
            }}
    }
    
    
    return 0;
}
