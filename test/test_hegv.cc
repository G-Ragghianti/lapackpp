#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_hegv_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    int64_t itype = params.itype();
    lapack::Job jobz = params.jobz();
    lapack::Uplo uplo = params.uplo();
    int64_t n = params.dim.n();
    int64_t align = params.align();
    int64_t verbose = params.verbose();
    params.matrix.mark();
    params.matrixB.mark();

    // mark non-standard output values
    params.ref_time();
    // params.ref_gflops();
    // params.gflops();

    if (! run) {
        params.matrixB.kind.set_default( "rand_dominant" );
        return;
    }

    // ---------- setup
    int64_t lda = roundup( blas::max( 1, n ), align );
    int64_t ldb = roundup( blas::max( 1, n ), align );
    size_t size_A = (size_t) lda * n;
    size_t size_B = (size_t) ldb * n;
    size_t size_W = (size_t) (n);

    std::vector< scalar_t > A_tst( size_A );
    std::vector< scalar_t > A_ref( size_A );
    std::vector< scalar_t > B_tst( size_B );
    std::vector< scalar_t > B_ref( size_B );
    std::vector< real_t > W_tst( size_W );
    std::vector< real_t > W_ref( size_W );

    // todo: how to specify A and B separately?
    lapack::generate_matrix( params.matrix,  n, n, &A_tst[0], lda );
    lapack::generate_matrix( params.matrixB, n, n, &B_tst[0], lda );
    A_ref = A_tst;
    B_ref = B_tst;

    if (verbose >= 1) {
        printf( "\n" );
        printf( "A n=%5lld, lda=%5lld\n", (lld) n, (lld) lda );
        printf( "B n=%5lld, ldb=%5lld\n", (lld) n, (lld) ldb );
    }
    if (verbose >= 2) {
        printf( "A = " ); print_matrix( n, n, &A_tst[0], lda );
        printf( "B = " ); print_matrix( n, n, &B_tst[0], lda );
    }

    // ---------- run test
    libtest::flush_cache( params.cache() );
    double time = libtest::get_wtime();
    int64_t info_tst = lapack::hegv( itype, jobz, uplo, n, &A_tst[0], lda, &B_tst[0], ldb, &W_tst[0] );
    time = libtest::get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::hegv returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    // double gflop = lapack::Gflop< scalar_t >::hegv( itype, jobz, n );
    // params.gflops() = gflop / time;

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache() );
        time = libtest::get_wtime();
        int64_t info_ref = LAPACKE_hegv( itype, job2char(jobz), uplo2char(uplo), n, &A_ref[0], lda, &B_ref[0], ldb, &W_ref[0] );
        time = libtest::get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_hegv returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        // params.ref_gflops() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( A_tst, A_ref );
        error += abs_error( B_tst, B_ref );
        error += abs_error( W_tst, W_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_hegv( Params& params, bool run )
{
    switch (params.datatype()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_hegv_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_hegv_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_hegv_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_hegv_work< std::complex<double> >( params, run );
            break;
    }
}
