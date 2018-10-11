#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION >= 30400  // >= 3.4.0

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup tpqrt
void tprfb(
    lapack::Side side, lapack::Op trans, lapack::Direct direct, lapack::StoreV storev,
    int64_t m, int64_t n, int64_t k, int64_t l,
    float const* V, int64_t ldv,
    float const* T, int64_t ldt,
    float* A, int64_t lda,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldt) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    char direct_ = direct2char( direct );
    char storev_ = storev2char( storev );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldt_ = (lapack_int) ldt;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldwork_ = (side == Side::Left ? k : m);

    // allocate workspace
    int64_t lwork = (side == Side::Left ? k*n : m*k);
    std::vector< float > work( lwork );

    LAPACK_stprfb(
        &side_, &trans_, &direct_, &storev_, &m_, &n_, &k_, &l_,
        V, &ldv_,
        T, &ldt_,
        A, &lda_,
        B, &ldb_,
        &work[0], &ldwork_ );
}

// -----------------------------------------------------------------------------
/// @ingroup tpqrt
void tprfb(
    lapack::Side side, lapack::Op trans, lapack::Direct direct, lapack::StoreV storev,
    int64_t m, int64_t n, int64_t k, int64_t l,
    double const* V, int64_t ldv,
    double const* T, int64_t ldt,
    double* A, int64_t lda,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldt) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    char direct_ = direct2char( direct );
    char storev_ = storev2char( storev );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldt_ = (lapack_int) ldt;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldwork_ = (side == Side::Left ? k : m);

    // allocate workspace
    int64_t lwork = (side == Side::Left ? k*n : m*k);
    std::vector< double > work( lwork );

    LAPACK_dtprfb(
        &side_, &trans_, &direct_, &storev_, &m_, &n_, &k_, &l_,
        V, &ldv_,
        T, &ldt_,
        A, &lda_,
        B, &ldb_,
        &work[0], &ldwork_ );
}

// -----------------------------------------------------------------------------
/// @ingroup tpqrt
void tprfb(
    lapack::Side side, lapack::Op trans, lapack::Direct direct, lapack::StoreV storev,
    int64_t m, int64_t n, int64_t k, int64_t l,
    std::complex<float> const* V, int64_t ldv,
    std::complex<float> const* T, int64_t ldt,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldt) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    char direct_ = direct2char( direct );
    char storev_ = storev2char( storev );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldt_ = (lapack_int) ldt;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldwork_ = (side == Side::Left ? k : m);

    // allocate workspace
    int64_t lwork = (side == Side::Left ? k*n : m*k);
    std::vector< std::complex<float> > work( lwork );

    LAPACK_ctprfb(
        &side_, &trans_, &direct_, &storev_, &m_, &n_, &k_, &l_,
        (lapack_complex_float*) V, &ldv_,
        (lapack_complex_float*) T, &ldt_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) &work[0], &ldwork_ );
}

