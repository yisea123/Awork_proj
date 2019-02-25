#ifndef ZAL_FD_IO_LAB_BOOST_MODEL_READER_H_
#define ZAL_FD_IO_LAB_BOOST_MODEL_READER_H_

#include <istream>
#include <vector>

#include "zal_model_reader.h"
#include "classifier/zal_lab_boosted_classifier.h"

namespace zal {
namespace fd {

class LABBoostModelReader : public ModelReader {
 public:
	 LABBoostModelReader() : ModelReader() {}
	 virtual ~LABBoostModelReader() {}

	 virtual bool Read(std::istream* input, zal::fd::Classifier* model);
 private:
	 bool ReadFeatureParam(std::istream* input,
		 zal::fd::LABBoostedClassifier* model);
	 bool ReadBaseClassifierParam(std::istream* input,
		 zal::fd::LABBoostedClassifier* model);
	 int32_t num_bin_;
	 int32_t num_base_classifer_;
};

}  // namespace fd
}  // namespace zal

#endif  // ZAL_FD_IO_LAB_BOOST_MODEL_READER_H_
