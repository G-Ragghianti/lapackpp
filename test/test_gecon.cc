#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_gecon_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    lapack::Norm norm = params.norm();
    int64_t n = params.dim.n();
    int64_t align = params.align();
    params.matrix.mark();

    // mark non-standard output values
    params.ref_time();
    //params.ref_gflops();
    //params.gflops();

    if (! run)
        return;

    // ---------- setup
    int64_t lda = roundup( blas::max( 1, n ), align );
    real_t anorm;
    real_t rcond_tst;
    real_t rcond_ref;
    size_t size_A = (size_t) lda * n;

    std::vector< scalar_t > A( size_A );

    lapack::generate_matrix( params.matrix, n, n, &A[0], lda );

    anorm = lapack::lange( norm, n, n, &A[0], lda );

    // ---------- run test
    libtest::flush_cache( params.cache() );
    double time = libtest::get_wtime();
    int64_t info_tst = lapack::gecon( norm, n, &A[0], lda, anorm, &rcond_tst );
    time = libtest::get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::gecon returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    //double gflop = lapack::Gflop< scalar_t >::gecon( norm, n );
    //params.gflops() = gflop / time;

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache() );
        time = libtest::get_wtime();
        int64_t info_ref = LAPACKE_gecon( norm2char(norm), n, &A[0], lda, anorm, &rcond_ref );
        time = libtest::get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_gecon returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        //params.ref_gflops() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += std::abs( rcond_tst - rcond_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_gecon( Params& params, bool run )
{
    switch (params.datatype()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_gecon_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_gecon_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_gecon_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_gecon_work< std::complex<double> >( params, run );
            break;
    }
}
