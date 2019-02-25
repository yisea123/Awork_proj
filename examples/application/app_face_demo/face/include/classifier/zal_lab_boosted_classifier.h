#ifndef ZAL_FD_CLASSIFIER_LAB_BOOSTED_CLASSIFIER_H_
#define ZAL_FD_CLASSIFIER_LAB_BOOSTED_CLASSIFIER_H_

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

#include "zal_classifier.h"
#include "feat/zal_lab_feature_map.h"

namespace zal {
namespace fd {

/**
 * @class LABBaseClassifier
 * @brief Base classifier using LAB feature.
 */
class LABBaseClassifier {
 public:
  LABBaseClassifier()
    : num_bin_(255), thresh_(0.0f) {
    weights_.resize(num_bin_ + 1);
  }

  ~LABBaseClassifier() {}

  void SetWeights(const float* weights, int32_t num_bin);

  inline void SetThreshold(float thresh) { thresh_ = thresh; }

  inline int32_t num_bin() const { return num_bin_; }
  inline float weights(int32_t val) const { return weights_[val]; }
  inline float threshold() const { return thresh_; }

 private:
  int32_t num_bin_;

  std::vector<float> weights_;
  float thresh_;
};

/**
 * @class LABBoostedClassifier
 * @Brief A strong classifier constructed from base classifiers using LAB features.
 */
class LABBoostedClassifier : public Classifier {
 public:
  LABBoostedClassifier() : use_std_dev_(true) {}
  virtual ~LABBoostedClassifier() {}

  virtual bool Classify(float* score = nullptr, float* outputs = nullptr);

  inline virtual zal::fd::ClassifierType type() {
    return zal::fd::ClassifierType::LAB_Boosted_Classifier;
  }

  void AddFeature(int32_t x, int32_t y);
  void AddBaseClassifier(const float* weights, int32_t num_bin, float thresh);

  inline virtual void SetFeatureMap(zal::fd::FeatureMap* featMap) {
    feat_map_ = dynamic_cast<zal::fd::LABFeatureMap*>(featMap);
  }

  inline void SetUseStdDev(bool useStdDev) { use_std_dev_ = useStdDev; }

 private:
  static const int32_t kFeatGroupSize = 10;
  const float kStdDevThresh = 10.0f;

  std::vector<zal::fd::LABFeature> feat_;
  std::vector<std::shared_ptr<zal::fd::LABBaseClassifier> > base_classifiers_;
  zal::fd::LABFeatureMap* feat_map_;
  bool use_std_dev_;
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_CLASSIFIER_LAB_BOOSTED_CLASSIFIER_H_