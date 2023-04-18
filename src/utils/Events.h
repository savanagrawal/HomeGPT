/**
 * @file Events.h
 * @author Chinmay Nagrale
 * @version 0.1
 * 
 * Storing all event codes and allowing interfacing with the eventpp library.
 */
#ifndef EVENTS_H
#define EVENTS_H

#include "eventpp/eventdispatcher.h"




class Events {
    public:
        enum EVENT_CODES {
            CLAP_DETECTED,
            CLAP_DETECTED_THREAD,
            DATASET_CREATOR_COMPLETE,
            DATASET_CREATOR_ERROR,
            DATASET_TRAINER_COMPLETE,
            DATASET_TRAINER_ERROR,
            INTRUDER_THREAD_KILL
        };

        eventpp::EventDispatcher<EVENT_CODES, void ()>* getDispatcher() {
             return &dispatcher;
        }
        
        void appendListener(EVENT_CODES ev, std::function<void()> cb){
            dispatcher.appendListener(ev, cb);
        }
        
        void dispatch(EVENT_CODES ev) {
            dispatcher.dispatch(ev);
        }

    private:
        eventpp::EventDispatcher<EVENT_CODES, void ()> dispatcher;
};

#endif
