#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup ptsv
int64_t ptsv(
    int64_t n, int64_t nrhs,
    float* D,
    float* E,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_sptsv(
        &n_, &nrhs_,
        D,
        E,
        B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup ptsv
int64_t ptsv(
    int64_t n, int64_t nrhs,
    double* D,
    double* E,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_dptsv(
        &n_, &nrhs_,
        D,
        E,
        B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup ptsv
int64_t ptsv(
    int64_t n, int64_t nrhs,
    float* D,
    std::complex<float>* E,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_cptsv(
        &n_, &nrhs_,
        D,
        (lapack_complex_float*) E,
        (lapack_complex_float*) B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the solution to a system of linear equations
/// \f$ A X = B, \f$ where A is an n-by-n Hermitian positive definite tridiagonal
/// matrix, and X and B are n-by-nrhs matrices.
///
/// A is factored as \f$ A = L D L^H, \f$ and the factored form of A is then
/// used to solve the system of equations.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrix B. nrhs >= 0.
///
/// @param[in,out] D
///     The vector D of length n.
///     On entry, the n diagonal elements of the tridiagonal matrix
///     A. On exit, the n diagonal elements of the diagonal matrix
///     D from the factorization \f$ A = L D L^H. \f$
///
/// @param[in,out] E
///     The vector E of length n-1.
///     On entry, the (n-1) subdiagonal elements of the tridiagonal
///     matrix A. On exit, the (n-1) subdiagonal elements of the
///     unit bidiagonal factor L from the \f$ L D L^H \f$ factorization of
///     A. E can also be regarded as the superdiagonal of the unit
///     bidiagonal factor U from the \f$ U^H D U \f$ factorization of A.
///
/// @param[in,out] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     On entry, the n-by-nrhs right hand side matrix B.
///     On successful exit, the n-by-nrhs solution matrix X.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @retval = 0: successful exit
/// @retval > 0: if return value = i, the leading minor of order i is not
///     positive definite, and the solution has not been
///     computed. The factorization has not been completed
///     unless i = n.
///
/// @ingroup ptsv
int64_t ptsv(
    int64_t n, int64_t nrhs,
    double* D,
    std::complex<double>* E,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    LAPACK_zptsv(
        &n_, &nrhs_,
        D,
        (lapack_complex_double*) E,
        (lapack_complex_double*) B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
