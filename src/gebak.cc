#include "lapack_fortran.h"
#include "lapack_util.hh"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t gebak(
    lapack::Job job, lapack::Side side, int64_t n, int64_t ilo, int64_t ihi,
    float const* SCALE, int64_t m,
    float* V, int64_t ldv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ilo) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ihi) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
    }
    char job_ = job2char( job );
    char side_ = side2char( side );
    blas_int n_ = (blas_int) n;
    blas_int ilo_ = (blas_int) ilo;
    blas_int ihi_ = (blas_int) ihi;
    blas_int m_ = (blas_int) m;
    blas_int ldv_ = (blas_int) ldv;
    blas_int info_ = 0;

    LAPACK_sgebak( &job_, &side_, &n_, &ilo_, &ihi_, SCALE, &m_, V, &ldv_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gebak(
    lapack::Job job, lapack::Side side, int64_t n, int64_t ilo, int64_t ihi,
    double const* SCALE, int64_t m,
    double* V, int64_t ldv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ilo) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ihi) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
    }
    char job_ = job2char( job );
    char side_ = side2char( side );
    blas_int n_ = (blas_int) n;
    blas_int ilo_ = (blas_int) ilo;
    blas_int ihi_ = (blas_int) ihi;
    blas_int m_ = (blas_int) m;
    blas_int ldv_ = (blas_int) ldv;
    blas_int info_ = 0;

    LAPACK_dgebak( &job_, &side_, &n_, &ilo_, &ihi_, SCALE, &m_, V, &ldv_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gebak(
    lapack::Job job, lapack::Side side, int64_t n, int64_t ilo, int64_t ihi,
    float const* SCALE, int64_t m,
    std::complex<float>* V, int64_t ldv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ilo) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ihi) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
    }
    char job_ = job2char( job );
    char side_ = side2char( side );
    blas_int n_ = (blas_int) n;
    blas_int ilo_ = (blas_int) ilo;
    blas_int ihi_ = (blas_int) ihi;
    blas_int m_ = (blas_int) m;
    blas_int ldv_ = (blas_int) ldv;
    blas_int info_ = 0;

    LAPACK_cgebak( &job_, &side_, &n_, &ilo_, &ihi_, SCALE, &m_, V, &ldv_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t gebak(
    lapack::Job job, lapack::Side side, int64_t n, int64_t ilo, int64_t ihi,
    double const* SCALE, int64_t m,
    std::complex<double>* V, int64_t ldv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ilo) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ihi) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldv) > std::numeric_limits<blas_int>::max() );
    }
    char job_ = job2char( job );
    char side_ = side2char( side );
    blas_int n_ = (blas_int) n;
    blas_int ilo_ = (blas_int) ilo;
    blas_int ihi_ = (blas_int) ihi;
    blas_int m_ = (blas_int) m;
    blas_int ldv_ = (blas_int) ldv;
    blas_int info_ = 0;

    LAPACK_zgebak( &job_, &side_, &n_, &ilo_, &ihi_, SCALE, &m_, V, &ldv_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack