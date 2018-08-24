#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    float const* AP,
    float* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_stpttf(
        &transr_, &uplo_, &n_,
        AP,
        ARF, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    double const* AP,
    double* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_dtpttf(
        &transr_, &uplo_, &n_,
        AP,
        ARF, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<float> const* AP,
    std::complex<float>* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_ctpttf(
        &transr_, &uplo_, &n_,
        (lapack_complex_float*) AP,
        (lapack_complex_float*) ARF, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<double> const* AP,
    std::complex<double>* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_ztpttf(
        &transr_, &uplo_, &n_,
        (lapack_complex_double*) AP,
        (lapack_complex_double*) ARF, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
