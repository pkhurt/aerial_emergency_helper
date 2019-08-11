#include <iostream>
#include <string>

using namespace std;
/*
    The task: After natural disasters or hazards there are often problems finding emergency exits to the people that need help. Especially bringing goods over landway and help people to escape is one of the main difficult tasks.
    1. Helpers should not be in danger as well
    2. Affected people can get ill / need food and medicine,... 
    3. ...
*/

// Global Variables
string HOME_PATH = getenv("HOME");
string IMAGE_PATH = HOME_PATH + "/" + "Pictures" + "/" + "aerial_footage";

main()
{
    // load aerial image
    cout << "Loading aerial images from " + IMAGE_PATH << endl;

    // edge extraction -> will only work with clear edges
    cout << "Extracting edges..." << endl;

    // Extract coordinates
    cout << "Extracting coordinates..." << endl;
}