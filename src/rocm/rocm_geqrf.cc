// Copyright (c) 2017-2020, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack/defines.h"

#if defined(LAPACK_HAVE_ROCBLAS)

#include "lapack/device.hh"

#include <rocsolver.h>

//==============================================================================
namespace lapack {

//------------------------------------------------------------------------------
// Wrapper around rocSolver workspace query.
// dA is only for templating scalar_t; it isn't referenced.
template <typename scalar_t>
void geqrf_work_size_bytes(
    int64_t m, int64_t n,
    scalar_t* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue )
{
    *dev_work_size  = 0;
    *host_work_size = 0;
}

//------------------------------------------------------------------------------
// Intermediate wrappers around rocSolver to deal with precisions.
void rocsolver_geqrf(
    rocblas_handle solver, rocblas_int m, rocblas_int n,
    float* dA, rocblas_int ldda, float* dtau )
{
    rocsolver_sgeqrf(
        solver, m, n, dA, ldda, dtau );
}

//----------
void rocsolver_geqrf(
    rocblas_handle solver, rocblas_int m, rocblas_int n,
    double* dA, rocblas_int ldda, double* dtau )
{
    rocsolver_dgeqrf(
        solver, m, n, dA, ldda, dtau );
}

//----------
void rocsolver_geqrf(
    rocblas_handle solver, rocblas_int m, rocblas_int n,
    std::complex<float>* dA, rocblas_int ldda, std::complex<float>* dtau )
{
    rocsolver_cgeqrf(
        solver, m, n,
        (rocblas_float_complex*) dA, ldda,
        (rocblas_float_complex*) dtau );
}

//----------
void rocsolver_geqrf(
    rocblas_handle solver, rocblas_int m, rocblas_int n,
    std::complex<double>* dA, rocblas_int ldda, std::complex<double>* dtau )
{
    rocsolver_zgeqrf(
        solver, m, n,
        (rocblas_double_complex*) dA, ldda,
        (rocblas_double_complex*) dtau );
}

//------------------------------------------------------------------------------
// Wrapper around rocSolver.
// This is async. Once finished, the return info is in dev_info on the device.
// In rocSolver, the workspaces are ignored.
// In rocSolver, there is no info. todo: set it to 0?
template <typename scalar_t>
void geqrf(
    int64_t m, int64_t n,
    scalar_t* dA, int64_t ldda, scalar_t* dtau,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue )
{
    // todo: check for overflow
    auto solver = queue.handle();

    blas::set_device( queue.device() );

    rocsolver_geqrf( solver, m, n, dA, ldda, dtau );
    device_memset( dev_info, 0, 1, queue );
}

//------------------------------------------------------------------------------
// Explicit instantiations.
template
void geqrf_work_size_bytes(
    int64_t m, int64_t n,
    float* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void geqrf_work_size_bytes(
    int64_t m, int64_t n,
    double* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void geqrf_work_size_bytes(
    int64_t m, int64_t n,
    std::complex<float>* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

template
void geqrf_work_size_bytes(
    int64_t m, int64_t n,
    std::complex<double>* dA, int64_t ldda,
    size_t* dev_work_size, size_t* host_work_size,
    lapack::Queue& queue );

//--------------------
template
void geqrf(
    int64_t m, int64_t n,
    float* dA, int64_t ldda, float* dtau,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void geqrf(
    int64_t m, int64_t n,
    double* dA, int64_t ldda, double* dtau,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void geqrf(
    int64_t m, int64_t n,
    std::complex<float>* dA, int64_t ldda, std::complex<float>* dtau,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

template
void geqrf(
    int64_t m, int64_t n,
    std::complex<double>* dA, int64_t ldda, std::complex<double>* dtau,
    void*  dev_work, size_t  dev_work_size,
    void* host_work, size_t host_work_size,
    device_info_int* dev_info, lapack::Queue& queue );

} // namespace lapack

#endif // LAPACK_HAVE_ROCBLAS
