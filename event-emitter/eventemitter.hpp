#include <bits/stdc++.h>

using namespace std;

template <typename args>
struct CallBack {
    function<void(args)> cb;

    bool once;
    int callTimes;

};

//EventEmitter Class
template <typename T>
class EventEmitter {
    private:
        unordered_map<string, vector<CallBack<T>>> callbacks;

    public:
        //When event is emmited on registered emitter, run the callback with the data emitted
        void on(string evnt, function<void(T)> cb);

        //Run callback only once after registered no matter how many times listener is emitted to
        void once(string evnt, function<void(T)> cb);

        //Emit event with data
        void emit(string evnt, T data);
};

template <typename T>
void EventEmitter<T>::on(string evnt, function<void(T)> cb) {
    EventEmitter::callbacks[evnt].push_back((CallBack<T>) {
        cb,
        false,
        0
    });
}


template <typename T>
void EventEmitter<T>::once(string evnt, function<void(T)> cb) {
    EventEmitter::callbacks[evnt].push_back((CallBack<T>) {
        cb,
        true,
        0
    });
}

template <typename T>
void EventEmitter<T>::emit(string evnt, T data) {
    if (EventEmitter::callbacks.find(evnt) == EventEmitter::callbacks.end()) return;

    //make a refrencee because im sick as shit of typing EventEmitter::callbacks, also used auto because im a lazy sack of shit
    vector<CallBack<T>>& list = EventEmitter<T>::callbacks[evnt];

    //loop thru all the callbacks that are registered
    for (int i=0; i < list.size(); i++) {

        //if its a once listener and its already been run, remove it from the list of callbacks
        if (list[i].callTimes > 0 && list[i].once) {
            list.erase(list.begin() + i);
        } else {

            //if not, run the callback
            list[i].cb(data);
            list[i].callTimes++;
        }
    }
}