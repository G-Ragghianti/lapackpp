#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t hptri(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    #if 1
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = ipiv_;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (n) );

    LAPACK_chptri(
        &uplo_, &n_,
        (lapack_complex_float*) AP,
        ipiv_ptr,
        (lapack_complex_float*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t hptri(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    #if 1
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = ipiv_;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (n) );

    LAPACK_zhptri(
        &uplo_, &n_,
        (lapack_complex_double*) AP,
        ipiv_ptr,
        (lapack_complex_double*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
