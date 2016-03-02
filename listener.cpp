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

class point{
public : int i,j;
};

queue<point> q;
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  point p;
 //std::stringstream ss;
  char * ss = new char [msg->data.length()+1];
  std::strcpy (ss, msg->data.c_str());
  sscanf(ss,"(%d,%d)",&p.i,&p.j);
 q.push(p);
 //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
 ros::init(argc, argv, "listener");
 ros::NodeHandle n;
 ros::Subscriber sub = n.subscribe("Path", 1000, chatterCallback);
 ros::spin();
Mat img = imread("/home/vivek/Downloads/ps1.png", CV_LOAD_IMAGE_COLOR);

do {
  point p=q.front();
  q.pop();
  img.at<Vec3b>(p.i,p.j)[0]=255;
  img.at<Vec3b>(p.i,p.j)[1]=0;
  img.at<Vec3b>(p.i,p.j)[2]=0;
} while(!q.empty());

namedWindow("Path", WINDOW_AUTOSIZE );
 imshow( "Path", img);

waitKey(0);
 return 0;
}
