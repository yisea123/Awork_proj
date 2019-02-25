#ifndef ZAL_FD_UTIL_NMS_H_
#define ZAL_FD_UTIL_NMS_H_

#include <vector>

#include "zal_common.h"

namespace zal {
namespace fd {

void NonMaximumSuppression(std::vector<zal::FaceInfo>* bboxes,
  std::vector<zal::FaceInfo>* bboxes_nms, float iou_thresh = 0.8f);

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_UTIL_NMS_H_
