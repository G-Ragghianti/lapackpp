#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION >= 30500  // >= 3.5

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup hesv_rk_computational
int64_t hetrf_rook(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    int64_t* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #if 1
        // 32-bit copy
        std::vector< lapack_int > ipiv_( (n) );
        lapack_int* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int* ipiv_ptr = ipiv;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_chetrf_rook(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_chetrf_rook(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @deprecated Replaced by `lapack::hetrf_rk`.
/// @since LAPACK 3.5.0.
/// @ingroup hesv_rk_computational
int64_t hetrf_rook(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    int64_t* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #if 1
        // 32-bit copy
        std::vector< lapack_int > ipiv_( (n) );
        lapack_int* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int* ipiv_ptr = ipiv;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_zhetrf_rook(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zhetrf_rook(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.5
