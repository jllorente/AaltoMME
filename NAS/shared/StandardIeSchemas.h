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
 * @file   StandardIeSchemas.h
 * @Author Vicent Ferrer
 * @date   May, 2013
 * @brief  Common IE types definition - 3GPP 24.007 clause 11.2.1
 *
 */

#ifndef _STDIESCH_H
#define _STDIESCH_H
#include <stdint.h>

/** 3GPP 24.007 clause 11.2.1*/

/** Max number of octets on value field*/
#define NASIE_MAX8	0xff
#define NASIE_MAX16	0xffff

/** Type 1 V*/
typedef struct ie_v_t1_l_c{
    uint8_t v:4;
    uint8_t s:4;
}__attribute__((packed))ie_v_t1_l_t;

typedef struct ie_v_t1_h_c{
    uint8_t s:4;
    uint8_t v:4;
}__attribute__((packed))ie_v_t1_h_t;

/** Type 1 TV*/
typedef struct ie_tv_t1_c{
    uint8_t t:4;
    uint8_t v:4;
}__attribute__((packed))ie_tv_t1_t;

/** Type 2 T*/
typedef uint8_t ie_t_t2_t;

/** Type 3 V This type is only used when the length is greater than 1*/
typedef uint8_t ie_v_t3_t[NASIE_MAX8];

/** Type 3 TV*/
typedef struct ie_tv_t3_c{
    uint8_t t;
    uint8_t v[NASIE_MAX8];
}__attribute__((packed))ie_tv_t3_t;

/** Type 4 LV*/
typedef struct ie_lv_t4_c{
    uint8_t l;
    uint8_t v[NASIE_MAX8];
}__attribute__((packed))ie_lv_t4_t;

/** Type 4 TLV*/
typedef struct ie_tlv_t4_c{
    uint8_t t;
    uint8_t l;
    uint8_t v[NASIE_MAX8];
}__attribute__((packed))ie_tlv_t4_t;

/** Type 6 LV*/
typedef struct ie_lv_t6_c{
    uint16_t    l;
    uint8_t     v[NASIE_MAX16];
}__attribute__((packed))ie_lv_t6_t;

/** Type 6 LTV*/
typedef struct ie_tlv_t6_c{
    uint8_t     t;
    uint16_t    l;
    uint8_t     v[NASIE_MAX16];
}__attribute__((packed)) ie_tlv_t6_t;

union nAS_ie_member{
    uint8_t     iei;
    ie_v_t1_l_t v_t1_l;
    ie_v_t1_h_t v_t1_h;
    ie_tv_t1_t	tv_t1;
    ie_t_t2_t	t_t2;
    ie_v_t3_t	v_t3;
    ie_tv_t3_t	tv_t3;
    ie_lv_t4_t	lv_t4;
    ie_tlv_t4_t	tlv_t4;
    ie_lv_t6_t	lv_t6;
    ie_tlv_t6_t	tlv_t6;
}__attribute__((packed));

/* ***** IE values types ***** */

/** TAI list*/
typedef struct NAS_tai_list_c{
    uint8_t     numOfElem:5;
    uint8_t     type:2;
    union{
        struct{
            uint32_t    plmn:24;
            uint16_t    tAC[16];
        }__attribute__((packed)) singlePLMNnonconsec;
        struct{
            uint32_t    plmn:24;
            uint16_t    tAC;
        }__attribute__((packed)) singlePLMNconsec;
        struct{
            uint32_t    plmn:24;
            uint16_t    tAC;
        }__attribute__((packed)) difPLMN[16];
    }list;
}__attribute__((packed)) NAS_tai_list_t;


void nasIe_v_t1_l(uint8_t** p, const uint8_t v);
void nasIe_v_t1_h(uint8_t** p, const uint8_t v);
void nasIe_tv_t1(uint8_t** p, const uint8_t t, const uint8_t v);
void nasIe_t_t2(uint8_t** p, const uint8_t t);
void nasIe_v_t3(uint8_t** p, const uint8_t *v, const uint8_t vsize);
void nasIe_tv_t3(uint8_t** p, const uint8_t t, const uint8_t *v, const uint8_t vsize);
void nasIe_lv_t4(uint8_t** p, const uint8_t *v, const uint8_t len);
void nasIe_tlv_t4(uint8_t** p, const uint8_t t, const uint8_t *v, const uint8_t len);
void nasIe_lv_t6(uint8_t** p, const uint8_t *v, const uint16_t len);
void nasIe_tlv_t6(uint8_t** p, const uint8_t t, const uint8_t *v, const uint16_t len);


#endif  /* !_STDIESCH_H */
