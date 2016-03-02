#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <queue>

using namespace cv;
using namespace std;

class point
{
public :int x,y;
};

int main(int argc, char **argv)
{

      Mat image;
      image = imread("/home/vivek/Downloads/ps1.png", CV_LOAD_IMAGE_COLOR);
          queue<point> q;
          int  i,j,flag=0,visit[image.rows][image.cols];point p,arr[image.rows][image.cols];
          for(i=0;i<image.rows;i++)
          {
          for(j=0;j<image.cols;j++)
          visit[i][j]=0;
          }
          p.x=27;
          p.y=31;
          visit[27][31]=1;
     namedWindow( "Display window", WINDOW_AUTOSIZE );
      imshow( "Display window", image );
          q.push(p);
          do{
          p=q.front();
          q.pop();
          for(i=(p.x)-1;i<=(p.x)+1 && flag!=1;i++)
          {
          if(i>=0 && i<image.cols)
          for(j=(p.y)-1;j<=(p.y)+1;j++)
          {
          if(j>=0 && j<image.rows)
         {
         if(visit[i][j]==1)continue;
          point a;
          a.x=i;
          a.y=j;
          arr[i][j]=p;
          if(image.at<Vec3b>(i,j)[0]==0 && image.at<Vec3b>(i,j)[1]==255)
         {p.x=i;p.y=j; flag=1;break;}
          if(image.at<Vec3b>(i,j)[0]!=255 && visit[i][j]==0)
          {q.push(a);
          visit[i][j]=1;}
          }
          }
          }
          }while(!q.empty() && flag!=1);

  ros::init(argc, argv, "Publisher");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("Path", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
do {
     i=p.x;j=p.y;
     p=arr[i][j];
    std_msgs::String msg;

    std::stringstream ss;
    ss << '(' << i << ',' << j << ')';
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }  while (i!=27 && j!=31);
  waitKey(0);
  return 0;
}
