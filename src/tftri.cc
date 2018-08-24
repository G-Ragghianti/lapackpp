#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t tftri(
    lapack::Op transr, lapack::Uplo uplo, lapack::Diag diag, int64_t n,
    float* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_stftri(
        &transr_, &uplo_, &diag_, &n_,
        A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tftri(
    lapack::Op transr, lapack::Uplo uplo, lapack::Diag diag, int64_t n,
    double* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_dtftri(
        &transr_, &uplo_, &diag_, &n_,
        A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tftri(
    lapack::Op transr, lapack::Uplo uplo, lapack::Diag diag, int64_t n,
    std::complex<float>* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_ctftri(
        &transr_, &uplo_, &diag_, &n_,
        (lapack_complex_float*) A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tftri(
    lapack::Op transr, lapack::Uplo uplo, lapack::Diag diag, int64_t n,
    std::complex<double>* A )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    LAPACK_ztftri(
        &transr_, &uplo_, &diag_, &n_,
        (lapack_complex_double*) A, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
