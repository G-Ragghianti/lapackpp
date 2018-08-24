#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup norm
float lanst(
    lapack::Norm norm, int64_t n,
    float const* D,
    float const* E )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = norm2char( norm );
    lapack_int n_ = (lapack_int) n;

    return LAPACK_slanst( &norm_, &n_, D, E );
}

// -----------------------------------------------------------------------------
/// Returns the value of the one norm, Frobenius norm,
/// infinity norm, or the element of largest absolute value of a
/// symmetric tridiagonal matrix A.
///
/// Overloaded versions are available for
/// `float`, `double`.
/// For real matrices, `lapack::lanht` is an alias for this.
/// For complex matrices, see `lapack::lanht`.
///
/// @param[in] norm
///     The value to be returned:
///     - lapack::Norm::Max: max norm: max(abs(A(i,j))).
///                          Note this is not a consistent matrix norm.
///     - lapack::Norm::One: one norm: maximum column sum
///     - lapack::Norm::Inf: infinity norm: maximum row sum
///     - lapack::Norm::Fro: Frobenius norm: square root of sum of squares
///
/// @param[in] n
///     The order of the matrix A. n >= 0. When n = 0, returns zero.
///
/// @param[in] D
///     The vector D of length n.
///     The diagonal elements of A.
///
/// @param[in] E
///     The vector E of length n-1.
///     The (n-1) sub-diagonal or super-diagonal elements of A.
///
/// @ingroup norm
double lanst(
    lapack::Norm norm, int64_t n,
    double const* D,
    double const* E )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = norm2char( norm );
    lapack_int n_ = (lapack_int) n;

    return LAPACK_dlanst( &norm_, &n_, D, E );
}

}  // namespace lapack
