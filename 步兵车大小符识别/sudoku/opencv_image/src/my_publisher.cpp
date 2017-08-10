#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer

using namespace cv;

int main(int argc, char** argv)
{
    // Check if video source has been passed as a parameter
    /*if(argv[1] == NULL)
    {
        ROS_INFO("argv[1]=NULL\n");
        return 1;
    }
    */
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);
	Mat distortion_coefficients;
	Mat camera_matrix = Mat(3, 3, CV_32FC1);
    Mat undistort_frame;
    FileStorage file_storage("/home/ubuntu/catkin_ws/src/opencv_image/src/out_camera_data.xml", FileStorage::READ);
    file_storage["Camera_Matrix"] >> camera_matrix;
    file_storage["Distortion_Coefficients"] >> distortion_coefficients;
    file_storage.release();
    
    // Convert the passed as command line parameter index for the video device to an integer
    /*std::istringstream video_sourceCmd(argv[1]);
    int video_source;
    // Check if it is indeed a number
    if(!(video_sourceCmd >> video_source))
    {
        ROS_INFO("video_sourceCmd is %d\n",video_source);
        return 1;
    }
    
    //int video_source = 0;*/
    cv::VideoCapture cap(0);
    // Check if video device can be opened with the given index
    while(!cap.isOpened())
    {
		cap.open(0);
		usleep(500000);
        //ROS_INFO("can not opencv video device\n");
        //return 1;
    }
	
    cv::Mat frame;
    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate(30);
    while (nh.ok()) {
        cap >> frame;
		undistort_frame = frame.clone();
        
        
        undistort(frame, undistort_frame, camera_matrix, distortion_coefficients);
        // Check if grabbed frame is actually full with some content
        if(!frame.empty()) {
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", undistort_frame).toImageMsg();
            pub.publish(msg);
            //cv::Wait(1);
        }
        
        ros::spinOnce();
        loop_rate.sleep();
    }
}
