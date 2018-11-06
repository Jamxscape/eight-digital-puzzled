//
//  main.cpp
//  bashuma
//
//  Created by 马元 on BE 2561/10/10.
//  Copyright © 2561 MaYuan. All rights reserved.
//
//广度优先 队列
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define N 9
int sou[3][3];//源期盼的二维数组
int dir[3][3];//目标棋盘的二维数组
int tempt[3][3];//上移的缓存
int tempb[3][3];//下移的缓存
int templ[3][3];//左移的缓存
int tempr[3][3];//右移的缓存
int value[349524];//移动后的缓存数据
string all[349524];//记录所有棋盘
int z1,z2;//记录空格的位置，z1 为x坐标，z2为y坐标
void swap(int *temp1,int *temp2){
    int t;
    t=*temp1;
    *temp1=*temp2;
    *temp2=t;
}//交换棋盘的位置
void printmap(int a[3][3]){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            cout<<a[i][j]<<' ';
            if(j==2)cout<<endl;
        }
}
void searchspace(int a[3][3]){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(a[i][j] == 0)
            {
                z1=i;z2=j;
                break;
            }
        }
}//搜索空格的位置
void str2array(string str){
    int re=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            sou[i][j]=str[re]-'0';
            re++;
        }
}//源棋盘的字符串转换成二维数组
void str2array2(string str){
    int re=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            dir[i][j]=str[re]-'0';
            re++;
        }
}//目标棋盘的字符串转换成二维数组
bool judgecache(int value1,int value){
    if(value == value1)
        return 0;// 如果相等，就不要搜索这个了呢，亲
    else
        return 1;//不相等时，返回1，已达到搜索的目的
}//记录前一步数组的值，以用来判断是否出现重复
bool judgedir(int a[3][3]){
    int c=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
             if(a[i][j]==dir[i][j])
                 c++;
             else {c=0;break;}
        }
    if(c==9)return true;//相等的时候 返回正确
    else return false;//否则false
}//判断与目标棋盘是否相等
void findtop(int value1,int *temp1,int *temp2,int value2,int sum){//value1 前一步缓存的数据，即为移动后的那个数据，对于前一个数组 ,value2 当亲的地址的数值呢, temp1 temp2 要交换的棋盘上两个棋子的数值 sum为当前总数组的下坐标，就是那个辣么的数组啦，30多万辣个，attention！只存那一个值亲
    // 找到最上面的值
    if(z1-1>=0){//当 ……  当什么来着，就是一定在墙内，不要翻墙
        if(judgecache(value1,value2))
        {
            swap(temp1,temp2);///交换当前数字，即移动棋子
            value[sum]=tempt[z1][z2];//缓存这个状态的数组，important！！！！！
        }
    } //否则不再交换
}//上移的函数
//下面的都是儿子函数，注释看top函数
void findbottom(int value1,int *temp1,int *temp2,int value2,int sum){//value1 is forward cache value ,x is current num locate, temp1 temp2 is value
    // find bottom value
    if(z1+1<3){
        if(judgecache(value1,value2))
        {
            swap(temp1,temp2);
            value[sum]=tempb[z1][z2];
        }
    }
    //else dont swipe it
}
void findleft(int value1,int *temp1,int *temp2,int value2,int sum){//value1 is forward cache value ,x is current num locate, temp1 temp2 is value
    // find left value
    if(z2-1>=0){
        if(judgecache(value1,value2))
        {
            swap(temp1,temp2);
            value[sum]=templ[z1][z2];
        }
    }
    //else dont swipe it
}
void findright(int value1,int *temp1,int *temp2,int value2,int sum){//value1 is forward cache value ,x is current num locate, temp1 temp2 is value
    // find right value
    if(z2+1<3){
        if(judgecache(value1,value2))
        {
            swap(temp1,temp2);
            value[sum]=tempr[z1][z2];
        }
    }
    //其他情况不交换数值
}

