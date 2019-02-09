#!/bin/bash
alias c="./c.sh"

args=("$@")
cmd=${args[0]}

compile() {
    gcc -o ./target/main main.c ./src/io.c ./src/exec.c ./src/strings.c ./src/pipe.c
}

clean() {
    rm ./target/main
}

run() {
    compile
    ./target/main
    clean
}

if [ "$cmd" = "compile" ]
then
    compile
elif [ "$cmd" = "clean" ]
then
    clean
elif [ "$cmd" = "run" ]
then
    run
else
    echo "Command not supported"
fi


