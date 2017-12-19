#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup heev_computational
int64_t ungtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float> const* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_cungtr( &uplo_, &n_, A, &lda_, tau, qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_cungtr( &uplo_, &n_, A, &lda_, tau, &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Generates a complex unitary matrix Q which is defined as the
/// product of n-1 elementary reflectors of order n, as returned by
/// `lapack::hetrd`:
///
/// if uplo = Upper, Q = H(n-1) . . . H(2) H(1),
///
/// if uplo = Lower, Q = H(1) H(2) . . . H(n-1).
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this is an alias for `lapack::orgtr`.
///
/// @param[in] uplo
///     - lapack::Uplo::Upper: Upper triangle of A contains elementary reflectors
///         from `lapack::hetrd`;
///     - lapack::Uplo::Lower: Lower triangle of A contains elementary reflectors
///         from `lapack::hetrd`.
///
/// @param[in] n
///     The order of the matrix Q. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     On entry, the vectors which define the elementary reflectors,
///     as returned by `lapack::hetrd`.
///     On exit, the n-by-n unitary matrix Q.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= n.
///
/// @param[in] tau
///     The vector tau of length n-1.
///     tau(i) must contain the scalar factor of the elementary
///     reflector H(i), as returned by `lapack::hetrd`.
///
/// @retval = 0: successful exit
///
/// @ingroup heev_computational
int64_t ungtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double> const* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_zungtr( &uplo_, &n_, A, &lda_, tau, qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zungtr( &uplo_, &n_, A, &lda_, tau, &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
