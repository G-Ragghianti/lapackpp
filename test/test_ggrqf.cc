#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_ggrqf_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    int64_t m = params.dim.m();
    int64_t p = params.dim.k();  // TODO Using k as a stand-in for p
    // int64_t p = params.p();
    int64_t n = params.dim.n();
    int64_t align = params.align();
    params.matrix.mark();
    params.matrixB.mark();

    // mark non-standard output values
    params.ref_time();
    // params.ref_gflops();
    // params.gflops();

    if (! run)
        return;

    // ---------- setup
    int64_t lda = roundup( blas::max( 1, m ), align );
    int64_t ldb = roundup( blas::max( 1, p ), align );
    size_t size_A = (size_t) lda * n;
    size_t size_taua = (size_t) (blas::min(m,n));
    size_t size_B = (size_t) ldb * n;
    size_t size_taub = (size_t) (blas::min(p,n));

    std::vector< scalar_t > A_tst( size_A );
    std::vector< scalar_t > A_ref( size_A );
    std::vector< scalar_t > taua_tst( size_taua );
    std::vector< scalar_t > taua_ref( size_taua );
    std::vector< scalar_t > B_tst( size_B );
    std::vector< scalar_t > B_ref( size_B );
    std::vector< scalar_t > taub_tst( size_taub );
    std::vector< scalar_t > taub_ref( size_taub );

    lapack::generate_matrix( params.matrix,  m, n, &A_tst[0], lda );
    lapack::generate_matrix( params.matrixB, p, n, &B_tst[0], ldb );
    A_ref = A_tst;
    B_ref = B_tst;

    // ---------- run test
    testsweeper::flush_cache( params.cache() );
    double time = testsweeper::get_wtime();
    int64_t info_tst = lapack::ggrqf( m, p, n, &A_tst[0], lda, &taua_tst[0], &B_tst[0], ldb, &taub_tst[0] );
    time = testsweeper::get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::ggrqf returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    // double gflop = lapack::Gflop< scalar_t >::ggrqf( m, n );
    // params.gflops() = gflop / time;

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        testsweeper::flush_cache( params.cache() );
        time = testsweeper::get_wtime();
        int64_t info_ref = LAPACKE_ggrqf( m, p, n, &A_ref[0], lda, &taua_ref[0], &B_ref[0], ldb, &taub_ref[0] );
        time = testsweeper::get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_ggrqf returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        // params.ref_gflops() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( A_tst, A_ref );
        error += abs_error( taua_tst, taua_ref );
        error += abs_error( B_tst, B_ref );
        error += abs_error( taub_tst, taub_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_ggrqf( Params& params, bool run )
{
    switch (params.datatype()) {
        case testsweeper::DataType::Integer:
            throw std::exception();
            break;

        case testsweeper::DataType::Single:
            test_ggrqf_work< float >( params, run );
            break;

        case testsweeper::DataType::Double:
            test_ggrqf_work< double >( params, run );
            break;

        case testsweeper::DataType::SingleComplex:
            test_ggrqf_work< std::complex<float> >( params, run );
            break;

        case testsweeper::DataType::DoubleComplex:
            test_ggrqf_work< std::complex<double> >( params, run );
            break;
    }
}
