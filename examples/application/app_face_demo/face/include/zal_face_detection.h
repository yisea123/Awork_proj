#ifndef ZAL_FACE_DETECTION_H_
#define ZAL_FACE_DETECTION_H_

#include <cstdint>
#include <vector>
#include "zal_common.h"
#include "zal_detector.h"

namespace zal{
class FaceDetection {
public:
	ZAL_API explicit FaceDetection(const char* model_path);
	ZAL_API ~FaceDetection();

	ZAL_API std::vector<zal::FaceInfo> Detect(const zal::ImageData & img);
	ZAL_API void SetMinFaceSize(int32_t size);
	ZAL_API void SetMaxFaceSize(int32_t size);
	ZAL_API void SetImagePyramidScaleFactor(float factor);
	ZAL_API void SetWindowStep(int32_t step_x, int32_t step_y);
	ZAL_API void SetScoreThresh(float thresh);
	DISABLE_COPY_AND_ASSIGN(FaceDetection);
private:
	class Impl;
	Impl* impl_;
};
}

#endif // !ZAL_FACE_DETECTION_H_
