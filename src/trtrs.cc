#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t trtrs(
    lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t n, int64_t nrhs,
    float const* A, int64_t lda,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_strtrs(
        &uplo_, &trans_, &diag_, &n_, &nrhs_,
        A, &lda_,
        B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t trtrs(
    lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t n, int64_t nrhs,
    double const* A, int64_t lda,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_dtrtrs(
        &uplo_, &trans_, &diag_, &n_, &nrhs_,
        A, &lda_,
        B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t trtrs(
    lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t n, int64_t nrhs,
    std::complex<float> const* A, int64_t lda,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_ctrtrs(
        &uplo_, &trans_, &diag_, &n_, &nrhs_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t trtrs(
    lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t n, int64_t nrhs,
    std::complex<double> const* A, int64_t lda,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    char diag_ = diag2char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_ztrtrs(
        &uplo_, &trans_, &diag_, &n_, &nrhs_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
