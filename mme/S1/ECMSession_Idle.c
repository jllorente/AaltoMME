/* This application was initially developed as a Final Project by
 *     Vicent Ferrer Guasch (vicent.ferrerguasch@aalto.fi)
 * under the supervision of,
 *     Jukka Manner (jukka.manner@aalto.fi)
 *     Jose Costa-Requena (jose.costa@aalto.fi)
 * in AALTO University and partially funded by EIT ICT labs.
 */

/**
 * @file   ECMSession_Idle.c
 * @Author Vicent Ferrer
 * @date   August, 2015
 * @brief  ECM Session Idle State
 *
 */

#include "ECMSession_Idle.h"
#include "MME.h"
#include "logmgr.h"
#include "MME_S1_priv.h"
#include "ECMSession_FSMConfig.h"
#include "ECMSession.h"
#include "ECMSession_priv.h"

static void ecm_processMsg(gpointer _ecm, S1AP_Message_t *s1msg, int r_sid){
    ECMSession_t *ecm = (ECMSession_t *)_ecm;

    if(s1msg->pdu->procedureCode == id_initialUEMessage &&
       s1msg->choice == initiating_message){
        log_msg(LOG_WARNING, 0, "Received id_initialUEMessage");
    }

}

static void disconnect(gpointer _ecm){
}

void linkECMSessionIdle(ECMSession_State* s){
    s->processMsg = ecm_processMsg;
    s->disconnect = disconnect;
}
