#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_lantr_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    lapack::Norm norm = params.norm();
    lapack::Uplo uplo = params.uplo();
    lapack::Diag diag = params.diag();
    int64_t m = params.dim.m();
    int64_t n = params.dim.n();
    int64_t align = params.align();
    int64_t verbose = params.verbose();
    params.matrix.mark();

    // mark non-standard output values
    params.ref_time();
    //params.ref_gflops();
    //params.gflops();
    params.msg();

    if (! run)
        return;

    // skip invalid sizes
    if ((uplo == blas::Uplo::Lower && m < n) ||
        (uplo == blas::Uplo::Upper && m > n))
    {
        params.msg() = "skipping: requires m >= n (lower) or m <= n (upper)";
        return;
    }

    // ---------- setup
    int64_t lda = roundup( blas::max( m, 1 ), align );
    size_t size_A = (size_t) lda * n;

    std::vector< scalar_t > A( size_A );

    lapack::generate_matrix( params.matrix, m, n, &A[0], lda );

    if (verbose >= 1) {
        printf( "\n"
                "A m=%5lld, n=%5lld, lda=%5lld\n",
                (lld) m, (lld) n, (lld) lda );
    }
    if (verbose >= 2) {
        printf( "A = " ); print_matrix( m, n, &A[0], lda );
    }

    // ---------- run test
    testsweeper::flush_cache( params.cache() );
    double time = testsweeper::get_wtime();
    real_t norm_tst = lapack::lantr( norm, uplo, diag, m, n, &A[0], lda );
    time = testsweeper::get_wtime() - time;

    params.time() = time;
    //double gflop = lapack::Gflop< scalar_t >::lantr( norm, diag, m, n );
    //params.gflops() = gflop / time;

    if (verbose >= 1) {
        printf( "norm_tst = %.8e\n", norm_tst );
    }

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        testsweeper::flush_cache( params.cache() );
        time = testsweeper::get_wtime();
        real_t norm_ref = LAPACKE_lantr( norm2char(norm), uplo2char(uplo), diag2char(diag), m, n, &A[0], lda );
        time = testsweeper::get_wtime() - time;

        params.ref_time() = time;
        //params.ref_gflops() = gflop / time;

        if (verbose >= 1) {
            printf( "norm_ref = %.8e\n", norm_ref );
        }

        // ---------- check error compared to reference
        real_t tol = 3 * std::numeric_limits< real_t >::epsilon();
        real_t normalize = 1;
        if (norm == lapack::Norm::Max && ! blas::is_complex< scalar_t >::value) {
            // max-norm depends on only one element, so in real there should be
            // zero error, but in complex there's error in abs().
            tol = 0;
        }
        else if (norm == lapack::Norm::One)
            normalize = sqrt( real_t(m) );
        else if (norm == lapack::Norm::Inf)
            normalize = sqrt( real_t(n) );
        else if (norm == lapack::Norm::Fro)
            normalize = sqrt( real_t(m)*n );
        real_t error = std::abs( norm_tst - norm_ref ) / normalize;
        if (norm_ref != 0)
            error /= norm_ref;
        params.error() = error;
        params.okay() = (error <= tol);
    }
}

// -----------------------------------------------------------------------------
void test_lantr( Params& params, bool run )
{
    switch (params.datatype()) {
        case testsweeper::DataType::Integer:
            throw std::exception();
            break;

        case testsweeper::DataType::Single:
            test_lantr_work< float >( params, run );
            break;

        case testsweeper::DataType::Double:
            test_lantr_work< double >( params, run );
            break;

        case testsweeper::DataType::SingleComplex:
            test_lantr_work< std::complex<float> >( params, run );
            break;

        case testsweeper::DataType::DoubleComplex:
            test_lantr_work< std::complex<double> >( params, run );
            break;
    }
}
