#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_pptri_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    lapack::Uplo uplo = params.uplo();
    int64_t n = params.dim.n();

    // mark non-standard output values
    params.ref_time();
    //params.ref_gflops();
    //params.gflops();

    if (! run)
        return;

    // ---------- setup
    size_t size_AP = (size_t) (n*(n+1)/2);

    std::vector< scalar_t > AP_tst( size_AP );
    std::vector< scalar_t > AP_ref( size_AP );

    int64_t idist = 1;
    int64_t iseed[4] = { 0, 1, 2, 3 };
    lapack::larnv( idist, iseed, AP_tst.size(), &AP_tst[0] );

    // diagonally dominant -> positive definite
    if (uplo == lapack::Uplo::Upper) {
        for (int64_t i = 0; i < n; ++i) {
            AP_tst[ i + 0.5*(i+1)*i ] += n;
        }
    }
    else { // lower
        for (int64_t i = 0; i < n; ++i) {
            AP_tst[ i + n*i - 0.5*i*(i+1) ] += n;
        }
    }

    // factor A into LL^T
    int64_t info = lapack::pptrf( uplo, n, &AP_tst[0] );
    if (info != 0) {
        fprintf( stderr, "lapack::pptrf returned error %lld\n", (lld) info );
    }

    AP_ref = AP_tst;

    // ---------- run test
    testsweeper::flush_cache( params.cache() );
    double time = testsweeper::get_wtime();
    int64_t info_tst = lapack::pptri( uplo, n, &AP_tst[0] );
    time = testsweeper::get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::pptri returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    //double gflop = lapack::Gflop< scalar_t >::pptri( n );
    //params.gflops() = gflop / time;

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        testsweeper::flush_cache( params.cache() );
        time = testsweeper::get_wtime();
        int64_t info_ref = LAPACKE_pptri( uplo2char(uplo), n, &AP_ref[0] );
        time = testsweeper::get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_pptri returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        //params.ref_gflops() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( AP_tst, AP_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_pptri( Params& params, bool run )
{
    switch (params.datatype()) {
        case testsweeper::DataType::Integer:
            throw std::exception();
            break;

        case testsweeper::DataType::Single:
            test_pptri_work< float >( params, run );
            break;

        case testsweeper::DataType::Double:
            test_pptri_work< double >( params, run );
            break;

        case testsweeper::DataType::SingleComplex:
            test_pptri_work< std::complex<float> >( params, run );
            break;

        case testsweeper::DataType::DoubleComplex:
            test_pptri_work< std::complex<double> >( params, run );
            break;
    }
}
