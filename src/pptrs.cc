#include "lapack_fortran.h"
#include "lapack_util.hh"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t pptrs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    float const* AP,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_spptrs( &uplo_, &n_, &nrhs_, AP, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pptrs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    double const* AP,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_dpptrs( &uplo_, &n_, &nrhs_, AP, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pptrs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<float> const* AP,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_cpptrs( &uplo_, &n_, &nrhs_, AP, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pptrs(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<double> const* AP,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_zpptrs( &uplo_, &n_, &nrhs_, AP, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack