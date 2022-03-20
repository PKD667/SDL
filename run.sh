if [ -z "$var" ]
then
    g++ main.cpp -g -pedantic -o bin/build -lSDL2 && bin/build
else
    g++ $1 -g -pedantic -o bin/test -lSDL2 && bin/test;
fi

