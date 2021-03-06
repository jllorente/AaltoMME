/* AaltoMME - Mobility Management Entity for LTE networks
 * Copyright (C) 2013 Vicent Ferrer Guash & Jesus Llorente Santos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   Messages.h
 * @Author Vicent Ferrer
 * @date   May, 2013
 * @brief  NAS messages
 *
 * The structures are a collection of pointers to the data.
 */

#ifndef _NAS_MESSAGES_H
#define _NAS_MESSAGES_H
#include <stdint.h>
#include <stddef.h>
#include "StandardIeSchemas.h"

typedef struct NAS_Header_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
}NAS_Header_t;

/** Generic Messages Structures*/
/** EMM Plain message */
typedef struct EMM_PlainMessage_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    union nAS_ie_member ie[30];
}EMM_Message_t;

/** ESM Plain message */
typedef struct ESM_PlainMessage_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t bearerIdendity;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member ie[30];
}ESM_Message_t;

typedef union NASPlainMsg_c{
    EMM_Message_t eMM;
    ESM_Message_t eSM;
}NASPlainMsg_t;

/** SECURITY PROTECTED NAS MESSAGE  */
typedef struct SecurityProtectedMsg_c{
    ie_v_t1_l_t     protocolDiscriminator;
    ie_v_t1_h_t     securityHeaderType;
    ie_v_t3_t       messageAuthCode;
    uint8_t         sequenceNum;
    uint8_t         *msg;
    uint32_t        len;
}SecurityProtectedMsg_t;

/** Structure defining the generic NAS message, plain or ciphered*/
typedef union GenericNASMsg_c{
    NAS_Header_t            header;
    NASPlainMsg_t           plain;
    SecurityProtectedMsg_t  ciphered;
}GenericNASMsg_t;

/**Identity Response : UE to nework : dual*/
typedef struct IdentityResponse_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    ie_lv_t4_t  mobileId;
}IdentityResponse_t;

void dec_IdentityResponse(IdentityResponse_t *msg, const uint8_t *buffer, const size_t s);

/** Authentication Response : UE to network : dual*/
typedef struct AuthenticationResponse_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    ie_lv_t4_t  authParam;
}AuthenticationResponse_t;

void dec_AuthenticationResponse(AuthenticationResponse_t *msg, const uint8_t *buffer, const size_t s);

/** Authentication Failure : UE to network : dual*/
typedef struct AuthenticationFailure_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    uint8_t     eMMCause;
    union nAS_ie_member optionals[1];
}AuthenticationFailure_t;

void dec_AuthenticationFailure(AuthenticationFailure_t *msg, const uint8_t *buffer, const size_t s);


/* ** Specific Procedures Messages ** */

/**ATTACH ACCEPT : network to UE : dual*/
typedef struct AttachAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    ie_v_t1_l_t ePSAttachResult;
    ie_v_t3_t   t3412;
    ie_lv_t4_t	tAI_list;
    ie_lv_t6_t	eSM_MessageContainer;
    union nAS_ie_member *optionals[11];
}AttachAccept_t;

void dec_AttachAccept(AttachAccept_t *msg, const uint8_t *buffer, const size_t s);


/** ATTACH COMPLETE : UE to network : dual*/
typedef struct AttachComplete_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    ie_lv_t6_t	eSM_MessageContainer;
}AttachComplete_t;

void dec_AttachComplete(AttachComplete_t *msg, const uint8_t *buffer, const size_t s);

/** ATTACH REJECT   : network to UE : dual*/
typedef struct AttachReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    uint8_t     eMMCause;
    union nAS_ie_member optionals[3];
}AttachReject_t;

void dec_AttachReject(AttachReject_t *msg, const uint8_t *buffer, const size_t s);


/** ATTACH REQUEST  : UE to network : dual*/
typedef struct AttachRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t	securityHeaderType;
    ie_t_t2_t	messageType;
    ie_v_t1_l_t ePSAttachType;
    ie_v_t1_h_t nASKeySetId;
    ie_lv_t4_t  ePSMobileId;
    ie_lv_t4_t	uENetworkCapability;
    ie_lv_t6_t	eSM_MessageContainer;
    union nAS_ie_member optionals[17];
}AttachRequest_t;

void dec_AttachRequest(AttachRequest_t *msg, const uint8_t *buffer, const size_t s);


/** DETACH ACCEPT : network to UE : dual*/
typedef struct DetachAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
}DetachAccept_t;


/** DETACH REQUEST : UE to network : dual*/
typedef struct DetachRequestUEOrig_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t detachType;
    ie_v_t1_h_t nASKeySetId;
    ie_lv_t4_t  ePSMobileId;
    union nAS_ie_member optionals[17];
}DetachRequestUEOrig_t;

