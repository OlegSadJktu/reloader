name=${1%.c}
gcc -Wall -g ./$1 -o ./build/$name.out -lm -lcurses 
# ./build.sh $1
shift
./build/$name.out $@
