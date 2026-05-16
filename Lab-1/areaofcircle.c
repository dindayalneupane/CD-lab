// Write a program to calculate area of circle by defining 
//PI as macro constant.
#include<stdio.h>
#define PI 3.1415
int main(){
    float radius = 5;
    float area = PI*radius*radius;
    printf("The area of circle is %f", area);
}