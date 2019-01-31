#include "utility.h"

namespace ml_cam {

void setLabel(cv::Mat& im, const std::string label, const cv::Point & origin)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.5;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::rectangle(im, origin + cv::Point(0, baseline), origin + cv::Point(text.width, -text.height), cv::Scalar(0,255,0), cv::FILLED);
    cv::putText(im, label, origin, fontface, scale, cv::Scalar(0,0,0), thickness, 8);

}


std::string expand_user(std::string path) {
	if (!path.empty() && path[0] == '~') {
		assert(path.size() == 1 || path[1] == '/');  // or other error handling
		char const* home = getenv("HOME");
		if (home || ((home = getenv("USERPROFILE")))) {
			path.replace(0, 1, home);
		}
		else {
			char const *hdrive = getenv("HOMEDRIVE"),
				*hpath = getenv("HOMEPATH");
			assert(hdrive);  // or other error handling
			assert(hpath);
			path.replace(0, 1, std::string(hdrive) + hpath);
		}
	}
	return path;
}

}