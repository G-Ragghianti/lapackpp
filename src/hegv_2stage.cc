#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION >= 30700  // >= 3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t hegv_2stage(
    int64_t itype, lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb,
    float* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    lapack_int ineg_one = -1;
    LAPACK_chegv_2stage(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        W,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( (max( 1, 3*n-2 )) );

    LAPACK_chegv_2stage(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        W,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t hegv_2stage(
    int64_t itype, lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb,
    double* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    lapack_int ineg_one = -1;
    LAPACK_zhegv_2stage(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        W,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( (max( 1, 3*n-2 )) );

    LAPACK_zhegv_2stage(
        &itype_, &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        W,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.7
