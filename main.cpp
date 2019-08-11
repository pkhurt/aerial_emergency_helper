#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>

using namespace std;
using namespace cv;
/*
    The task: After natural disasters or hazards there are often problems finding emergency exits to the people that need help. Especially bringing goods over landway and help people to escape is one of the main difficult tasks.
    1. Helpers should not be in danger as well
    2. Affected people can get ill / need food and medicine,... 
    3. ...

    Dependencies: -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imcodecs
*/

// Global Variables
string HOME_PATH = getenv("HOME");
string IMAGE_PATH = HOME_PATH + "/" + "Pictures" + "/" + "aerial_footage";

/**
 * pathExist(const std::string) returns true if the given path exists and false if the given path does not exist 
 * 
 * @param Path string
 * @return True or False
 */
bool pathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

int main()
{
    // ---------------------------------------- //
    // LOAD AERIAL IMAGES
    // exist path
    if ( !pathExist(IMAGE_PATH) ) return 1;
    cout << "Loading aerial images from " + IMAGE_PATH << endl;

    vector<cv::String> fn;
    glob(IMAGE_PATH, fn, false); // get all filenames in directory

    vector<Mat> image_data;
    vector<String> image_names;
    for (size_t k=0; k<fn.size(); ++k) // loop through all images
    {
        Mat image = imread(fn[k], CV_LOAD_IMAGE_COLOR);

        if (image.empty()) continue; 
        
        // store names and images
        image_names.push_back(fn[k]);
        image_data.push_back(image);
    }

    namedWindow( image_names[0], WINDOW_NORMAL );// Create a window for display.
    
    imshow( image_names[0], image_data[0] );                   // Show our image inside it.
    resizeWindow(image_names[0], 600, 600); // resize window

    waitKey(0);

    // ---------------------------------------- //
    // edge extraction -> will only work with clear edges
    cout << "Extracting edges..." << endl;

    // ---------------------------------------- //
    // Extract coordinates
    cout << "Extracting coordinates..." << endl;

    return 0;
}