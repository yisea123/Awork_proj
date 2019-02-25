#ifndef ZAL_FD_FUST_H_
#define ZAL_FD_FUST_H_

#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "zal_detector.h"
#include "zal_model_reader.h"
#include "zal_classifier.h"
#include "zal_feature_map.h"

namespace zal {
namespace fd {

class FuStDetector : public Detector {
public:
FuStDetector()
	: wnd_size_(40), slide_wnd_step_x_(4), slide_wnd_step_y_(4),
	num_hierarchy_(0) {
	wnd_data_buf_.resize(wnd_size_ * wnd_size_);
	wnd_data_.resize(wnd_size_ * wnd_size_);
}

~FuStDetector() {}

virtual bool LoadModel(const std::string & model_path);
virtual std::vector<zal::FaceInfo> Detect(zal::fd::ImagePyramid* img_pyramid);

inline virtual void SetWindowSize(int32_t size) {
	if (size >= 20)
		wnd_size_ = size;
}

inline virtual void SetSlideWindowStep(int32_t step_x, int32_t step_y) {
	if (step_x > 0)
		slide_wnd_step_x_ = step_x;
	if (step_y > 0)
		slide_wnd_step_y_ = step_y;
}

private:
	std::shared_ptr<zal::fd::ModelReader> CreateModelReader(zal::fd::ClassifierType type);
	std::shared_ptr<zal::fd::Classifier> CreateClassifier(zal::fd::ClassifierType type);
	std::shared_ptr<zal::fd::FeatureMap> CreateFeatureMap(zal::fd::ClassifierType type);

	void GetWindowData(const zal::ImageData & img, const zal::Rect & wnd);

	int32_t wnd_size_;
	int32_t slide_wnd_step_x_;
	int32_t slide_wnd_step_y_;

	int32_t num_hierarchy_;
	std::vector<int32_t> hierarchy_size_;
	std::vector<int32_t> num_stage_;
	std::vector<std::vector<int32_t> > wnd_src_id_;

	std::vector<uint8_t> wnd_data_buf_;
	std::vector<uint8_t> wnd_data_;

	std::vector<std::shared_ptr<zal::fd::Classifier> > model_;
	std::vector<std::shared_ptr<zal::fd::FeatureMap> > feat_map_;
	std::map<zal::fd::ClassifierType, int32_t> cls2feat_idx_;

	DISABLE_COPY_AND_ASSIGN(FuStDetector);
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_FUST_H_
