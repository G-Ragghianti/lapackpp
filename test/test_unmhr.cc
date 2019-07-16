#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"

#include <vector>

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_unmhr_work( Params& params, bool run )
{
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    lapack::Side side = params.side();
    lapack::Op trans = params.trans();
    int64_t m = params.dim.m();
    int64_t n = params.dim.n();
    int64_t align = params.align();
    params.matrix.mark();

    // mark non-standard output values
    params.ref_time();
    // params.ref_gflops();
    // params.gflops();

    if (! run)
        return;

    // ---------- setup
    // C is m-by-n
    // if left,  A is m-by-m (r-by-r)
    // if right, A is n-by-n (r-by-r)
    int64_t r = ( side == lapack::Side::Left ? m : n );
    int64_t lda = roundup( blas::max( 1, r ), align );
    int64_t ldc = roundup( blas::max( 1, m ), align );
    size_t size_A = (size_t) ( lda * r );
    size_t size_tau = (size_t) ( r - 1 );
    size_t size_C = (size_t) ( ldc * n );

    // r >= ihi >= ilo >= 1
    int64_t ilo = 1;
    int64_t ihi = r;

    std::vector< scalar_t > A( size_A );
    std::vector< scalar_t > tau( size_tau );
    std::vector< scalar_t > C_tst( size_C );
    std::vector< scalar_t > C_ref( size_C );

    lapack::generate_matrix( params.matrix, r, r, &A[0], lda );
    int64_t idist = 1;
    int64_t iseed[4] = { 0, 1, 2, 3 };
    lapack::larnv( idist, iseed, tau.size(), &tau[0] );
    lapack::larnv( idist, iseed, C_tst.size(), &C_tst[0] );

    // reduce A to Hessenberg form
    int64_t info_hrd = lapack::gehrd( r, ilo, ihi, &A[0], lda, &tau[0] );
    if (info_hrd != 0) {
        fprintf( stderr, "lapack::gehrd returned error %lld\n", (lld) info_hrd );
    }

    C_ref = C_tst;

    // ---------- run test
    libtest::flush_cache( params.cache() );
    double time = libtest::get_wtime();
    int64_t info_tst = lapack::unmhr( side, trans, m, n, ilo, ihi, &A[0], lda, &tau[0], &C_tst[0], ldc );
    time = libtest::get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::unmhr returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    // double gflop = lapack::Gflop< scalar_t >::unmhr( side, trans, m, n, ilo, ihi );
    // params.gflops() = gflop / time;

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache() );
        time = libtest::get_wtime();
        int64_t info_ref = LAPACKE_unmhr( side2char(side), op2char(trans), m, n, ilo, ihi, &A[0], lda, &tau[0], &C_ref[0], ldc );
        time = libtest::get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_unmhr returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        // params.ref_gflops() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( C_tst, C_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_unmhr( Params& params, bool run )
{
    switch (params.datatype()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_unmhr_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_unmhr_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_unmhr_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_unmhr_work< std::complex<double> >( params, run );
            break;
    }
}