// -----------------------------------------------------------------------------
/// Applies a complex "triangular-pentagonal" block reflector H or its
/// conjugate transpose $H^H$ to a complex matrix C, which is composed of two
/// blocks A and B, either from the left or right.
///
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @since LAPACK 3.4.0
///
/// @param[in] side
///     - lapack::Side::Left:  apply $H$ or $H^H$ from the Left
///     - lapack::Side::Right: apply $H$ or $H^H$ from the Right
///
/// @param[in] trans
///     - lapack::Op::NoTrans:   apply $H    (No transpose)
///     - lapack::Op::ConjTrans: apply $H^H$ (Conjugate transpose)
///
/// @param[in] direct
///     Indicates how H is formed from a product of elementary
///     reflectors
///     - lapack::Direct::Forward:  $H = H(1) H(2) . . . H(k)$ (Forward)
///     - lapack::Direct::Backward: $H = H(k) . . . H(2) H(1)$ (Backward)
///
/// @param[in] storev
///     Indicates how the vectors which define the elementary
///     reflectors are stored:
///     - lapack::StoreV::Columnwise: Columns
///     - lapack::StoreV::Rowwise: Rows
///
/// @param[in] m
///     The number of rows of the matrix B.
///     m >= 0.
///
/// @param[in] n
///     The number of columns of the matrix B.
///     n >= 0.
///
/// @param[in] k
///     The order of the matrix T, i.e. the number of elementary
///     reflectors whose product defines the block reflector.
///     k >= 0.
///
/// @param[in] l
///     The order of the trapezoidal part of V.
///     k >= l >= 0. See Further Details.
///
/// @param[in] V
///     If storev, side are:
///     - Columnwise, Left:  the m-by-k matrix V, stored in an ldv-by-k array.
///     - Columnwise, Right: the n-by-k matrix V, stored in an ldv-by-k array.
///     - Rowwise,    Left:  the k-by-m matrix V, stored in an ldv-by-m array.
///     - Rowwise,    Right: the k-by-n matrix V, stored in an ldv-by-n array.
///     The pentagonal matrix V, which contains the elementary reflectors
///     H(1), H(2), ..., H(k). See Further Details.
///
/// @param[in] ldv
///     The leading dimension of the array V.
///     If storev = Columnwise and side = Left,  ldv >= max(1,m);
///     if storev = Columnwise and side = Right, ldv >= max(1,n);
///     if storev = Rowwise, ldv >= k.
///
/// @param[in] T
///     The k-by-k matrix T, stored in an ldt-by-k array.
///     The triangular k-by-k matrix T in the representation of the
///     block reflector.
///
/// @param[in] ldt
///     The leading dimension of the array T.
///     ldt >= k.
///
/// @param[in,out] A
///     If side = Left,  the k-by-n matrix A, stored in an lda-by-n array.
///     If side = Right, the n-by-k matrix A, stored in an lda-by-k array.
///     On exit, A is overwritten by the corresponding block of
///     H*C or H^H*C or C*H or C*H^H. See Further Details.
///
/// @param[in] lda
///     The leading dimension of the array A.
///     If side = Left,  lda >= max(1,k);
///     If side = Right, lda >= max(1,m).
///
/// @param[in,out] B
///     The m-by-n matrix B, stored in an ldb-by-n array.
///     On exit, B is overwritten by the corresponding block of
///     $HC$, $H^H C$, $CH$, or $CH^H$. See Further Details.
///
/// @param[in] ldb
///     The leading dimension of the array B.
///     ldb >= max(1,m).
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// The matrix C is a composite matrix formed from blocks A and B.
/// The block B is of size m-by-n; if side = Right, A is of size m-by-k,
/// and if side = Left, A is of size k-by-n.
///
/// If side = Right and direct = Forward,
///     $C = [A B]$.
///
/// If side = Left and direct = Forward,
///     $C = \left[ \begin{array}{c}
///         A
///         B
///     \end{array} \right].
///
/// If side = Right and direct = Backward,
///     $C = [B A]$.
///
/// If side = Left and direct = Backward,
///     $C = \left[ \begin{array}{c}
///         B
///         A
///     \end{array} \right].
///
/// The pentagonal matrix V is composed of a rectangular block V1 and a
/// trapezoidal block V2.  The size of the trapezoidal block is determined by
/// the parameter l, where 0 <= l <= k.  If l=k, the V2 block of V is triangular;
/// if l=0, there is no trapezoidal block, thus V = V1 is rectangular.
///
/// If direct = Forward and storev = Columnwise:
///     $V = \left[ \begin{array}{c}
///         V1
///         V2
///     \end{array} \right].
///     - V2 is upper trapezoidal (first l rows of k-by-k upper triangular)
///
/// If direct = Forward and storev = Rowwise:
///     $V = [V1 V2]$
///     - V2 is lower trapezoidal (first l columns of k-by-k lower triangular)
///
/// If direct = Backward and storev = Columnwise:
///     $V = \left[ \begin{array}{c}
///         V2
///         V1
///     \end{array} \right].
///     - V2 is lower trapezoidal (last l rows of k-by-k lower triangular)
///
/// If direct = Backwar$d and storev = Rowwise:
///     $V = [V2 V1]
///     - V2 is upper trapezoidal (last l columns of k-by-k upper triangular)
///
/// If storev = Columnwise and side = Left, V is m-by-k with V2 l-by-k.
///
/// If storev = Columnwise and side = Right, V is n-by-k with V2 l-by-k.
///
/// If storev = Rowwise and side = Left, V is k-by-m with V2 k-by-l.
///
/// If storev = Rowwise and side = Right, V is k-by-n with V2 k-by-l.
///
/// @ingroup tpqrt
void tprfb(
    lapack::Side side, lapack::Op trans, lapack::Direct direct, lapack::StoreV storev, int64_t m, int64_t n, int64_t k, int64_t l,
    std::complex<double> const* V, int64_t ldv,
    std::complex<double> const* T, int64_t ldt,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldv) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldt) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    char direct_ = direct2char( direct );
    char storev_ = storev2char( storev );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int ldv_ = (lapack_int) ldv;
    lapack_int ldt_ = (lapack_int) ldt;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldwork_ = (side == Side::Left ? k : m);

    // allocate workspace
    int64_t lwork = (side == Side::Left ? k*n : m*k);
    std::vector< std::complex<double> > work( lwork );

    LAPACK_ztprfb(
        &side_, &trans_, &direct_, &storev_, &m_, &n_, &k_, &l_,
        (lapack_complex_double*) V, &ldv_,
        (lapack_complex_double*) T, &ldt_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) &work[0], &ldwork_ );
}

}  // namespace lapack

#endif  // LAPACK >= 3.4.0