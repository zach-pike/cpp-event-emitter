#include "../include/eventemitter.hpp"
#include <stdlib.h>
#include <stdio.h>

struct Testing {
    int myint;
    float myfloat;
};

int main() {
    // initiate the class with the struct used for emitted data
    EventEmitter<Testing> emitter;    


    emitter.on("event", [](Testing data) {
        printf("Cool! this will be printed every time %d\n", data.myint);
    });

    emitter.once("event", [](Testing data) {
        printf("This will be printed only once! %f\n", data.myfloat);
    });


    Testing data = {
        10,
        4.20f
    };

    //emit to the "event" event listeners
    emitter.emit("event", data);

    //increment vaue for fun
    data.myint++;

    emitter.emit("event", data);
    emitter.emit("event", data);
    emitter.emit("event", data);
}