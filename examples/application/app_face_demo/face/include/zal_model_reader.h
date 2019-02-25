#ifndef ZAL_FD_MODEL_READER_H_
#define ZAL_FD_MODEL_READER_H_

#include <iosfwd>

#include "zal_classifier.h"

namespace zal {
namespace fd {

class ModelReader {
 public:
  ModelReader() {}
  virtual ~ModelReader() {}

  virtual bool Read(std::istream* input, zal::fd::Classifier* model) = 0;

  DISABLE_COPY_AND_ASSIGN(ModelReader);
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_MODEL_READER_H_
