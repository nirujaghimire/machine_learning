//
// Created by NIRUJA on 7/26/2023.
//



#include "stdio.h"
#include <windows.h>
#include <math.h>
#include <time.h>

#define N 1000

float k = 0.01f;
float m = 0.9f;
float w = 1, b=2;
float p_w = 0, p_b = 0;


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
    return w* expf(b*x);
}

float train(float x[],float y_ref[],int size,int mini_batch_size){
    float total_err = 0;
    for (int n = 0; n < size/mini_batch_size; ++n) {
        float dw = 0;
        float db = 0;
        float err = 0;
        for (int i = 0; i < mini_batch_size; ++i) {
            int index = i+mini_batch_size*n;
            float y = forward(x[index]);
            float dy = y-y_ref[index];
            dw += dy*y/w;
            db += dy*x[index]*y;
            err+=0.5f*(y_ref[index]-y)*(y_ref[index]-y);
        }
        p_w = m*p_w + dw/(float )mini_batch_size;
        w=w-k*p_w;

        p_b = m*p_b + db/(float )mini_batch_size;
        b=b-k*p_b;

        total_err+=err;
        err = err/(float )mini_batch_size;
        printf("Batch : %d ==> w = %f, b = %f, Err = %f\n",n,w,b,err);
    }

    return total_err/(float )size;
}


int main(){
    srand(time(0));
    // Data generation
    float x_train[N];
    float y_train[N];

    for (int i = 0; i < N; ++i) {
        x_train[i]=(float)(rand()%100)/100.0f;
//        y[i]= expf(x[i])+ sinf(2*x[i])* expf(cosf(2*x[i]))+(rand()%100)/10000.0f;
//        y[i]= 3*x[i]+5+(rand()%100)/10000.0f;
        y_train[i] = 2.4* expf(5.6*(rand()%100)/100.0f);
    }


    /********************MAIN******************/
    //Training
    for (int i = 0; i < 1000; ++i) {
        float err = train(x_train,y_train,N,N/10);
        printf("Epoch : %d ==> w = %f, b = %f, Err = %f\n",i,w,b,err);
//        if(err<1e-8)
//            break;
    }

    printf("y=%f", forward(10.0f));

    char str[20240];
    int ptr = 0;
    for (int i = 0; i < sizeof(x_train)/4; ++i)
        ptr+=sprintf(str+ptr, "%f \n",y_train[i]);
    copyToClipboard(str);
    return 0;
}