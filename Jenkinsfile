pipeline {
agent none
triggers { cron ('H H(0-2) * * *') }
stages {
stage ('Build'){
parallel {
stage ('Build - Caffeine'){
  agent { node ('caffeine.icl.utk.edu')}
  steps {
    sh '''
      #!/bin/sh +x
      echo "LAPACK++ Building..."
      hostname && pwd

      source /home/jmfinney/spack/share/spack/setup-env.sh
      spack load cmake
      spack load gcc@6.4.0
      spack load intel-mkl
      spack load intel-mpi

      rm -rf *

      hg clone http://bitbucket.org/icl/testsweeper && cd testsweeper
      make config
      sed -i '/CXXFLAGS/s/$/ -DNO_COLOR/' make.inc
      make
      cd ..

      hg clone http://bitbucket.org/icl/blaspp && cd blaspp
      make config && make -j4
      cd ..

      hg clone http://bitbucket.org/icl/lapackpp && cd lapackpp
      make config CXXFLAGS="-Werror"
      make -j4
      ldd test/tester | tee ldd_output.txt
    '''
  } // steps
  post {
    unstable {
      slackSend channel: '#slate_ci',
        color: 'warning',
        message: "Caffeine build - ${currentBuild.fullDisplayName} unstable: (<${env.BUILD_URL}|Open>)"
    }
    failure {
      slackSend channel: '#slate_ci',
        color: 'danger',
        message: "Caffeine build - ${currentBuild.fullDisplayName} failed: (<${env.BUILD_URL}|Open>)"
      mail to: 'slate-dev@icl.utk.edu',
        subject: "${currentBuild.fullDisplayName} Build Failure",
        body: "Caffeine build - See more at ${env.BUILD_URL}"
    }
  } //post
} // build - caffeine
stage ('Build - Lips'){
  agent { node ('lips.icl.utk.edu')}
  steps {
    sh '''
      #!/bin/sh +x
      echo "LAPACK++ Building..."
      hostname && pwd

      source /home/jmfinney/spack/share/spack/setup-env.sh
      spack load cmake
      spack load gcc@6.4.0
      spack load cuda
      spack load intel-mkl
      spack load intel-mpi

      rm -rf *

      hg clone http://bitbucket.org/icl/testsweeper && cd testsweeper
      make config
      sed -i '/CXXFLAGS/s/$/ -DNO_COLOR/' make.inc
      make
      cd ..

      hg clone http://bitbucket.org/icl/blaspp && cd blaspp
      make config && make -j4
      cd ..

      hg clone http://bitbucket.org/icl/lapackpp && cd lapackpp
      make config CXXFLAGS="-Werror"
      make -j4
      ldd test/tester | tee ldd_output.txt
    '''
  } // steps
  post {
    unstable {
      slackSend channel: '#slate_ci',
        color: 'warning',
        message: "Lips build - ${currentBuild.fullDisplayName} unstable: (<${env.BUILD_URL}|Open>)"
    }
    failure { 
      slackSend channel: '#slate_ci',
        color: 'danger', 
        message: "Lips build - ${currentBuild.fullDisplayName} failed: (<${env.BUILD_URL}|Open>)"
      mail to: 'slate-dev@icl.utk.edu',
        subject: "${currentBuild.fullDisplayName} Build Failure",
        body: "Lips build - See more at ${env.BUILD_URL}"
    }         
  } //post 
} // build - lips
} // parallel
} // stage (build)
stage ('Test') {
parallel {
stage ('Test - Caffeine') {
  agent { node ('caffeine.icl.utk.edu')}
  steps {
    sh '''
      #!/bin/sh +x
      echo "LAPACK++ Building..."
      hostname && pwd

      source /home/jmfinney/spack/share/spack/setup-env.sh
      spack load gcc@6.4.0
      spack load intel-mkl
      spack load intel-mpi

      cd lapackpp/test
      ./run_tests.py --ref n --xml report.xml
    '''
    junit 'lapackpp/test/*.xml'
  } // steps
  post {
    unstable {
      slackSend channel: '#slate_ci',
        color: 'warning',
        message: "Caffeine test - ${currentBuild.fullDisplayName} unstable: (<${env.BUILD_URL}|Open>)"
    }
    failure { 
      slackSend channel: '#slate_ci',
        color: 'danger', 
        message: "Caffeine test - ${currentBuild.fullDisplayName} failed: (<${env.BUILD_URL}|Open>)"
      mail to: 'slate-dev@icl.utk.edu',
        subject: "${currentBuild.fullDisplayName} Test Failure",
        body: "Caffeine Test failure - See more at ${env.BUILD_URL}"
    }         
  } //post 
} // stage test caffeine
stage ('Test - Lips') {
  agent { node ('lips.icl.utk.edu')}
  steps {
    sh '''
      #!/bin/sh +x
      echo "LAPACK++ Building..."
      hostname && pwd

      source /home/jmfinney/spack/share/spack/setup-env.sh
      spack load gcc@6.4.0
      spack load cuda
      spack load intel-mkl
      spack load intel-mpi

      cd lapackpp/test
      ./run_tests.py --ref n --xml report.xml
    '''
    junit 'lapackpp/test/*.xml'
  } // steps
  post {
    unstable {
      slackSend channel: '#slate_ci',
        color: 'warning',
        message: "Lips test - ${currentBuild.fullDisplayName} unstable: (<${env.BUILD_URL}|Open>)"
    }
    failure { 
      slackSend channel: '#slate_ci',
        color: 'danger',
        message: "Lips test - ${currentBuild.fullDisplayName} failed: (<${env.BUILD_URL}|Open>)"
      mail to: 'slate-dev@icl.utk.edu',
        subject: "${currentBuild.fullDisplayName} Test Failure",
        body: "Lips Test failure - See more at ${env.BUILD_URL}"
    }
  } //post 
} // stage test lips
} // parallel
} // stage (test)
} // stages
} // pipeline