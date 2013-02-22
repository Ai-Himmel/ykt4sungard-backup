#ifndef _KNG_MIFARE_CARD_H_
#define _KNG_MIFARE_CARD_H_

#include "include/datatype.h"
#include "z18pos.h"

#define CARD_PRC_BEGIN 1 // ����,��ʼ����
#define CARD_PRC_WRITE_MONEY 2 // д�����ɹ�

#define CARD_MAX_REC 10 // ���м�¼��
/** 
 * @brief ��¼��Ƭ����
 * 
 * @param phyno 
 * @param sect 
 * 
 * @return 
 */
uint8 kng_login_card(uint8 *phyno,uint8 sect);
/** 
 * @brief ��ȡ������ID�ţ��� select ��
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 kng_read_phyno(uint8 *phyno);
/** 
 * @brief ������Ϣ
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 read_card_info(const uint8 *phyno);
/** 
 * @brief ����Ǯ����Ϣ
 * 
 * @param phyno 
 * 
 * @return 
 */
uint8 read_card_purse(z18_record_t *record,card_rec_info_t *card_rec);
/** 
 * @brief д��Ǯ��
 * 
 * @param record 
 * @param money 
 * 
 * @return 
 */
uint8 write_card_purse(z18_record_t *record,card_rec_info_t *card_rec);

#endif // _KNG_MIFARE_CARD_H_

