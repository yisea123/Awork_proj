#ifndef ZAL_FD_DETECTOR_H_
#define ZAL_FD_DETECTOR_H_

#include <cstdint>
#include <string>
#include <vector>

#include "zal_common.h"
#include "util/zal_image_pyramid.h"

namespace zal {
namespace fd {

class Detector {
public:
	Detector() {}
	virtual ~Detector() {}

	virtual bool LoadModel(const std::string & model_path) = 0;
	virtual std::vector<zal::FaceInfo> Detect(zal::fd::ImagePyramid* img_pyramid) = 0;

	virtual void SetWindowSize(int32_t size) {}
	virtual void SetSlideWindowStep(int32_t step_x, int32_t step_y) {}

	DISABLE_COPY_AND_ASSIGN(Detector);
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_DETECTOR_H_
