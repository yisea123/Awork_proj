#ifndef zal_FD_CLASSIFIER_SURF_MLP_H_
#define zal_FD_CLASSIFIER_SURF_MLP_H_

#include <memory>
#include <vector>

#include "zal_classifier.h"
#include "classifier/zal_mlp.h"
#include "feat/zal_surf_feature_map.h"

namespace zal {
namespace fd {

class SURFMLP : public Classifier {
 public:
  SURFMLP() : Classifier(), model_(new zal::fd::MLP()) {}
  virtual ~SURFMLP() {}

  virtual bool Classify(float* score = nullptr, float* outputs = nullptr);

  inline virtual void SetFeatureMap(zal::fd::FeatureMap* feat_map) {
	  feat_map_ = dynamic_cast<zal::fd::SURFFeatureMap*>(feat_map);
  }

  inline virtual zal::fd::ClassifierType type() {
    return zal::fd::ClassifierType::SURF_MLP;
  }

  void AddFeatureByID(int32_t feat_id);
  void AddLayer(int32_t input_dim, int32_t output_dim, const float* weights,
    const float* bias, bool is_output = false);

  inline void SetThreshold(float thresh) { thresh_ = thresh; }

 private:
  std::vector<int32_t> feat_id_;
  std::vector<float> input_buf_;
  std::vector<float> output_buf_;

  std::shared_ptr<zal::fd::MLP> model_;
  float thresh_;
  zal::fd::SURFFeatureMap* feat_map_;
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_CLASSIFIER_SURF_MLP_H_