void savearray(int a[3][3],int count){
    string str="000000000";
    int n=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            str[n]=a[i][j]+'0';
            n++;
    }
    all[count]=str;
}//存成一维字符数组，然后再转换
int temperary[3][3];//移动过程中，最最最重要的缓存数组，所有的实现都靠他~~~~~
void apartarray(int count){
    string str;
    str=all[count];
    int n=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            temperary[i][j]=str[n]-'0';
            n++;
        }
}//分离一维的整型数组到二维数组
bool is_equal(){
    return 0;
}
void swipemap(){//棋盘之间
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            tempt[i][j]=sou[i][j];
            tempb[i][j]=sou[i][j];
            templ[i][j]=sou[i][j];
            tempr[i][j]=sou[i][j];
       }
    int inter=0;//记录一共走了多少步数
    int sum=0;//替代j的值，为了好看好看好看好看，易懂，没什么其他用处
        for(int j=0;j<349524;j++){
            sum = j;
            if(j>=0&&j<4)
            inter = 1;//wrong
            else if(j>=pow(4,inter)&&j<pow(4,inter+1))
            inter++;
                searchspace(sou);
            // j=0 1 2 3是第一步执行的时候 需要初始化的缓存值，以后就不需要再缓存了
                if(j==0)
                {//只讲一个，下面的自己想，最讨厌的就是cunt写注释了
                    value[j] = 0;//上一个移动的数值的缓存数据 由于上一个没有，所以赋值为00000，亲
                    cout<<"正在执行上移，棋盘为："<<endl;//zhegewobujieshi,woyebuxiangxinnihuikanwan,zhemewuliao,woco
                    findtop(1, &tempt[z1][z2], &tempt[z1-1][z2],value[j],sum);//移动棋子
                    savearray(tempt,sum);///移动完了，当然要保存了
                    printmap(tempt);//打印这个状态的temperary
                    if(judgedir(tempt))//与目标作对比
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                }
                else if(j==1)
                {
                    value[j] = 0;
                    cout<<"正在执行下移，棋盘为："<<endl;
                    findbottom(1, &tempb[z1][z2], &tempb[z1+1][z2],value[j],sum);
                    savearray(tempb,sum);
                    printmap(tempb);
                    if(judgedir(tempb))//equal movenumber and dir
                   {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                }
                else if(j==2)
                {
                    value[j] = 0;
                    cout<<"正在执行左移，棋盘为："<<endl;
                    findleft(1, &templ[z1][z2], &templ[z1][z2-1],value[j],sum);
                    savearray(templ, sum);
                    printmap(templ);
                    if(judgedir(templ))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                }
                else if(j==3)
                {
                    value[j] = 0;
                    cout<<"正在执行右移，棋盘为："<<endl;
                    findright(1, &tempr[z1][z2], &tempr[z1][z2+1],value[j],sum);
                    savearray(tempr, sum);
                    printmap(tempr);
                    if(judgedir(tempr))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                }
                else if(j%4==0){
                    apartarray(sum/4-1);
                    cout<<"正在执行上移，棋盘为："<<endl;
                    searchspace(temperary);
                    findtop(value[(j/4)-1], &temperary[z1][z2], &temperary[z1-1][z2],temperary[z1-1][z2],sum);
                    savearray(temperary, sum);
                    printmap(temperary);
                    if(judgedir(temperary))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                    //top
                }
                else if(j%4==1){
                    apartarray(sum/4-1);
                    cout<<"正在执行下移，棋盘为："<<endl;
                    searchspace(temperary);
                    findbottom(value[j/4-1], &temperary[z1][z2], &temperary[z1+1][z2],temperary[z1+1][z2],sum);
                    savearray(temperary, sum);
                    printmap(temperary);
                    if(judgedir(temperary))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                    //bottom
                }
                else if(j%4==2){
                    apartarray(sum/4-1);
                    cout<<"正在执行左移，棋盘为："<<endl;
                    searchspace(temperary);
                    findleft(value[j/4-1], &temperary[z1][z2], &temperary[z1][z2-1],temperary[z1][z2-1],sum);
                    savearray(temperary, sum);
                    printmap(temperary);
                    if(judgedir(temperary))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                    //left
                }
                else if(j%4==3){
                    apartarray(sum/4-1);
                    cout<<"正在执行右移，棋盘为："<<endl;
                    searchspace(temperary);
                    findright(value[j/4-1], &temperary[z1][z2], &temperary[z1][z2+1],temperary[z1][z2+1],sum);
                    savearray(temperary, sum);
                    printmap(temperary);
                    if(judgedir(temperary))//equal movenumber and dir
                    {cout<<"共需要走 "<<inter<<" 步."<<"获得成功!"<<endl;break;}
                    //right
                }
        }
    cout<<"运算结束，输出最简步骤:"<<endl;
    string whatyouneed;//打印要输出的结果
    printmap(dir);
    int cat=int(sum/4-1);
    cout<<"cat="<<cat<<endl;
    while(cat>0){
        apartarray(cat);
        cout<<"↑"<<endl;
        printmap(temperary);
        cat=int(cat/4-1);
        cout<<"cat="<<cat<<endl;
    }
    printmap(sou);
    cout<<"向上看是移动步骤"<<endl;
}
int main()
{
   
   string sour="203184765";
    string dire="123804765";
    /*
    string sour="123456780";
    string dire="123450786";
    */
    /*
     
    string sour="203184765";
    string dire="283014765";*/
    
    str2array(sour);
    str2array2(dire);
    swipemap();
    return 0;
}
