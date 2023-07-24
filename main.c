#include <stdio.h>
#include <windows.h>
#include <math.h>


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

float f(float x){
//    return powf(x,2)-4*x+3;
    return powf(x,2)+ sinf(10*x)-5;
}


float gradF(float x){
//    return 2*x-4;
    return 2*x+10* cosf(10*x);
}

int main() {
//    float x[10];
//    float y[10];
//    for (int i = 0; i < sizeof(x)/4; ++i) {
//        x[i]=(float)i;
//        y[i] = f(x[i]);
//    }

    float c = 0.01f;
    float m = 2.0f;
    float p = 0;
    float x1[100];
    float z1=2.169;
    for (int i = 0; i < sizeof(x1)/4; ++i) {
        x1[i]=z1;
        float p_new = max(m*exp(-i*0.15),0.9)*p+ gradF(z1);
        float z1_new = z1-c* p_new;
        p = p_new;
        z1 = z1_new;
    }
    printf("Minima : f(%f) = %f\n",z1, f(z1));


//    float x[5];
//    float z = 0.46f;
//    float k = 1.2f;
//    for (int i = 0; i < sizeof(x)/4; ++i) {
//        x[i]=z;
//        float z_new = z - k* gradF(z);
//        z = z_new;
//    }
//    printf("Minima : f(%f)=%f\n",z,f(z));


    char str[1024];
    int ptr = 0;
    for (int i = 0; i < sizeof(x1)/4; ++i)
        ptr+=sprintf(str+ptr, "%f \n",x1[i]);
//    printf("%s",str);
    copyToClipboard(str);



    return 0;
}
