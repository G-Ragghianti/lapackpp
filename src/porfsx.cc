#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION_MAJOR >= 3 && LAPACK_VERSION_MINOR >= 3  // >= v3.3

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t porfsx(
    lapack::Uplo uplo, lapack::Equed equed, int64_t n, int64_t nrhs,
    float const* A, int64_t lda,
    float const* AF, int64_t ldaf,
    float* S,
    float const* B, int64_t ldb,
    float* X, int64_t ldx,
    float* rcond,
    float* berr, int64_t n_err_bnds,
    float* ERR_BNDS_NORM,
    float* ERR_BNDS_COMP, int64_t nparams,
    float* PARAMS )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n_err_bnds) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nparams) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char equed_ = equed2char( equed );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int n_err_bnds_ = (blas_int) n_err_bnds;
    blas_int nparams_ = (blas_int) nparams;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (4*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_sporfsx( &uplo_, &equed_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, S, B, &ldb_, X, &ldx_, rcond, berr, &n_err_bnds_, ERR_BNDS_NORM, ERR_BNDS_COMP, &nparams_, PARAMS, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t porfsx(
    lapack::Uplo uplo, lapack::Equed equed, int64_t n, int64_t nrhs,
    double const* A, int64_t lda,
    double const* AF, int64_t ldaf,
    double* S,
    double const* B, int64_t ldb,
    double* X, int64_t ldx,
    double* rcond,
    double* berr, int64_t n_err_bnds,
    double* ERR_BNDS_NORM,
    double* ERR_BNDS_COMP, int64_t nparams,
    double* PARAMS )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n_err_bnds) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nparams) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char equed_ = equed2char( equed );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int n_err_bnds_ = (blas_int) n_err_bnds;
    blas_int nparams_ = (blas_int) nparams;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (4*n) );
    std::vector< blas_int > iwork( (n) );

    LAPACK_dporfsx( &uplo_, &equed_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, S, B, &ldb_, X, &ldx_, rcond, berr, &n_err_bnds_, ERR_BNDS_NORM, ERR_BNDS_COMP, &nparams_, PARAMS, &work[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t porfsx(
    lapack::Uplo uplo, lapack::Equed equed, int64_t n, int64_t nrhs,
    std::complex<float> const* A, int64_t lda,
    std::complex<float> const* AF, int64_t ldaf,
    float* S,
    std::complex<float> const* B, int64_t ldb,
    std::complex<float>* X, int64_t ldx,
    float* rcond,
    float* berr, int64_t n_err_bnds,
    float* ERR_BNDS_NORM,
    float* ERR_BNDS_COMP, int64_t nparams,
    float* PARAMS )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n_err_bnds) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nparams) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char equed_ = equed2char( equed );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int n_err_bnds_ = (blas_int) n_err_bnds;
    blas_int nparams_ = (blas_int) nparams;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (2*n) );
    std::vector< float > rwork( (2*n) );

    LAPACK_cporfsx( &uplo_, &equed_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, S, B, &ldb_, X, &ldx_, rcond, berr, &n_err_bnds_, ERR_BNDS_NORM, ERR_BNDS_COMP, &nparams_, PARAMS, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t porfsx(
    lapack::Uplo uplo, lapack::Equed equed, int64_t n, int64_t nrhs,
    std::complex<double> const* A, int64_t lda,
    std::complex<double> const* AF, int64_t ldaf,
    double* S,
    std::complex<double> const* B, int64_t ldb,
    std::complex<double>* X, int64_t ldx,
    double* rcond,
    double* berr, int64_t n_err_bnds,
    double* ERR_BNDS_NORM,
    double* ERR_BNDS_COMP, int64_t nparams,
    double* PARAMS )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldaf) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n_err_bnds) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nparams) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    char equed_ = equed2char( equed );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldaf_ = (blas_int) ldaf;
    blas_int ldb_ = (blas_int) ldb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int n_err_bnds_ = (blas_int) n_err_bnds;
    blas_int nparams_ = (blas_int) nparams;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (2*n) );
    std::vector< double > rwork( (2*n) );

    LAPACK_zporfsx( &uplo_, &equed_, &n_, &nrhs_, A, &lda_, AF, &ldaf_, S, B, &ldb_, X, &ldx_, rcond, berr, &n_err_bnds_, ERR_BNDS_NORM, ERR_BNDS_COMP, &nparams_, PARAMS, &work[0], &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= v3.3
