#ifndef ZAL_FD_CLASSIFIER_H_
#define ZAL_FD_CLASSIFIER_H_

#include "zal_common.h"
#include "zal_feature_map.h"

namespace zal {
namespace fd {

enum ClassifierType {
    LAB_Boosted_Classifier,
    SURF_MLP
};

class Classifier {
 public:
  Classifier() {}
  virtual ~Classifier() {}

  virtual void SetFeatureMap(zal::fd::FeatureMap* feat_map) = 0;
  virtual bool Classify(float* score = nullptr, float* outputs = nullptr) = 0;
  
  virtual zal::fd::ClassifierType type() = 0;

  DISABLE_COPY_AND_ASSIGN(Classifier);
};

}  // namespace fd
}  // namespace zal

#endif  // zal_FD_CLASSIFIER_H_