void dec_DetachRequestUEOrig(DetachRequestUEOrig_t *msg, const uint8_t *buffer, const size_t s);


/** DETACH REQUEST : network to UE : dual*/
typedef struct DetachRequestUETerm_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t detachType;
    union nAS_ie_member optionals[1];
}DetachRequestUETerm_t;

void dec_DetachRequestUETerm(DetachRequestUETerm_t *msg, const uint8_t *buffer, const size_t s);



/** TRACKING AREA UPDATE ACCEPT : network to UE : dual*/
typedef struct TrackingAreaUpdateAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t ePSUpdateResult;
    union nAS_ie_member optionals[14];
}TrackingAreaUpdateAccept_t;

void dec_TrackingAreaUpdateAccept(TrackingAreaUpdateAccept_t *msg, const uint8_t *buffer, const size_t s);

/** TRACKING AREA UPDATE COMPLETE : UE to network : dual*/
typedef struct TrackingAreaUpdateComplete_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
}TrackingAreaUpdateComplete_t;


/** TRACKING AREA UPDATE REJECT : network to UE : dual*/
typedef struct TrackingAreaUpdateReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    uint8_t     eMMCause;
    union nAS_ie_member optionals[1];
}TrackingAreaUpdateReject_t;

void dec_TrackingAreaUpdateReject(TrackingAreaUpdateReject_t *msg, const uint8_t *buffer, const size_t s);


/** TRACKING AREA UPDATE REQUEST : UE to network : dual*/
typedef struct TrackingAreaUpdateRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t ePSUpdateType;
    ie_v_t1_h_t nASKeySetId;
    ie_lv_t4_t  oldGUTI;    /*EPS mobile identity*/
    union nAS_ie_member optionals[22];
}TrackingAreaUpdateRequest_t;

void dec_TrackingAreaUpdateRequest(TrackingAreaUpdateRequest_t *msg, const uint8_t *buffer, const size_t s);


/*ESM*/

/**  ACTIVATE DEFAULT EPS BEARER CONTEXT ACCEPT : UE to network : dual*/
typedef struct ActivateDefaultEPSBearerContextAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member optionals[1];
}ActivateDefaultEPSBearerContextAccept_t;

void dec_ActivateDefaultEPSBearerContextAccept(ActivateDefaultEPSBearerContextAccept_t *msg, const uint8_t *buffer, const size_t s);

/**  ACTIVATE DEFAULT EPS BEARER CONTEXT REJECT : UE to network : dual*/
typedef struct ActivateDefaultEPSBearerContextReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[1];
}ActivateDefaultEPSBearerContextReject_t;

void dec_ActivateDefaultEPSBearerContextReject(ActivateDefaultEPSBearerContextReject_t *msg, const uint8_t *buffer, const size_t s);

/**  ACTIVATE DEFAULT EPS BEARER CONTEXT REQUEST : network to UE : dual*/
typedef struct ActivateDefaultEPSBearerContextRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_lv_t4_t  ePSQoS;
    ie_lv_t4_t  accessPointName;
    ie_lv_t4_t  pDNAddress;
    union nAS_ie_member optionals[9];
}ActivateDefaultEPSBearerContextRequest_t;

void dec_ActivateDefaultEPSBearerContextRequest(ActivateDefaultEPSBearerContextRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  ACTIVATE DEDICATED EPS BEARER CONTEXT ACCEPT : UE to network : dual*/
typedef struct ActivateDedicatedEPSBearerContextAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member optionals[1];
}ActivateDedicatedEPSBearerContextAccept_t;

void dec_ActivateDedicatedEPSBearerContextAccept(ActivateDedicatedEPSBearerContextAccept_t *msg, const uint8_t *buffer, const size_t s);

/**  ACTIVATE DEDICATED EPS BEARER CONTEXT REJECT : UE to network : dual*/
typedef struct ActivateDedicatedEPSBearerContextReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[1];
}ActivateDedicatedEPSBearerContextReject_t;

void dec_ActivateDedicatedEPSBearerContextReject(ActivateDedicatedEPSBearerContextReject_t *msg, const uint8_t *buffer, const size_t s);

/**  ACTIVATE DEDICATED EPS BEARER CONTEXT REQUEST : network to UE : dual*/
typedef struct ActivateDedicatedEPSBearerContextRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t linkedEPSId;
    ie_lv_t4_t  ePSQoS;
    ie_lv_t4_t  tFT;
    union nAS_ie_member optionals[6];
}ActivateDedicatedEPSBearerContextRequest_t;

void dec_ActivateDedicatedEPSBearerContextRequest(ActivateDedicatedEPSBearerContextRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  MODIFY EPS BEARER CONTEXT ACCEPT  : UE to network : dual*/
typedef struct ModifyEPSBearerContextAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member optionals[1];
}ModifyEPSBearerContextAccept_t;

