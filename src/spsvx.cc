#include "lapack_fortran.h"
#include "lapack_util.hh"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t spsvx(
    lapack::Factored fact, lapack::Uplo uplo, int64_t n, int64_t nrhs,
    float const* AP,
    float* AFP,
    int64_t* ipiv,
    float const* B, int64_t ldb,
    float* X, int64_t ldx,
    float* rcond,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_sspsvx( &fact_, &uplo_, &n_, &nrhs_, AP, AFP, ipiv_ptr, B, &ldb_, X, &ldx_, rcond, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t spsvx(
    lapack::Factored fact, lapack::Uplo uplo, int64_t n, int64_t nrhs,
    double const* AP,
    double* AFP,
    int64_t* ipiv,
    double const* B, int64_t ldb,
    double* X, int64_t ldx,
    double* rcond,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (3*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_dspsvx( &fact_, &uplo_, &n_, &nrhs_, AP, AFP, ipiv_ptr, B, &ldb_, X, &ldx_, rcond, ferr, berr, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t spsvx(
    lapack::Factored fact, lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<float> const* AP,
    std::complex<float>* AFP,
    int64_t* ipiv,
    std::complex<float> const* B, int64_t ldb,
    std::complex<float>* X, int64_t ldx,
    float* rcond,
    float* ferr,
    float* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (2*n) );
    std::vector< float > rwork( (n) );

    LAPACK_cspsvx( &fact_, &uplo_, &n_, &nrhs_, AP, AFP, ipiv_ptr, B, &ldb_, X, &ldx_, rcond, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t spsvx(
    lapack::Factored fact, lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<double> const* AP,
    std::complex<double>* AFP,
    int64_t* ipiv,
    std::complex<double> const* B, int64_t ldb,
    std::complex<double>* X, int64_t ldx,
    double* rcond,
    double* ferr,
    double* berr )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char fact_ = factored2char( fact );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (2*n) );
    std::vector< double > rwork( (n) );

    LAPACK_zspsvx( &fact_, &uplo_, &n_, &nrhs_, AP, AFP, ipiv_ptr, B, &ldb_, X, &ldx_, rcond, ferr, berr, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

}  // namespace lapack