pipeline {

agent none
options {
    // Required to clean before build
    skipDefaultCheckout( true )
}
triggers { pollSCM 'H/10 * * * *' }
stages {
    //======================================================================
    stage('Parallel Build') {
        matrix {
            axes {
                axis {
                    name 'maker'
                    values 'make', 'cmake'
                }
                axis {
                    name 'host'
                    values 'cpu_intel'
                }
            } // axes
            stages {
                stage('Build') {
                    agent { label "${host}" }

                    //----------------------------------------------------------
                    steps {
                        cleanWs()
                        checkout scm
                        sh '''
#!/bin/sh

set +e  # errors are not fatal (e.g., Spack sometimes has spurious failures)
set -x  # echo commands

date
hostname && pwd
export top=`pwd`

# Suppress echo (-x) output of commands executed with `run`. Useful for Spack.
# set +x, set -x are not echo'd.
run() {
    { set +x; } 2> /dev/null;
    $@;
    set -x
}

# Suppress echo (-x) output of `print` commands. https://superuser.com/a/1141026
# aliasing `echo` causes issues with spack_setup, so use `print` instead.
echo_and_restore() {
    builtin echo "$*"
    case "$save_flags" in
        (*x*)  set -x
    esac
}
alias print='{ save_flags="$-"; set +x; } 2> /dev/null; echo_and_restore'

print "======================================== load compiler"
date
run source /home/jenkins/spack_setup
run sload gcc@7.3.0
run spack compiler find
run sload intel-mkl
#run sload netlib-lapack

print "======================================== verify spack"
# Check what is loaded.
run spack find --loaded

which g++
g++ --version

which nvcc
nvcc --version

which hipcc
hipcc --version

print "MKLROOT ${MKLROOT}"

print "======================================== env"
env

print "======================================== setup build"
date
print "maker ${maker}"
export color=no
rm -rf ${top}/install
if [ "${maker}" = "make" ]; then
    make distclean
    make config CXXFLAGS="-Werror" prefix=${top}/install

    # Used to need LAPACKE from Netlib, but MKL has been fixed.
    ## Modify make.inc to add netlib LAPACKE for bug fixes.
    #export LAPACKDIR=`spack location -i netlib-lapack`/lib64
    #sed -i -e 's/LIBS *=/LIBS = -L${LAPACKDIR} -llapacke /' make.inc
fi
if [ "${maker}" = "cmake" ]; then
    run sload cmake
    which cmake
    cmake --version

    rm -rf blaspp
    git clone https://bitbucket.org/icl/blaspp
    mkdir blaspp/build && cd blaspp/build
    cmake -Dcolor=no -Dbuild_tests=no -DCMAKE_INSTALL_PREFIX=${top}/install ..
    make -j8 install
    cd ../..

    rm -rf build && mkdir build && cd build
    cmake -Dcolor=no -DCMAKE_CXX_FLAGS="-Werror" \
          -DCMAKE_PREFIX_PATH=${top}/install/lib64/blaspp \
          -DCMAKE_INSTALL_PREFIX=${top}/install ..
fi

print "======================================== build"
date
make -j8

print "======================================== install"
date
make -j8 install
ls -R ${top}/install

print "======================================== verify build"
print "Verify that tester linked with cublas or rocblas as intended."
date
ldd test/tester
if [ "${host}" = "gpu_nvidia" ]; then
    ldd test/tester | grep cublas || exit 1
fi
if [ "${host}" = "gpu_amd" ]; then
    ldd test/tester | grep rocblas || exit 1
fi

print "======================================== tests"
print "Run tests."
date
cd test
export OMP_NUM_THREADS=8
./run_tests.py --quick --xml ${top}/report-${maker}.xml

print "======================================== smoke tests"
print "Verify install with smoke tests."
date
cd ${top}/example

if [ "${maker}" = "make" ]; then
    export PKG_CONFIG_PATH=${top}/install/lib/pkgconfig
    make clean
fi
if [ "${maker}" = "cmake" ]; then
    rm -rf build && mkdir build && cd build
    cmake "-DCMAKE_PREFIX_PATH=${top}/install/lib64/blaspp;${top}/install/lib64/lapackpp" ..
fi

make
./example_potrf || exit 1

date
'''
                    } // steps

                    //----------------------------------------------------------
                    post {
                        failure {
                            mail to: 'slate-dev@icl.utk.edu',
                                subject: "${currentBuild.fullDisplayName} >> ${STAGE_NAME} >> ${maker} ${host} failed",
                                body: "See more at ${env.BUILD_URL}"
                        }
                        always {
                            junit '*.xml'
                        }
                    } // post

                } // stage(Build)
            } // stages
        } // matrix
    } // stage(Parallel Build)
} // stages

} // pipeline
