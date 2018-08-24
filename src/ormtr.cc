#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup syev_computational
int64_t ormtr(
    lapack::Side side, lapack::Uplo uplo, lapack::Op trans, int64_t m, int64_t n,
    float const* A, int64_t lda,
    float const* tau,
    float* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // for real, map ConjTrans to Trans
    if (trans_ == 'C')
        trans_ = 'T';

    // query for workspace size
    float qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_sormtr(
        &side_, &uplo_, &trans_, &m_, &n_,
        A, &lda_,
        tau,
        C, &ldc_,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );

    LAPACK_sormtr(
        &side_, &uplo_, &trans_, &m_, &n_,
        A, &lda_,
        tau,
        C, &ldc_,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @see lapack::unmtr
/// @ingroup syev_computational
int64_t ormtr(
    lapack::Side side, lapack::Uplo uplo, lapack::Op trans, int64_t m, int64_t n,
    double const* A, int64_t lda,
    double const* tau,
    double* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char uplo_ = uplo2char( uplo );
    char trans_ = op2char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // for real, map ConjTrans to Trans
    if (trans_ == 'C')
        trans_ = 'T';

    // query for workspace size
    double qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_dormtr(
        &side_, &uplo_, &trans_, &m_, &n_,
        A, &lda_,
        tau,
        C, &ldc_,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );

    LAPACK_dormtr(
        &side_, &uplo_, &trans_, &m_, &n_,
        A, &lda_,
        tau,
        C, &ldc_,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
