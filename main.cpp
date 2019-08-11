#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <stdlib.h>

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

Mat src_image, src_image_gray;
Mat dst_image, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

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

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_image_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst_image = Scalar::all(0);

  src_image.copyTo(dst_image, detected_edges);
  imshow( window_name, dst_image );
  resizeWindow(window_name, 600, 600); // resize window

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
        src_image = imread(fn[k], CV_LOAD_IMAGE_COLOR);

        if (src_image.empty()) continue; 
        
        // store names and images
        image_names.push_back(fn[k]);
        image_data.push_back(src_image);
    }

    cout << "Found " << image_names.size() << " image(s) for processing." << endl;

    // ---------------------------------------- //
    // edge extraction -> will only work with clear edges
    cout << "Extracting edges..." << endl;
    // process all found images
    for (size_t k=0; k<image_names.size(); ++k)
    {
        cout << "Processing image " << image_names[k] << endl;

        // USING CANNY EDGE DETECTOR OF OPENCV
        //create a matrix of the same type and size as src image
        dst_image.create(src_image.size(), src_image.type());

        // Convert image to grayscale
        cvtColor(src_image, src_image_gray, CV_BGR2GRAY);

        namedWindow( window_name, WINDOW_NORMAL );// Create a window for display.
    
        //imshow( image_names[k], image_data[k] );  // Show our image inside it.

        createTrackbar("Min threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

        CannyThreshold(0, 0);

        waitKey(0);
    }

    // ---------------------------------------- //
    // Extract coordinates
    cout << "Extracting coordinates..." << endl;

    return 0;
}