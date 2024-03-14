#include "elmos/includes/el_types_ACM0_GCC.h"

#ifndef DBC_H_
#define DBC_H_

 typedef union bk0{
    struct{
        u16 distance      :16;
        u16 temp          :8;
        u16 measure       :3;
        u16 ringdown_time :16;
        u16 delay_time    :16;
    }sMsg;
    uint8_t flog;
 }bk0_dbc,*PTR_bk0_dbc;

 typedef union bk0_fault{
    struct{
      u8 SnsParaInitFail      :1;
      u8 SnsOpen              :1;
      u8 SnsNosingal          :1;
      u8 SnsDInitFail         :1;
      u8 SnsHwErr             :1;
      u8 SnsDisturb           :1;
      u8 SnsComErr            :1;
      u8 SnsBlock             :1;
      u8 SnsShort             :2;
      u8 SnsVS                :8;
    }sMsg;
    uint8_t flog;
 }bk0_fault_dbc,*PTR_bk0_fault_dbc;


 typedef union bk0_other{
    struct{
      u8 OSC_TRIM_3_0         :4;
      u8 CUSTOMER_BITS_6_0    :7;
      u8 G_ANA_2_0            :3;
      u8 G_DIG_6_0            :7;
      u8 F_DRV_7_2            :6;
      u8 I_DRV_1_0            :5;
      u8 F_DRV_1_0            :2;
      u8 status_s             :5;
      u8 status_fd            :5;
    }sMsg;
    uint8_t flog;
 }bk0_other_dbc,*PTR_bk0_other_dbc;

#endif /*MOD_DBC_H_*/