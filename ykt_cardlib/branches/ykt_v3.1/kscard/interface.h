#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include "ksdevice.h"
#include "ksenc.h"

int load_interface_layer(const char *path);
int free_interface_layer();

extern ks_device_op_t g_dev_op;
extern ks_reader_dev_t g_reader;
extern ks_card_info_t g_cardinfo;
extern ks_enc_op_t g_enc_op;

#endif // _INTERFACE_H_
