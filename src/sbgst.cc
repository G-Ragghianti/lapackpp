#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t sbgst(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t ka, int64_t kb,
    float* AB, int64_t ldab,
    float const* BB, int64_t ldbb,
    float* X, int64_t ldx )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ka) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(kb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldbb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldx) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int ka_ = (lapack_int) ka;
    lapack_int kb_ = (lapack_int) kb;
    lapack_int ldab_ = (lapack_int) ldab;
    lapack_int ldbb_ = (lapack_int) ldbb;
    lapack_int ldx_ = (lapack_int) ldx;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (2*n) );

    LAPACK_ssbgst(
        &jobz_, &uplo_, &n_, &ka_, &kb_,
        AB, &ldab_,
        BB, &ldbb_,
        X, &ldx_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sbgst(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t ka, int64_t kb,
    double* AB, int64_t ldab,
    double const* BB, int64_t ldbb,
    double* X, int64_t ldx )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ka) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(kb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldbb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldx) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int ka_ = (lapack_int) ka;
    lapack_int kb_ = (lapack_int) kb;
    lapack_int ldab_ = (lapack_int) ldab;
    lapack_int ldbb_ = (lapack_int) ldbb;
    lapack_int ldx_ = (lapack_int) ldx;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (2*n) );

    LAPACK_dsbgst(
        &jobz_, &uplo_, &n_, &ka_, &kb_,
        AB, &ldab_,
        BB, &ldbb_,
        X, &ldx_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
