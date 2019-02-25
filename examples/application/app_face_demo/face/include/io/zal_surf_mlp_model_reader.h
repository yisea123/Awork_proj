#ifndef ZAL_FD_IO_SURF_MLP_MODEL_READER_H_
#define ZAL_FD_IO_SURF_MLP_MODEL_READER_H_

#include <iosfwd>
#include <vector>

#include "zal_model_reader.h"

namespace zal {
namespace fd {

class SURFMLPModelReader : public ModelReader {
 public:
  SURFMLPModelReader() {}
  virtual ~SURFMLPModelReader() {}

  virtual bool Read(std::istream* input, zal::fd::Classifier* model);

 private:
  std::vector<int32_t> feat_id_buf_;
  std::vector<float> weights_buf_;
  std::vector<float> bias_buf_;
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_IO_SURF_MLP_MODEL_READER_H_
