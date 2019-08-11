#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sys/stat.h>

using namespace std;
using namespace cv;
/*
    The task: After natural disasters or hazards there are often problems finding emergency exits to the people that need help. Especially bringing goods over landway and help people to escape is one of the main difficult tasks.
    1. Helpers should not be in danger as well
    2. Affected people can get ill / need food and medicine,... 
    3. ...
*/

// Global Variables
string HOME_PATH = getenv("HOME");
string IMAGE_PATH = HOME_PATH + "/" + "Pictures" + "/" + "aerial_footage" + "/" + "erdrutsch.jpg";

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

    cv::String path(IMAGE_PATH);
    //glob(IMAGE_PATH, fn, false); // get all filenames in directory

    //Mat image;
    //image = imread(IMAGE_PATH, CV_LOAD_IMAGE_COLOR);

    // ---------------------------------------- //
    // edge extraction -> will only work with clear edges
    cout << "Extracting edges..." << endl;

    // ---------------------------------------- //
    // Extract coordinates
    cout << "Extracting coordinates..." << endl;

    return 0;
}