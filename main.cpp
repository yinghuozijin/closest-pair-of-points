#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>

using namespace std;
static int resultpoints[2];

struct point{
    double x,y;
};

double dis(struct point a,struct point b);
double closest_points(struct point point[],int n,int start);

int main(){
    int num;
    cout<<"请输入要产生的坐标点的数目：";
    cin>>num;
    struct point point[num];
    srand((unsigned)time(NULL));
    for(int i=0;i<num;i++){
        point[i].x=rand()/(double)(RAND_MAX/100);
        point[i].y=rand()/(double)(RAND_MAX/100);
    }

    struct point temp;
    for(int i=0;i<num-1;i++){
        for(int j=0;j<num-i-1;j++){
            if (point[j].x>point[j+1].x){
                temp=point[j];
                point[j]=point[j+1];
                point[j+1]=temp;
            }
        }
    }

    double result=closest_points(point,num,0);
    cout<<"最小距离为："<<result<<endl;
    ofstream op("E:\\DAA\\test3.txt");
    for(int i=0;i<num;i++){
        op<<"（"<<point[i].x<<"，"<<point[i].y<<"）";
        op<<"\n";
    }
    op.close();
    cout<<"("<<resultpoints[0]+1<<","<<resultpoints[1]+1<<")";
}

double dis(struct point a,struct point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double closest_points(struct point point[],int n,int start){
    double result;
    int points[6];
    if(n==0||n==1){
        points[0]=points[1]=start;
        return 0;
    }
    if(n==2){
        resultpoints[0]=start;
        resultpoints[1]=start+1;
        return dis(point[0],point[1]);
    }
    if(n==3){
        double distance[3];
        distance[0]=dis(point[0],point[1]);
        distance[1]=dis(point[0],point[2]);
        distance[2]=dis(point[1],point[2]);
        result=distance[0];
        resultpoints[0]=start;
        resultpoints[1]=start+1;
        if(result>distance[1]){
            result=distance[1];
            resultpoints[0]=start;
            resultpoints[1]=start+2;
        }
        if(result>distance[2]){
            result=distance[2];
            resultpoints[0]=start+1;
            resultpoints[1]=start+2;
        }
        return result;
    }
    int mean=n/2;
    struct point left[mean],right[n-mean];
    for(int i=0;i<mean;i++)
        left[i]=point[i];
    for(int i=0;i<n-mean;i++)
        right[i]=point[i+mean];
    double leftmindis=closest_points(left,mean,start);
    points[0]=resultpoints[0];
    points[1]=resultpoints[1];
    double rightmindis=closest_points(right,n-mean,start+mean);
    points[2]=resultpoints[0];
    points[3]=resultpoints[1];
    double mindis=leftmindis;
    resultpoints[0]=points[0];
    resultpoints[1]=points[1];
    if(mindis>rightmindis){
        resultpoints[0]=points[2];
        resultpoints[1]=points[3];
        mindis=rightmindis;}
    int leftnum=0,rightnum=0;
    double mean_line=(point[mean-1].x+point[mean].x)/2;
    for(int i=0;i<mean;i++){
        if((mean_line-point[i].x)<mindis)
            leftnum++;
    }
    for(int i=0;i<n-mean;i++){
        if((point[i+mean].x-mean_line)<mindis)
            rightnum++;
    }
    if(leftnum==0||rightnum==0){
        return mindis;
    }

    for(int i=1;i<=leftnum;i++){
        for(int j=0;j<rightnum;j++){
            if(dis(point[mean-i],point[mean+j])<mindis){
                mindis=dis(point[mean-i],point[mean+j]);
                resultpoints[0]=mean-i+start;
                resultpoints[1]=mean+j+start;
            }
        }
    }
    result=mindis;
    return result;
}
