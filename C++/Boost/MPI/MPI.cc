// mpic++ MPI.cc -lboost_mpi -o MPI
// mpirun -np ${n} MPI

#include <boost/mpi.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <iostream>

int main(int argc, char* argv[]){
    boost::mpi::environment env(argc,argv);
    boost::mpi::communicator world;

    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;

    std::cout << "hello from " << world.rank() << std::endl;

    return 0;
}