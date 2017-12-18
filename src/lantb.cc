#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup norm
float lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    float const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(k) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
    }
    char norm_ = norm2char( norm );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    blas_int n_ = (blas_int) n;
    blas_int k_ = (blas_int) k;
    blas_int ldab_ = (blas_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    std::vector< float > work( max(1,lwork) );

    return LAPACK_slantb( &norm_, &uplo_, &diag_, &n_, &k_, AB, &ldab_, &work[0] );
}

// -----------------------------------------------------------------------------
/// @ingroup norm
double lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    double const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(k) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
    }
    char norm_ = norm2char( norm );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    blas_int n_ = (blas_int) n;
    blas_int k_ = (blas_int) k;
    blas_int ldab_ = (blas_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    std::vector< double > work( max(1,lwork) );

    return LAPACK_dlantb( &norm_, &uplo_, &diag_, &n_, &k_, AB, &ldab_, &work[0] );
}

// -----------------------------------------------------------------------------
/// @ingroup norm
float lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    std::complex<float> const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(k) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
    }
    char norm_ = norm2char( norm );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    blas_int n_ = (blas_int) n;
    blas_int k_ = (blas_int) k;
    blas_int ldab_ = (blas_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    std::vector< float > work( max(1,lwork) );

    return LAPACK_clantb( &norm_, &uplo_, &diag_, &n_, &k_, AB, &ldab_, &work[0] );
}

// -----------------------------------------------------------------------------
/// Returns the value of the one norm, Frobenius norm,
/// infinity norm, or the element of largest absolute value of an
/// n-by-n triangular band matrix A, with (k + 1) diagonals.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] norm
///     Specifies the value to be returned:
///     - lapack::Norm::Max: max norm: max(abs(A(i,j))).
///                          Note this is not a consistent matrix norm.
///     - lapack::Norm::One: one norm: maximum column sum
///     - lapack::Norm::Inf: infinity norm: maximum row sum
///     - lapack::Norm::Fro: Frobenius norm: square root of sum of squares
///
/// @param[in] uplo
///     Specifies whether the matrix A is upper or lower triangular.
///     - lapack::Uplo::Upper: Upper triangular
///     - lapack::Uplo::Lower: Lower triangular
///
/// @param[in] diag
///     Specifies whether or not the matrix A is unit triangular.
///     - lapack::Diag::NonUnit: Non-unit triangular
///     - lapack::Diag::Unit: Unit triangular
///
/// @param[in] n
///     The order of the matrix A. n >= 0. When n = 0, returns zero.
///
/// @param[in] k
///     If uplo = Upper, the number of super-diagonals of the matrix A;
///     \n
///     if uplo = Lower, the number of sub-diagonals of the matrix A
///     \n
///     k >= 0.
///
/// @param[in] AB
///     The n-by-n matrix AB, stored in an ldab-by-n array.
///     The upper or lower triangular band matrix A, stored in the
///     first k+1 rows of AB. The j-th column of A is stored
///     in the j-th column of the array AB as follows:
///     \n
///     if uplo = Upper, AB(k+1+i-j,j) = A(i,j) for max(1,j-k)<=i<=j;
///     \n
///     if uplo = Lower, AB(1+i-j,j) = A(i,j) for j<=i<=min(n,j+k).
///     Note that when diag = 'U', the elements of the array AB
///     corresponding to the diagonal elements of the matrix A are
///     not referenced, but are assumed to be one.
///
/// @param[in] ldab
///     The leading dimension of the array AB. ldab >= k+1.
///
/// @ingroup norm
double lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    std::complex<double> const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(k) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldab) > std::numeric_limits<blas_int>::max() );
    }
    char norm_ = norm2char( norm );
    char uplo_ = uplo2char( uplo );
    char diag_ = diag2char( diag );
    blas_int n_ = (blas_int) n;
    blas_int k_ = (blas_int) k;
    blas_int ldab_ = (blas_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    std::vector< double > work( max(1,lwork) );

    return LAPACK_zlantb( &norm_, &uplo_, &diag_, &n_, &k_, AB, &ldab_, &work[0] );
}

}  // namespace lapack