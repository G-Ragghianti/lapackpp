#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION_MAJOR >= 3 && LAPACK_VERSION_MINOR >= 7  // >= 3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t sbev_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t kd,
    float* AB, int64_t ldab,
    float* W,
    float* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kd) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int kd_ = (blas_int) kd;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_ssbev_2stage( &jobz_, &uplo_, &n_, &kd_, AB, &ldab_, W, Z, &ldz_, qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );

    LAPACK_ssbev_2stage( &jobz_, &uplo_, &n_, &kd_, AB, &ldab_, W, Z, &ldz_, &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sbev_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t kd,
    double* AB, int64_t ldab,
    double* W,
    double* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kd) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int kd_ = (blas_int) kd;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_dsbev_2stage( &jobz_, &uplo_, &n_, &kd_, AB, &ldab_, W, Z, &ldz_, qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );

    LAPACK_dsbev_2stage( &jobz_, &uplo_, &n_, &kd_, AB, &ldab_, W, Z, &ldz_, &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.7
