#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION >= 30600  // >= 3.6

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::Job jobu, lapack::Job jobv, lapack::Job jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    float* A, int64_t lda,
    float* B, int64_t ldb,
    float* alpha,
    float* beta,
    float* U, int64_t ldu,
    float* V, int64_t ldv,
    float* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(p) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = job2char( jobv );
    char jobq_ = jobq2char( jobq );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int p_ = (lapack_int) p;
    lapack_int k_ = (lapack_int) *k;
    lapack_int l_ = (lapack_int) *l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldu_ = (lapack_int) ldu;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_sggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        A, &lda_,
        B, &ldb_,
        alpha,
        beta,
        U, &ldu_,
        V, &ldv_,
        Q, &ldq_,
        qry_work, &ineg_one,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< lapack_int > iwork( (n) );

    LAPACK_sggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        A, &lda_,
        B, &ldb_,
        alpha,
        beta,
        U, &ldu_,
        V, &ldv_,
        Q, &ldq_,
        &work[0], &lwork_,
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::Job jobu, lapack::Job jobv, lapack::Job jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    double* A, int64_t lda,
    double* B, int64_t ldb,
    double* alpha,
    double* beta,
    double* U, int64_t ldu,
    double* V, int64_t ldv,
    double* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(p) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = job2char( jobv );
    char jobq_ = jobq2char( jobq );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int p_ = (lapack_int) p;
    lapack_int k_ = (lapack_int) *k;
    lapack_int l_ = (lapack_int) *l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldu_ = (lapack_int) ldu;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_dggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        A, &lda_,
        B, &ldb_,
        alpha,
        beta,
        U, &ldu_,
        V, &ldv_,
        Q, &ldq_,
        qry_work, &ineg_one,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< lapack_int > iwork( (n) );

    LAPACK_dggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        A, &lda_,
        B, &ldb_,
        alpha,
        beta,
        U, &ldu_,
        V, &ldv_,
        Q, &ldq_,
        &work[0], &lwork_,
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::Job jobu, lapack::Job jobv, lapack::Job jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb,
    float* alpha,
    float* beta,
    std::complex<float>* U, int64_t ldu,
    std::complex<float>* V, int64_t ldv,
    std::complex<float>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(p) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = job2char( jobv );
    char jobq_ = jobq2char( jobq );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int p_ = (lapack_int) p;
    lapack_int k_ = (lapack_int) *k;
    lapack_int l_ = (lapack_int) *l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldu_ = (lapack_int) ldu;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_cggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        alpha,
        beta,
        (lapack_complex_float*) U, &ldu_,
        (lapack_complex_float*) V, &ldv_,
        (lapack_complex_float*) Q, &ldq_,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( (2*n) );
    std::vector< lapack_int > iwork( (n) );

    LAPACK_cggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        alpha,
        beta,
        (lapack_complex_float*) U, &ldu_,
        (lapack_complex_float*) V, &ldv_,
        (lapack_complex_float*) Q, &ldq_,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0],
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t ggsvd3(
    lapack::Job jobu, lapack::Job jobv, lapack::Job jobq, int64_t m, int64_t n, int64_t p,
    int64_t* k,
    int64_t* l,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb,
    double* alpha,
    double* beta,
    std::complex<double>* U, int64_t ldu,
    std::complex<double>* V, int64_t ldv,
    std::complex<double>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(p) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobu_ = jobu2char( jobu );
    char jobv_ = job2char( jobv );
    char jobq_ = jobq2char( jobq );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int p_ = (lapack_int) p;
    lapack_int k_ = (lapack_int) *k;
    lapack_int l_ = (lapack_int) *l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldu_ = (lapack_int) ldu;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_zggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        alpha,
        beta,
        (lapack_complex_double*) U, &ldu_,
        (lapack_complex_double*) V, &ldv_,
        (lapack_complex_double*) Q, &ldq_,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( (2*n) );
    std::vector< lapack_int > iwork( (n) );

    LAPACK_zggsvd3(
        &jobu_, &jobv_, &jobq_, &m_, &n_, &p_, &k_, &l_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        alpha,
        beta,
        (lapack_complex_double*) U, &ldu_,
        (lapack_complex_double*) V, &ldv_,
        (lapack_complex_double*) Q, &ldq_,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0],
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *k = k_;
    *l = l_;
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.6
