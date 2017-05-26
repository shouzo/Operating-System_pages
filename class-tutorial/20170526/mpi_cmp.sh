mpicc $1 -o ~/mpi_out/${1}.out
read -p "press any key" -s -n 1 key

scp ~/mpi_out/${1}.out cuda02:~/mpi_out
read -p "press any key" -s -n 1 key

echo ""
read -p "type num of node:" node 
mpirun -f MPIhosts -np $node ~/mpi_out/${1}.out
