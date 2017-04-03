#pragma once
#include "common/base_matrix.h"
#include "types-fpga.h"

namespace amunmt {
namespace FPGA {
namespace mblas {

class Matrix : public BaseMatrix {
public:
  Matrix(const OpenCLInfo &openCLInfo);
  Matrix(const OpenCLInfo &openCLInfo, size_t rows, size_t cols, bool zero = false);
  Matrix(const OpenCLInfo &openCLInfo, size_t rows, size_t cols, float *val);

  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  virtual ~Matrix();

  virtual size_t dim(size_t i) const
  {
    switch (i) {
    case 0: return rows_;
    case 1: return cols_;
    case 2: return 1;
    case 3: return 1;
    default:
      abort();
    }
  }

  virtual void Resize(size_t rows, size_t cols, size_t beam = 1, size_t batches = 1);

  const OpenCLInfo &GetOpenCLInfo() const
  { return openCLInfo_; }

  cl_mem &data()
  { return mem_; }

  const cl_mem &data() const
  { return mem_; }

  virtual std::string Debug(size_t detailed = 0) const;

  void Swap(Matrix &other);

  void Set(const float *data);

protected:
  const OpenCLInfo &openCLInfo_;
  cl_mem mem_;
  size_t rows_, cols_;
  size_t arrSize_;

};


}
}
}
