//
// Created by NIRUJA on 7/26/2023.
//



#include "stdio.h"
#include <windows.h>
#include <math.h>
#include <time.h>

#define N 1000

float k = 0.01f;
float w = 1, b=2;


static void copyToClipboard(const char* output){
//    const char* output = "Test\0abc";
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

float forward(float x){
    return w*x+b;
}

float train(float x[],float y_ref[],int size){
    float err = 0;
    for (int n = 0; n < size; ++n) {
        float y = forward(x[n]);
        float dy = y-y_ref[n];
        float dw = x[n]*dy;
        float db = dy;
        w=w-k*dw;
        b=b-k*db;
        err+=0.5f*(y_ref[n]-y)*(y_ref[n]-y);
    }
    return err/(float )size;
}


int main(){
    srand(time(0));
    // Data generation
    float x[N];
    float y[N];

    for (int i = 0; i < N; ++i) {
        x[i]=(float)(rand()%100)/100.0f;
        y[i]= expf(x[i])+ sinf(2*x[i])* expf(cosf(2*x[i]))+(rand()%100)/10000.0f;
    }

    //Training
    for (int i = 0; i < 10; ++i) {
        float err = train(x,y,N);
        printf("Epoch : %d ==> w = %f, b = %f, Err = %f\n",i,w,b,err);
//        if(err<1e-8)
//            break;
    }

    printf("y=%f", forward(10.0f));

    char str[20240];
    int ptr = 0;
    for (int i = 0; i < sizeof(x)/4; ++i)
        ptr+=sprintf(str+ptr, "%f \n",y[i]);
    copyToClipboard(str);
    return 0;
}