void dec_ModifyEPSBearerContextAccept(ModifyEPSBearerContextAccept_t *msg, const uint8_t *buffer, const size_t s);

/**  MODIFY EPS BEARER CONTEXT REJECT : UE to network : dual*/
typedef struct ModifyEPSBearerContextReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[1];
}ModifyEPSBearerContextReject_t;

void dec_ModifyEPSBearerContextReject(ModifyEPSBearerContextReject_t *msg, const uint8_t *buffer, const size_t s);

/**  MODIFY EPS BEARER CONTEXT REQUEST  : network to UE : dual*/
typedef struct ModifyEPSBearerContextRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member optionals[8];
}ModifyEPSBearerContextRequest_t;

void dec_ModifyEPSBearerContextRequest(ModifyEPSBearerContextRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  DEACTIVATE EPS BEARER CONTEXT ACCEPT  : UE to network : dual*/
typedef struct DeactivateEPSBearerContextAccept_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    union nAS_ie_member optionals[1];
}DeactivateEPSBearerContextAccept_t;

void dec_DeactivateEPSBearerContextAccept(DeactivateEPSBearerContextAccept_t *msg, const uint8_t *buffer, const size_t s);

/**  DEACTIVATE EPS BEARER CONTEXT REQUEST  : network to UE : dual*/
typedef struct DeactivateEPSBearerContextRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[2];
}DeactivateEPSBearerContextRequest_t;

void dec_DeactivateEPSBearerContextRequest(DeactivateEPSBearerContextRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  PDN CONNECTIVITY REJECT   : network to UE : dual*/
typedef struct PDNConnectivityReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[2];
}PDNConnectivityReject_t;

void dec_PDNConnectivityReject(PDNConnectivityReject_t *msg, const uint8_t *buffer, const size_t s);

/**  PDN CONNECTIVITY REQUEST   : UE to network : dual*/
typedef struct PDNConnectivityRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t requestType;
    ie_v_t1_h_t PDNType;
    union nAS_ie_member optionals[4];
}PDNConnectivityRequest_t;

void dec_PDNConnectivityRequest(PDNConnectivityRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  PDN DISCONNECT REJECT   : network to UE : dual*/
typedef struct PDNDisconnectReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[1];
}PDNDisconnectReject_t;

void dec_PDNDisconnectReject(PDNDisconnectReject_t *msg, const uint8_t *buffer, const size_t s);

/**  PDN DISCONNECT REQUEST   : UE to network : dual*/
typedef struct PDNDisconnectRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t linkedEPSId;
    union nAS_ie_member optionals[1];
}PDNDisconnectRequest_t;

void dec_PDNDisconnectRequest(PDNDisconnectRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  BEARER RESOURCE ALLOCATION REJECT   : network to UE : dual*/
typedef struct BearerResourceAllocationReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[2];
}BearerResourceAllocationReject_t;

void dec_BearerResourceAllocationReject(BearerResourceAllocationReject_t *msg, const uint8_t *buffer, const size_t s);

/**  BEARER RESOURCE ALLOCATION REQUEST    : UE to network : dual*/
typedef struct BearerResourceAllocationRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t linkedEPSId;
    ie_lv_t4_t  trafficFlowAggregate;
    ie_lv_t4_t  requiredTrafficFlowQoS;
    union nAS_ie_member optionals[2];
}BearerResourceAllocationRequest_t;

void dec_BearerResourceAllocationRequest(BearerResourceAllocationRequest_t *msg, const uint8_t *buffer, const size_t s);


/**  BEARER RESOURCE MODIFICATION REJECT   : network to UE : dual*/
typedef struct BearerResourceModificationReject_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    uint8_t     eSMCause;
    union nAS_ie_member optionals[2];
}BearerResourceModificationReject_t;

void dec_BearerResourceModificationReject(BearerResourceModificationReject_t *msg, const uint8_t *buffer, const size_t s);

/**  BEARER RESOURCE MODIFICATION REQUEST    : UE to network : dual*/
typedef struct BearerResourceModificationRequest_c{
    ie_v_t1_l_t protocolDiscriminator;
    ie_v_t1_h_t securityHeaderType;
    uint8_t     procedureTransactionIdentity;
    ie_t_t2_t   messageType;
    ie_v_t1_l_t EPSBearerIdForPacketFilter;
    ie_lv_t4_t  trafficFlowAggregate;
    union nAS_ie_member optionals[4];
}BearerResourceModificationRequest_t;

void dec_BearerResourceModificationRequest(BearerResourceModificationRequest_t *msg, const uint8_t *buffer, const size_t s);

#endif  /* !_NAS_MESSAGES_H */
