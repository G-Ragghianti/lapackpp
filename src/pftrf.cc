#include "lapack_fortran.h"
#include "lapack_util.hh"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t pftrf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    float* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_spftrf( &transr_, &uplo_, &n_, A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pftrf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    double* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_dpftrf( &transr_, &uplo_, &n_, A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pftrf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<float>* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_cpftrf( &transr_, &uplo_, &n_, A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pftrf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<double>* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_zpftrf( &transr_, &uplo_, &n_, A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack