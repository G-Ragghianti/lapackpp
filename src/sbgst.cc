#include "lapack_fortran.h"
#include "lapack_util.hh"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t sbgst(
    lapack::Vect vect, lapack::Uplo uplo, int64_t n, int64_t ka, int64_t kb,
    float* AB, int64_t ldab,
    float const* BB, int64_t ldbb,
    float* X, int64_t ldx )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ka) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldbb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char vect_ = vect2char( vect );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int ka_ = (blas_int) ka;
    blas_int kb_ = (blas_int) kb;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldbb_ = (blas_int) ldbb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (2*n) );

    LAPACK_ssbgst( &vect_, &uplo_, &n_, &ka_, &kb_, AB, &ldab_, BB, &ldbb_, X, &ldx_, &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sbgst(
    lapack::Vect vect, lapack::Uplo uplo, int64_t n, int64_t ka, int64_t kb,
    double* AB, int64_t ldab,
    double const* BB, int64_t ldbb,
    double* X, int64_t ldx )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ka) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(kb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldbb) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldx) > std::numeric_limits<blas_int>::max() );
    }
    char vect_ = vect2char( vect );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int ka_ = (blas_int) ka;
    blas_int kb_ = (blas_int) kb;
    blas_int ldab_ = (blas_int) ldab;
    blas_int ldbb_ = (blas_int) ldbb;
    blas_int ldx_ = (blas_int) ldx;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (2*n) );

    LAPACK_dsbgst( &vect_, &uplo_, &n_, &ka_, &kb_, AB, &ldab_, BB, &ldbb_, X, &ldx_, &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack