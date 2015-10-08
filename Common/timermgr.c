/* This application was initially developed as a Final Project by
 *     Vicent Ferrer Guasch (vicent.ferrerguasch@aalto.fi)
 * under the supervision of,
 *     Jukka Manner (jukka.manner@aalto.fi)
 *     Jose Costa-Requena (jose.costa@aalto.fi)
 * in AALTO University and partially funded by EIT ICT labs.
 */

/**
 * @file   timermgr.c
 * @Author Vicent Ferrer
 * @date   Octover, 2015
 * @brief
 */

#include "timermgr.h"
#include <glib.h>


/**
 * @typedef Internal timer manager structure*/
typedef struct{
    struct event_base *evbase;
    GHashTable         *timers;
}TimerMgr_t;

/**
 * @typedef Internal timer structure*/
typedef struct{
    struct event   *ev;
    struct timeval tv;
    TimerMgr       mgr;
    guint32        max_rtx;
    guint32        rtx;
    Timer_cb       cb_to;
    Timer_cb       cb_maxTo;
    Timer_cb       cb_free;
    gpointer       cb_args;
}Timer_t;



/**
 * @brief  Starts a new timer
 * @param [in]  t Timer handler
 *
 * Private function to be called when the timer is removed
 */
static void free_timer(Timer_t *t){
    if(t->cb_free){
        t->cb_free((Timer)t, t->cb_args);
    }
}


/**
 * @brief  Timer callback
 * @param [in] sock   Not Used
 * @param [in] which  Not Used
 * @param [in] arg    User Data
 *
 * Private callback function. It calls the appropiate callback.
 */
static void timer_cb(int sock, short which, void *arg){
    Timer_t * t = (Timer_t*)arg;

    if(t->rtx == t->max_rtx){
        /* Max Retransmission reached*/
        if(t->cb_maxTo){
            t->cb_maxTo((Timer)t, t->cb_args);
        }
        tm_stop_timer(t);
    }else{
        /* Process CB*/
        t->cb_to((Timer)t, t->cb_args);
        /*Last timer and cb_maxTo is NULL*/
        if(!t->cb_maxTo && (t->rtx + 1) == t->max_rtx){
            tm_stop_timer(t);
        }
    }
    t->rtx++;
}

TimerMgr init_timerMgr(struct event_base *ev_base){
    TimerMgr_t *self = g_new0(TimerMgr_t, 1);

    if(!ev_base){
        return NULL;
    }
    self->evbase = ev_base;
    self->timers = g_hash_table_new_full(g_direct_hash,
                                         g_direct_equal,
                                         NULL,
                                         (GDestroyNotify)free_timer);
}

void free_timerMgr(TimerMgr h){
    TimerMgr_t *self = (TimerMgr_t*) h;

    g_hash_table_destroy(self->timers);
}


Timer tm_add_timer(TimerMgr h, const struct timeval *tv, const uint32_t max_rtx,
                   Timer_cb cb_to, Timer_cb cb_maxTo, Timer_cb cb_free,
                   void* cb_args){
    Timer_t *t;
    TimerMgr_t *self = (TimerMgr_t*) h;
    if(!tv || !cb_to){
        return NULL;
    }
    if(tv->tv_sec == 0 && tv->tv_usec == 0){
        return NULL;
    }
    if(max_rtx < 1){
        return NULL;
    }

    t = g_new0(Timer_t, 1);

    t->tv.tv_sec = tv->tv_sec;
    t->tv.tv_usec = tv->tv_usec;
    t->mgr = self;
    t->max_rtx = max_rtx;
    t->cb_to = cb_to;
    t->cb_maxTo = cb_maxTo;
    t->cb_free = cb_free;
    t->cb_args = cb_args;

    t->ev = event_new(self->evbase, -1, EV_PERSIST , timer_cb, t);
    evtimer_add(t->ev, &(t->tv));

    g_hash_table_add(self->timers, t);
    return t;
}

void tm_stop_timer(Timer timer){

    Timer_t *t = (Timer_t*)timer;
    TimerMgr_t *tm = t->mgr;

    evtimer_del(t->ev);

    g_hash_table_remove(tm->timers, t);

    g_free(t);
}