#ifndef _KNG_MIFARE_CARD_H_
#define _KNG_MIFARE_CARD_H_

#include "include/datatype.h"
#include "z18pos.h"

#define CARD_PRC_BEGIN 1 // 读卡,开始交易
#define CARD_PRC_WRITE_MONEY 2 // 写卡金额成功

#define CARD_MAX_REC 10 // 卡中记录数
/** 
 * @brief 登录卡片扇区
 * 
 * @param phyno 
 * @param sect 
 * 
 * @return 
 */
uint8 kng_login_card(uint8 *phyno,uint8 sect);
/** 
 * @brief 读取卡物理ID号，并 select 卡
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 kng_read_phyno(uint8 *phyno);
/** 
 * @brief 读卡信息
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 read_card_info(const uint8 *phyno);
/** 
 * @brief 读卡钱包信息
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 read_card_purse(z18_record_t *record,card_rec_info_t *card_rec);
/** 
 * @brief 写卡钱包
 * 
 * @param record 
 * @param money 
 * 
 * @return 
 */
uint8 write_card_purse(z18_record_t *record,card_rec_info_t *card_rec);

#endif // _KNG_MIFARE_CARD_H_

