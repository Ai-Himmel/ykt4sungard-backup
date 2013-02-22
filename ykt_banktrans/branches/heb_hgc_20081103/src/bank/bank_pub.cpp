#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank_pub.h"

int debug=2;

void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);

	if(debug < 2)
		return;
	printf("���״���	=[%2.2s]\n",pTransPak->TranCode);
	printf("���׽��	=[%2.2s]\n",pTransPak->RetCode);
	printf("��������	=[%8.8s]\n",pTransPak->TranDate);
	printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCardNo);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->MercAccount);
	printf("ת�˽��	=[%9.9s]\n",pTransPak->TranMoney);
	printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%8.8s]\n",pTransPak->LocalSn);
	printf("������ˮ��	=[%20.20s]\n",pTransPak->BankSn);
	printf("�ն��豸��	=[%5.5s]\n",pTransPak->PosNo);
}

void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("���״���	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("���׽��	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("��������	=[%8.8s]\n",pTransPak->head.);
	//printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCard);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("ת�˽��	=[%13.13s]\n",pTransPak->TranMoney);
	//printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("������ˮ��	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("�ն��豸��	=[%2.2s]\n",pTransPak->head.TmlId);
}

void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("���״���	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("���׽��	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("��������	=[%8.8s]\n",pTransPak->head.);
	//printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCard);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("ת�˽��	=[%9.9s]\n",pTransPak->TranMoney);
	printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("������ˮ��	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("�ն��豸��	=[%2.2s]\n",pTransPak->head.TmlId);

}

void Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	
	printf("����ͷ����	=[%d]\n", pTransPak->head.packet_head_length[0]);
	printf("���׽��	=[%X]\n", pTransPak->head.head_flag[0]);
	printf("�����ܳ���	=[%4.4s]\n", pTransPak->head.packet_length);
	printf("Ŀ��ID	=[%11.11s]\n", pTransPak->head.dest_id);
	printf("ԴID 		=[%11.11s]\n", pTransPak->head.src_id);
	printf("����λ	=[%X:%X:%X]\n", pTransPak->head.reserve_1[0],pTransPak->head.reserve_1[1],pTransPak->head.reserve_1[2]);
	printf("���κ�	=[%X]\n", pTransPak->head.batch_no[0]);
	printf("������Ϣ	=[%8.8s]\n", pTransPak->head.trade_info);
	printf("�û���Ϣ	=[%X]\n", pTransPak->head.user_info[0]);
	printf("�ܾ���	=[%5.5s]\n", pTransPak->head.reject_code);
	printf("��Ϣ����  =[%4.4s]\n", pTransPak->msg_type);
	printf("λͼ  =[%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->bit[0], pTransPak->bit[1], pTransPak->bit[2], pTransPak->bit[3], pTransPak->bit[4], pTransPak->bit[5],pTransPak->bit[6], pTransPak->bit[7], pTransPak->bit[8], pTransPak->bit[9], pTransPak->bit[10], pTransPak->bit[11], pTransPak->bit[12], pTransPak->bit[13], pTransPak->bit[14], pTransPak->bit[15]);
	printf("���ʺ�  =[%21.21s]\n", pTransPak->main_account);
	printf("���״�����  =[%6.6s]\n", pTransPak->trade_deal_code);
	printf("���״���ʱ��  =[%10.10s]\n", pTransPak->trade_deal_time);
	printf("ϵͳ���ٺ�  =[%6.6s]\n", pTransPak->system_id);
	printf("�ܿ������ڵ�ʱ��  =[%6.6s]\n", pTransPak->accept_card_time);
	printf("�ܿ������ڵ�����  =[%4.4s]\n", pTransPak->accept_card_date);
	printf("�̻�����  =[%4.4s]\n", pTransPak->shop_type);
	printf("�������뷽ʽ��  =[%3.3s]\n", pTransPak->service_input_code);
	printf("����������  =[%2.2s]\n", pTransPak->service_terms_code);
	printf("����ڵ����  =[%13.13s]\n", pTransPak->proxy_node_code);
	printf("���ͽڵ����  =[%13.13s]\n", pTransPak->send_node_code);
	printf("�ڶ��ŵ�����  =[%39.39s]\n", pTransPak->second_mag_tune);
	printf("�����ŵ�����  =[%107.107s]\n", pTransPak->third_mag_tune);
	printf("�����ο���  =[%12.12s]\n", pTransPak->check_code);
	printf("�ܿ����ն˱�ʶ��  =[%8.8s]\n", pTransPak->device_phy);
	printf("�ܿ�����ʶ  =[%15.15s]\n", pTransPak->mark);
	printf("�ܿ�����ַ����  =[%40.40s]\n", pTransPak->address);
	printf("��������  =[%515.515s]\n", pTransPak->append_data);
	printf("���׻��Ҵ���  =[%3.3s]\n", pTransPak->trade_money_code);
	printf("���˱�ʶ������  =[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->personal_mark[0], pTransPak->personal_mark[1],
		pTransPak->personal_mark[2], pTransPak->personal_mark[3], pTransPak->personal_mark[4], pTransPak->personal_mark[5],
		pTransPak->personal_mark[6], pTransPak->personal_mark[7]);
	printf("�Զ�����  =[%33.33s]\n", pTransPak->defalut_area);
	printf("���ܽڵ��ʶ��  =[%13.13s]\n", pTransPak->accept_node_code);
	printf("���ļ�����  =[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->packet_identity_code[0], pTransPak->packet_identity_code[1],
		pTransPak->packet_identity_code[2], pTransPak->packet_identity_code[3], pTransPak->packet_identity_code[4],
		pTransPak->packet_identity_code[5], pTransPak->packet_identity_code[6], pTransPak->packet_identity_code[7]);
	printf("Ӧ����  =[%2.2s]\n", pTransPak->answser_code);
	printf("ʵ�����  =[%43.43s]\n", pTransPak->cur_balance);
	printf("��������  =[%4.4s]\n", pTransPak->liquidate_date);
	printf("���׽��  =[%12.12s]\n", pTransPak->trade_money);
	printf("ԭʼ����  =[%42.42s]\n", pTransPak->inital_data);
	printf("������Ҵ���  =[%3.3s]\n", pTransPak->liq_cur_code);
	printf("������Ϣ����  =[%3.3s]\n", pTransPak->net_info_code);
	printf("���ӽ�����Ϣ  =[%103.103s]\n", pTransPak->append_trade_info);
	printf("ת�ʱ���  =[%10.10s]\n", pTransPak->transfer_count);
	printf("��ȫ������Ϣ  =[%16.16s]\n", pTransPak->security_info_control);
	printf("���׿���  =[%30.30s]\n", pTransPak->card_id);
	printf("������  =[%12.12s]\n", pTransPak->liq_money);
}

void Trace_Bank_Package_YNNH(BANK_YNNH_TRADE_STRUCT_PACKET *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	
	printf("�汾��Ϣ��	=[%2.2s]\n", pTransPak->ynnh_head.bank_version);
	printf("���ݰ���С	=[%5.5s]\n", pTransPak->ynnh_head.packet_length);
	printf("���𷽱�ʶ	=[%2.2s]\n", pTransPak->ynnh_head.lanuch_mark);
	printf("�����㷨	=[%1.1s]\n", pTransPak->ynnh_head.algorithm);
	printf("��Կ�ֶ� 	=[%16.16s]\n", pTransPak->ynnh_head.secret_seg);
	printf("MACУ����	=[%8.8s]\n", pTransPak->ynnh_head.mac_check);
	printf("��������	=[%4.4s]\n", pTransPak->ynnh_head.trade_type);
	printf("��������	=[%8.8s]\n", pTransPak->ynnh_head.trade_date);
	printf("����ʱ��	=[%6.6s]\n", pTransPak->ynnh_head.trade_time);
	printf("�����¼��	=[%5.5s]\n", pTransPak->ynnh_head.packet_count);
	printf("��ˮ��	=[%20.20s]\n", pTransPak->ynnh_head.trade_serial);
	printf("�豸��	=[%8.8s]\n", pTransPak->ynnh_head.device_id);
	printf("�ɹ���־	=[%1.1s]\n", pTransPak->ynnh_head.success_flag);
	printf("������	=[%4.4s]\n", pTransPak->ynnh_head.error_code);
	printf("������־	=[%1.1s]\n", pTransPak->ynnh_head.follow_flag);
	printf("�����	=[%5.5s]\n", pTransPak->ynnh_head.packet_id);
	printf("��������	=[%2.2s]\n", pTransPak->ynnh_head.request_type);
	printf("��������ID	=[%8.8s]\n", pTransPak->ynnh_head.channel_id);
	printf("���п���	=[%20.20s]\n", pTransPak->bank_account);
	printf("������	=[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->bank_pin[0], pTransPak->bank_pin[1], pTransPak->bank_pin[2], pTransPak->bank_pin[3],
		pTransPak->bank_pin[4], pTransPak->bank_pin[5], pTransPak->bank_pin[6], pTransPak->bank_pin[7]);
	printf("���׽��	=[%14.14s]\n", pTransPak->trade_money);
	printf("��������ˮ��	=[%20.20s]\n", pTransPak->trans_serail);
	printf("�˻����	=[%14.14s]\n", pTransPak->account_money);
	printf("�������	=[%14.14s]\n", pTransPak->remain_money);
	printf("���׿���	=[%12.12s]\n", pTransPak->card_id);
}

void Trace_Bank_Package_HRBZH(BANK_HRBZH_TRADE_STRUCT_PACKET *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;

	printf("�ܰ�����	=[%4.4s]\n", pTransPak->hrbzh_head.AllPacketLen);
	printf("��������	=[%1.1d]\n", pTransPak->hrbzh_head.PKgtype[0]);		// 0 ��8583��, 1 ��8583��
	printf("��Ϣ����	=[%4.4s]\n", pTransPak->hrbzh_head.MsgType);
	printf("Prccde	=[%6.6s]\n", pTransPak->hrbzh_head.Prccde);
	printf("�յ�������	=[%8.8s]\n", pTransPak->hrbzh_head.AcqInstID);
	printf("�յ������ն˺� 	=[%8.8s]\n", pTransPak->hrbzh_head.TermID);
	printf("Trcno	=[%6.6s]\n", pTransPak->hrbzh_head.Trcno);
	printf("������	=[%2.2s]\n", pTransPak->hrbzh_head.Custype);
	printf("����	=[%25.25s]\n", pTransPak->hrbzh_head.Cusidt);
	printf("Ӧ������	=[%2.2s]\n", pTransPak->hrbzh_head.Apcode);
	printf("���ʷ���������	=[%8.8s]\n", pTransPak->hrbzh_head.SrvuID);
	printf("������	=[%2.2s]\n", pTransPak->hrbzh_head.Rspcde);
	printf("�������	=[%2.2s]\n", pTransPak->hrbzh_head.PKseq);
	printf("������	=[%6.6s]\n", pTransPak->hrbzh_head.Filler);
	printf("����������	=[%4.4s]\n", pTransPak->hrbzh_head.MsgLen);
	
	printf("��Ϣ����	=[%4.4s]\n", pTransPak->hrbzh_trade_packet.msg_type_id);
	printf("����λͼ	=[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->hrbzh_trade_packet.bit_map[0], pTransPak->hrbzh_trade_packet.bit_map[1], pTransPak->hrbzh_trade_packet.bit_map[2],
	pTransPak->hrbzh_trade_packet.bit_map[3], pTransPak->hrbzh_trade_packet.bit_map[4], pTransPak->hrbzh_trade_packet.bit_map[5], pTransPak->hrbzh_trade_packet.bit_map[6], pTransPak->hrbzh_trade_packet.bit_map[7]);	
	printf("��չλͼ	=[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->hrbzh_trade_packet.bit_map_ext[0], pTransPak->hrbzh_trade_packet.bit_map_ext[1], pTransPak->hrbzh_trade_packet.bit_map_ext[2],
		pTransPak->hrbzh_trade_packet.bit_map_ext[3], pTransPak->hrbzh_trade_packet.bit_map_ext[4], pTransPak->hrbzh_trade_packet.bit_map_ext[5], pTransPak->hrbzh_trade_packet.bit_map_ext[6], pTransPak->hrbzh_trade_packet.bit_map_ext[7]);
	printf("��ǿ�����	=[%22.22s]\n", pTransPak->hrbzh_trade_packet.account_id);
	printf("������	=[%6.6s]\n", pTransPak->hrbzh_trade_packet.process_code);
	printf("���׽��	=[%12.12s]\n", pTransPak->hrbzh_trade_packet.trans_amount);
	printf("��������ʱ��	=[%10.10s]\n", pTransPak->hrbzh_trade_packet.trans_date_time);
	printf("ϵͳ׷�ٱ�ʾ��	=[%6.6s]\n", pTransPak->hrbzh_trade_packet.stan);
	printf("����ʱ��	=[%6.6s]\n", pTransPak->hrbzh_trade_packet.time_trans);
	printf("��������	=[%4.4s]\n", pTransPak->hrbzh_trade_packet.date_trans);
	printf("���ڲ�����	=[%4.4s]\n", pTransPak->hrbzh_trade_packet.date_capture);
	printf("�������������	=[%2.2s]\n", pTransPak->hrbzh_trade_packet.point_of_scc);
	printf("������ˮ��	=[%6.6s]\n", pTransPak->hrbzh_trade_packet.flush_trade_serial_no);
	printf("�绰���������	=[%11.11s]\n", pTransPak->hrbzh_trade_packet.aiic);
	printf("�ͻ�����ƽ̨����	=[%11.11s]\n", pTransPak->hrbzh_trade_packet.css_id);
	printf("������	=[%2.2s]\n", pTransPak->hrbzh_trade_packet.response_code);
	printf("�����ն˺�  =[%8.8s]\n", pTransPak->hrbzh_trade_packet.acceptor_terminal_id);
	printf("���ܵ�ID��  =[%15.15s]\n", pTransPak->hrbzh_trade_packet.acceptor_Id);
	printf("��������  =[%999.999s]\n", pTransPak->hrbzh_trade_packet.encrypt_pwd);
	printf("����ֵ1  =[%999.999s]\n", pTransPak->hrbzh_trade_packet.reserve_id1);
	printf("����  =[%16.16s]\n", pTransPak->hrbzh_trade_packet.pid_data);
	printf("����ֵ2  =[%16.16s]\n", pTransPak->hrbzh_trade_packet.reserve_id2);
	printf("ԭʼ����  =[%42.42s]\n", pTransPak->hrbzh_trade_packet.original_data);
	printf("����ֵ3  =[%28.28s]\n", pTransPak->hrbzh_trade_packet.reserve_id3);
	printf("����ֵ4 =[%28.28s]\n", pTransPak->hrbzh_trade_packet.reserve_id4);

	return ;
}

int Packet_Buf_Transform(char *buf, void *packet, int change_flag, 
							  int bank_id, int trade_type, 
							  INNER_TRANS_REQUEST * pNode, int serial_no)
{
	BANK_YNXH_TRADE_STRUCT_PACKET *packet_point = NULL;
	BANK_YNNH_TRADE_STRUCT_PACKET *packet_point2 = NULL;
	BANK_HRBZH_TRADE_STRUCT_PACKET *packet_point3 = NULL;			// ���������нṹ
	
	int _length = 0;						// �䳤����
	int packet_length = 0;					// ÿ�����ĵ����ݳ���
	int buf_length = 0;						// �����ܵ�buf����
	char prs_next[516] = "";				// �źϼ��ܺ����Կ
	char mac[9] = "";						// �źϼ�����mac��Կ
	char packet_str[516] = "";				// �źϱ������ 
	int req_packet_length = 0;				// �ź��������ܳ���
	int ans_packet_length = 0;				// �ź�Ӧ�����ܳ���
	char str_length[6] = "";
	char msg[25] = "";
	double second = 0.0;
	char forward_date[10]="";			    // ����ʱ����ļ�����ȡ��
	int ret = 0;
	char all_bit_map[129] = "";				// iso8583 char type bit map
	unsigned char bcd_bit[16] = "";			// binary bit map	
	static int local_serial = 400011;
	if (NULL == buf) { return -2; }

	writelog(LOG_ERR,"��������־[%d]--���б�־[%d]--��������[%d]",change_flag, bank_id, trade_type);
	// ������ѹ��������
	if (PACKET_TO_BUF == change_flag)
	{
		// �ź�����
		if (BANK_YNXH == bank_id)
		{		
			packet_point = (BANK_YNXH_TRADE_STRUCT_PACKET *)packet;
			// 1. ����ͷ���������, ��ѯ, ����, ����, ����ͨ��
			packet_point->head.packet_head_length[0] = 46;
			packet_point->head.head_flag[0] = 1;			//bit:10000001
//			memcpy(packet_point->head.dest_id, "14097310   ", sizeof(packet_point->head.dest_id) - 1);
//			memcpy(packet_point->head.src_id, "00010000   ", sizeof(packet_point->head.dest_id) - 1);	// ����ʱ���ṩ
			memcpy(packet_point->head.dest_id, "99990001   ", sizeof(packet_point->head.dest_id) - 1);
			memcpy(packet_point->head.src_id, "01040001   ", sizeof(packet_point->head.dest_id) - 1);
			memcpy(packet_point->head.reserve_1, "000", sizeof(packet_point->head.reserve_1) - 1);
			packet_point->head.batch_no[0] = 0x30;
			memcpy(packet_point->head.trade_info, "00000000", sizeof(packet_point->head.trade_info) - 1);
			packet_point->head.user_info[0] = 0x30;
			memcpy(packet_point->head.reject_code, "00000", sizeof(packet_point->head.reject_code) - 1);
			sprintf(packet_point->main_account, "%02d", strlen(pNode->BankCardNo));
			memcpy(packet_point->main_account + 2, pNode->BankCardNo, strlen(pNode->BankCardNo));
			strncpy(packet_point->trade_deal_time, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4);		// Ȧ�������
			strncpy(packet_point->trade_deal_time + 4, pNode->TradeTime, sizeof(pNode->TradeTime));			// Ȧ���ʱ��
			memcpy(packet_point->accept_card_time, pNode->TradeDate + 4, sizeof(packet_point->accept_card_time) - 1);
			memcpy(packet_point->accept_card_date, pNode->TradeTime, sizeof(pNode->TradeDate) - 4);
			memcpy(packet_point->shop_type, "8220", sizeof(packet_point->shop_type) - 1);
			memcpy(packet_point->service_input_code, "021", sizeof(packet_point->service_input_code) - 1);
			memcpy(packet_point->service_terms_code, "00", sizeof(packet_point->service_terms_code) - 1);
			sprintf(packet_point->proxy_node_code, "%02d", strlen("01040001"));
			memcpy(packet_point->proxy_node_code + 2, "01040001", strlen("01040001")); // �豸ID��
			sprintf(packet_point->send_node_code, "%02d", strlen("01040000"));	// �󳤶�
			memcpy(packet_point->send_node_code + 2, "01040000", strlen("01040000")); 
			sprintf(packet_point->second_mag_tune, "%02d", strlen(pNode->SencodMagTune));	// �󳤶�
			memcpy(packet_point->second_mag_tune + 2, pNode->SencodMagTune, strlen(pNode->SencodMagTune));
			sprintf(packet_point->third_mag_tune, "%03d", strlen(pNode->ThirdMagTune));	// �󳤶�
			memcpy(packet_point->third_mag_tune + 3, pNode->ThirdMagTune, strlen(pNode->ThirdMagTune));
			memcpy(packet_point->device_phy, "00000000", 8);
			memcpy(packet_point->device_phy + 8 - strlen(pNode->TerminalId), pNode->TerminalId, strlen(pNode->TerminalId));
			strncpy(packet_point->check_code, packet_point->device_phy + 4, 4);		
			strncpy(packet_point->check_code + 4, "00", 2);
			sprintf(packet_point->check_code + 6, "%06d", 0);
			memcpy(packet_point->mark, "822010689000001", sizeof(packet_point->mark) - 1);
			memcpy(packet_point->address, "���ϲƴ���ȪУ��", sizeof(packet_point->address) - 1);
			strncpy(prs_next, pNode->Reserve1, strlen(pNode->Reserve1));
			strncpy(prs_next + strlen(pNode->Reserve1), pNode->Reserve2, strlen(pNode->Reserve2));
			strncpy(prs_next + strlen(pNode->Reserve1) + strlen(pNode->Reserve2), pNode->Reserve3, 2);
			sprintf(packet_point->append_data, "%03d", strlen(prs_next));		// 48���ֵ
			memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			memcpy(packet_point->trade_money_code, "156", sizeof(packet_point->trade_money_code) - 1);
			memcpy(packet_point->personal_mark, pNode->BankCardPwd, 8);			// 52���ֵ, �˴�Ϊ��������
			sprintf(packet_point->defalut_area, "%03d", strlen("000002000100"));
			memcpy(packet_point->defalut_area + 3, "000002000100", sizeof(packet_point->defalut_area) - 1);
			memcpy(packet_point->accept_node_code, "1101999999999", sizeof(packet_point->accept_node_code) - 1);
			sprintf(packet_point->system_id, "%06d", 0);				// ϵͳ��ˮ��
			
			// ��ѯ�������
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{	
				// 2. ��������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_QUERYBALANCE, sizeof(packet_point->msg_type) - 1);
				packet_point->bit[0] = 0xE2;
				packet_point->bit[1] = 0x38;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0xB8;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x90;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x10;
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				memcpy(packet_point->trade_deal_code, "300000", sizeof(packet_point->trade_deal_code) - 1);
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_QUERYBALANCE, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_QUERYBALANCE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code , SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);

				Caculate_Session_MAC(pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);				
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
								writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				// ��������ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->second_mag_tune) + strlen(packet_point->third_mag_tune) + strlen(packet_point->append_data) 
				                    + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) + 201;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);
				
				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->second_mag_tune);
				memcpy(buf + buf_length, packet_point->second_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->third_mag_tune);
				memcpy(buf + buf_length, packet_point->third_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->personal_mark, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			// ��������
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				// 2. ��������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_TRANS, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0xF2;
				packet_point->bit[1] = 0x3A;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0xB8;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x98;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x12;	// ����103��Ľ��׿���
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				memcpy(packet_point->trade_deal_code, "400000", sizeof(packet_point->trade_deal_code) - 1);
				mempcpy(packet_point->trade_money, "000000000000", sizeof(packet_point->trade_money) - 1);
				memcpy(packet_point->trade_money + 12 - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));
				sprintf(packet_point->system_id, "%06d", serial_no);				// ϵͳ��ˮ��
				memcpy(packet_point->liquidate_date, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4); // MMDD
				sprintf(packet_point->check_code + 6, "%06d", serial_no);				// �ܿ����ն˺ź�4λ + 00 + ϵͳ��ˮ��
				_length = strlen(trim(pNode->CardNo));
				sprintf(packet_point->card_id, "%02d", _length);
				memcpy(packet_point->card_id + 2, pNode->CardNo, _length);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_TRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_TRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->card_id + 2, SPLIT_VL);
				
				memcpy(pNode->BankCardPwd, packet_point->personal_mark, sizeof(packet_point->personal_mark));
				Caculate_Session_MAC(pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);

				memcpy(packet_point->packet_identity_code, mac, 8);
				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->second_mag_tune) + strlen(packet_point->third_mag_tune) + strlen(packet_point->append_data) 
				                    + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) + strlen(packet_point->card_id) + 233;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->trade_money, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->second_mag_tune);
				memcpy(buf + buf_length, packet_point->second_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->third_mag_tune);
				memcpy(buf + buf_length, packet_point->third_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->personal_mark, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->security_info_control, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->card_id);
				memcpy(buf + buf_length, packet_point->card_id, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				// 3. ������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_DETRANS, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0xF2;
				packet_point->bit[1] = 0x3A;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0x88;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x80;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x40;
				packet_point->bit[12] = 0x12;			// ����103��
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				getsysdate(pNode->BankDate);
				getsystime(pNode->BankTime);
				memcpy(packet_point->trade_deal_code, "400000", sizeof(packet_point->trade_deal_code) - 1);
				strncpy(packet_point->trade_deal_time, pNode->BankDate + 4, sizeof(pNode->BankDate) - 4);		// ��ǰ��������(MMDD)	
				strncpy(packet_point->trade_deal_time + 4, pNode->BankTime, sizeof(pNode->TradeTime));			// ��ǰ����ʱ��(HHMMSS)
				_length = strlen(trim(pNode->TransMoney));
				sprintf(pNode->TransMoney, "%d", atoi(pNode->TransMoney) * 100);
//				writelog(LOG_INFO,"TransMoney=[%s], Length=[%d]", pNode->TransMoney, _length);
				memcpy(packet_point->trade_money, "000000000000", sizeof(packet_point->trade_money) - 1);		// �ź�12λ, һ��ͨ9λ			
				memcpy(packet_point->trade_money + 12 - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));
				sprintf(packet_point->system_id, "%06d", pNode->RecvNo);				// ������ˮ��
				memcpy(packet_point->liquidate_date, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4); // MMDD, ����ʱ��(��Ҫ������ˮ�Ľ���ʱ��)
				sprintf(packet_point->check_code + 6, "%06d", pNode->RecvNo);				// �ܿ����ն˺ź�4λ + 00 + ϵͳ��ˮ��
				memcpy(packet_point->inital_data, BANK_YNXH_TRADE_CODE_TRANS, 4);
				memcpy(packet_point->inital_data + 4, packet_point->system_id, 6);			// ԭʼ��¼: ������ˮ�� + ��������ʱ�� + ����ԭʼ����ڵ� + ����ԭʼ���ͽڵ�
				memcpy(packet_point->inital_data + 10, pNode->TradeDate + 4, 4);			// pNode->TradeDate + 4
				memcpy(packet_point->inital_data + 14, pNode->TradeTime, 6);				// pNode->TradeTime
				memcpy(packet_point->inital_data + 20, "0000000000000000000000", 22);
				memcpy(packet_point->inital_data + 20 + 11 - strlen(packet_point->proxy_node_code + 2), packet_point->proxy_node_code + 2, strlen(packet_point->proxy_node_code + 2));
				memcpy(packet_point->inital_data + 31 + 11 - strlen(packet_point->send_node_code + 2), packet_point->send_node_code + 2, strlen(packet_point->send_node_code + 2));
				_length = strlen(trim(pNode->CardNo));
				sprintf(packet_point->card_id, "%02d", _length);
				memcpy(packet_point->card_id + 2, pNode->CardNo, _length);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_DETRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_DETRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->inital_data, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->card_id + 2, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);	// prs_next��Ϊ��������
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));

				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->append_data) + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) 
				                    + strlen(packet_point->card_id) + 251;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->trade_money, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = 42;
				memcpy(buf + buf_length, packet_point->inital_data, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->card_id);
				memcpy(buf + buf_length, packet_point->card_id, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else if (BANK_TRADE_CODE_COMPARE == trade_type)
			{
				// 4. ���˱�������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_COMPARE, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0x82;
				packet_point->bit[1] = 0x22;
				packet_point->bit[2] = 0x40;
				packet_point->bit[3] = 0x01;
				packet_point->bit[4] = 0x88;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x40;
				packet_point->bit[7] = 0x00;
				packet_point->bit[8] = 0x04;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x10;
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				getsysdate(pNode->BankDate);
				getsystime(pNode->BankTime);
				strncpy(packet_point->trade_deal_time, pNode->BankDate + 4, sizeof(pNode->BankDate) - 4);		// ��ǰ��������(MMDD)	
				strncpy(packet_point->trade_deal_time + 4, pNode->BankTime, sizeof(pNode->TradeTime));	
				sprintf(packet_point->system_id, "%06d", 0);
				ret = datetime2second(pNode->BankDate, "YYYYMMDD", &second);
				if (ret)
				{
					writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
					return ret;
				}
				second = second - 24 * 60 * 60;
				ret = second2datetime(second, forward_date, "YYYYMMDD");
				if(ret)
				{
					writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
					return 	ret;
				}
				memcpy(packet_point->liquidate_date, forward_date + 4, sizeof(pNode->BankDate) - 4);	// ��������, ���ն���
				sprintf(packet_point->check_code + 6, "%06d", 0);		// ����û����ˮ��
				memcpy(packet_point->liq_cur_code, "156", 3);
				memcpy(packet_point->net_info_code, "272", 3);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_COMPARE, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_COMPARE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);	// prs_next��Ϊ��������
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));

				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->append_data) + strlen(packet_point->accept_node_code) 
				                    + 179;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->liq_cur_code, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->net_info_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else 
			{
				NULL;
			}
		}
		// ����ũҵ����
		else if (BANK_YNNH == bank_id)
		{
			// ��ѯ���, ���ð�ͷ
			packet_point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)packet;
			memcpy(packet_point2->ynnh_head.bank_version, "01", sizeof(packet_point2->ynnh_head.bank_version));
			memcpy(packet_point2->ynnh_head.lanuch_mark, "03", sizeof(packet_point2->ynnh_head.lanuch_mark));
			memcpy(packet_point2->ynnh_head.algorithm, "1", sizeof(packet_point2->ynnh_head.algorithm));
			memset(packet_point2->ynnh_head.secret_seg, 0x20, sizeof(packet_point2->ynnh_head.secret_seg));
			memset(packet_point2->ynnh_head.mac_check, 0x20, sizeof(packet_point2->ynnh_head.mac_check));
			memcpy(packet_point2->ynnh_head.trade_type, "9529", sizeof(packet_point2->ynnh_head.trade_type));
			memcpy(packet_point2->ynnh_head.trade_date, pNode->TradeDate, sizeof(packet_point2->ynnh_head.trade_date));
			memcpy(packet_point2->ynnh_head.trade_time, pNode->TradeTime, sizeof(packet_point2->ynnh_head.trade_time));
			memset(packet_point2->ynnh_head.packet_count, 0x20, sizeof(packet_point2->ynnh_head.packet_count));
			memset(packet_point2->ynnh_head.trade_serial, 0x20, sizeof(packet_point2->ynnh_head.trade_serial));
			memset(packet_point2->ynnh_head.device_id, 0x20, sizeof(packet_point2->ynnh_head.device_id));
			memcpy(packet_point2->ynnh_head.device_id, pNode->TerminalId, strlen(pNode->TerminalId));
			memset(packet_point2->ynnh_head.success_flag, 0x20, sizeof(packet_point2->ynnh_head.success_flag));
			memcpy(packet_point2->ynnh_head.error_code, "0000", sizeof(packet_point2->ynnh_head.error_code));
			memcpy(packet_point2->ynnh_head.follow_flag, "0", sizeof(packet_point2->ynnh_head.follow_flag));
			memset(packet_point2->ynnh_head.packet_id, 0x20, sizeof(packet_point2->ynnh_head.packet_id));
			memcpy(packet_point2->ynnh_head.request_type, "01", sizeof(packet_point2->ynnh_head.request_type));
			memcpy(packet_point2->ynnh_head.channel_id, "10000311", sizeof(packet_point2->ynnh_head.channel_id));
			
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				memcpy(packet_point2->bank_account, pNode->BankCardNo, strlen(pNode->BankCardNo));
				memcpy(packet_point2->bank_pin, pNode->BankCardPwd, strlen(pNode->BankCardPwd));
				// ������ĳ���
				req_packet_length = sizeof(packet_point2->ynnh_head) + sizeof(packet_point2->bank_account) + sizeof(packet_point2->bank_pin);

				memset(packet_point2->ynnh_head.packet_length, 0x20, sizeof(packet_point2->ynnh_head.packet_length));
				sprintf(str_length, "%d", req_packet_length);
				memcpy(packet_point2->ynnh_head.packet_length, str_length, strlen(str_length));

				// ѹ���ͷ����
				_length = sizeof(packet_point2->ynnh_head);
				memcpy(buf + buf_length, &(packet_point2->ynnh_head), _length);
				// ѹ���������
				buf_length += _length;
				_length = sizeof(packet_point2->bank_account);
				memcpy(buf + buf_length, packet_point2->bank_account, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->bank_pin);
				writelog(LOG_ERR,"password=[%s], buf_length=[%d]",packet_point2->bank_pin, buf_length);
//				hex2dec(pNode->BankCardPwd, (unsigned char*)packet_point2->bank_pin, 8);
				_length = 8;
				packet_point2->bank_pin[0] = 0x73;
				packet_point2->bank_pin[1] = 0x19;
				packet_point2->bank_pin[2] = 0x86;
				packet_point2->bank_pin[3] = 0xA1;
				packet_point2->bank_pin[4] = 0xAF;
				packet_point2->bank_pin[5] = 0x9E;
				packet_point2->bank_pin[6] = 0x16;
				packet_point2->bank_pin[7] = 0x37;
				
				memcpy(buf + buf_length, packet_point2->bank_pin, _length);
			}
			// ת��
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
//				memset(packet_point2->bank_account, 0x20, sizeof(packet_point2->bank_account));
//				memset(packet_point2->bank_pin, 0x20, sizeof(packet_point2->bank_pin));
				memcpy(packet_point2->bank_account, pNode->BankCardNo, strlen(pNode->BankCardNo));
				memcpy(packet_point2->bank_pin, pNode->BankCardPwd, strlen(pNode->BankCardPwd));
//				memset(packet_point2->trade_money, 0x20, sizeof(packet_point2->trade_money));
				memcpy(packet_point2->trade_money, pNode->TransMoney, sizeof(pNode->TransMoney));
				sprintf(msg, "%d", serial_no);
//				memset(packet_point2->trans_serail, 0x20, sizeof(packet_point2->trans_serail));
				memcpy(packet_point2->trans_serail, msg, strlen(msg));
//				memset(packet_point2->card_id, 0x20, sizeof(packet_point2->card_id));
				memcpy(packet_point2->card_id, pNode->CardNo, sizeof(pNode->CardNo));
				
				// ������ĳ���
				req_packet_length = sizeof(packet_point2->ynnh_head) + sizeof(packet_point2->bank_account) + sizeof(packet_point2->bank_pin)
				+ sizeof(packet_point2->trade_money) + sizeof(packet_point2->card_id);

//				memset(packet_point2->ynnh_head.packet_length, 0x20, sizeof(packet_point2->ynnh_head.packet_length));
				sprintf(str_length, "%d", req_packet_length);
				memcpy(packet_point2->ynnh_head.packet_length, str_length, strlen(str_length));

				// ѹ���ͷ����
				_length = sizeof(packet_point2->ynnh_head);
				memcpy(buf + buf_length, &(packet_point2->ynnh_head), _length);
				// ѹ���������
				buf_length += _length;
				_length = sizeof(packet_point2->bank_account);
				memcpy(buf + buf_length, packet_point2->bank_account, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->trade_money);
				memcpy(buf + buf_length, packet_point2->trade_money, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->bank_pin);
				_length = 8;
				packet_point2->bank_pin[0] = 0x73;
				packet_point2->bank_pin[1] = 0x19;
				packet_point2->bank_pin[2] = 0x86;
				packet_point2->bank_pin[3] = 0xA1;
				packet_point2->bank_pin[4] = 0xAF;
				packet_point2->bank_pin[5] = 0x9E;
				packet_point2->bank_pin[6] = 0x16;
				packet_point2->bank_pin[7] = 0x37;
				memcpy(buf + buf_length, packet_point2->bank_pin, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->card_id);
				memcpy(buf + buf_length, packet_point2->card_id, _length);
			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				memcpy(packet_point2->bank_account, pNode->BankCardNo, sizeof(packet_point2->bank_account));
				sprintf(msg, "%d", pNode->RecvNo);			// ��Ҫ��������ˮ��
				memset(packet_point2->trans_serail, 0x20, sizeof(packet_point2->trans_serail));
				memcpy(packet_point2->trans_serail, msg, strlen(msg));
				
				// ������ĳ���
				req_packet_length = sizeof(packet_point2->ynnh_head) + sizeof(packet_point2->bank_account) + sizeof(packet_point2->trans_serail);
				
				memset(packet_point2->ynnh_head.packet_length, 0x20, sizeof(packet_point2->ynnh_head.packet_length));
				sprintf(str_length, "%d", req_packet_length);
				memcpy(packet_point2->ynnh_head.packet_length, str_length, strlen(str_length));

				// ѹ���ͷ����
				_length = sizeof(packet_point2->ynnh_head);
				memcpy(buf + buf_length, &(packet_point2->ynnh_head), _length);
				// ѹ���������
				buf_length += _length;
				_length = sizeof(packet_point2->bank_account);
				memcpy(buf + buf_length, packet_point2->bank_account, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->trans_serail);
				memcpy(buf + buf_length, packet_point2->trans_serail, _length);
			}
			else
			{
				NULL;
			}
			
			return 0;
		}
		// ����������
		else if (BANK_HRBZH == bank_id)
		{
			packet_point3 = (BANK_HRBZH_TRADE_STRUCT_PACKET *)packet;
			memcpy(packet_point3->hrbzh_head.Prccde, "010000", sizeof(packet_point3->hrbzh_head.Prccde));
			memcpy(packet_point3->hrbzh_head.AcqInstID, "24650000", sizeof(packet_point3->hrbzh_head.AcqInstID));
			memcpy(packet_point3->hrbzh_head.TermID, "24650000", sizeof(packet_point3->hrbzh_head.TermID));
			memcpy(packet_point3->hrbzh_head.Trcno, "000000", sizeof(packet_point3->hrbzh_head.Trcno));			// ��ˮ��			
			memcpy(packet_point3->hrbzh_head.Cusidt, pNode->BankCardNo, strlen(pNode->BankCardNo));
			memcpy(packet_point3->hrbzh_head.Apcode, "21", sizeof(packet_point3->hrbzh_head.Apcode));
			memcpy(packet_point3->hrbzh_head.SrvuID, "00246500", sizeof(packet_point3->hrbzh_head.SrvuID));
			memcpy(packet_point3->hrbzh_head.Rspcde, "00", sizeof(packet_point3->hrbzh_head.Rspcde));
			memcpy(packet_point3->hrbzh_head.PKseq, "00", sizeof(packet_point3->hrbzh_head.PKseq));
			memcpy(packet_point3->hrbzh_head.Filler, "000000", sizeof(packet_point3->hrbzh_head.Filler));
			memcpy(packet_point3->hrbzh_head.MsgLen, "0000", sizeof(packet_point3->hrbzh_head.MsgLen));
			memcpy(packet_point3->hrbzh_head.Custype, "01", sizeof(packet_point3->hrbzh_head.Custype));

			getsysdate(pNode->BankDate);
			getsystime(pNode->BankTime);
			memcpy(packet_point3->hrbzh_trade_packet.account_id, pNode->BankCardNo, strlen(pNode->BankCardNo));		
			memcpy(packet_point3->hrbzh_trade_packet.process_code, "010000", sizeof(packet_point3->hrbzh_trade_packet.process_code));
			memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, pNode->BankDate + 4, 4);
			memcpy(packet_point3->hrbzh_trade_packet.trans_date_time + 4, pNode->BankTime, sizeof(pNode->BankTime));
			memset(packet_point3->hrbzh_trade_packet.stan, 0x30, sizeof(packet_point3->hrbzh_trade_packet.stan));
			memcpy(packet_point3->hrbzh_trade_packet.time_trans, pNode->BankTime, sizeof(pNode->BankTime));

			memcpy(packet_point3->hrbzh_trade_packet.date_trans, pNode->BankDate + 4, sizeof(packet_point3->hrbzh_trade_packet.date_trans));
			memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, "24", sizeof(packet_point3->hrbzh_trade_packet.point_of_scc));
			memcpy(packet_point3->hrbzh_trade_packet.aiic, "24650000", 8);
			memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, "21045201", 8);
			memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, "000000000000000", 15);
			memset(packet_point3->hrbzh_trade_packet.pid_data, 0x20, sizeof(packet_point3->hrbzh_trade_packet.pid_data));
			memcpy(packet_point3->hrbzh_trade_packet.pid_data, pNode->BankCardPwd, strlen(pNode->BankCardPwd));

			if (BANK_TRADE_CODE_SIGN_IN == trade_type)
			{
				memcpy(packet_point3->hrbzh_head.MsgType, BANK_HRBZH_TRADE_CODE_SIGN_IN, sizeof(packet_point3->hrbzh_head.MsgType));
				memcpy(packet_point3->hrbzh_trade_packet.msg_type_id, BANK_HRBZH_TRADE_CODE_SIGN_IN, sizeof(packet_point3->hrbzh_trade_packet.msg_type_id));
				//memcpy(all_bit_map, "01000111000111000000000010000001000000000000001100001000000000000000000000000000000000000000000000000000000000000000000000000000", sizeof(all_bit_map) - 1);
				//sprintf(packet_point3->hrbzh_trade_packet.stan, "%06d", local_serial);
				
				_length = sizeof(packet_point3->hrbzh_head);
				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.msg_type_id, packet_length);

				_length += packet_length;
				packet_point3->hrbzh_trade_packet.bit_map[0] = 0x62;
				packet_point3->hrbzh_trade_packet.bit_map[1] = 0x38;
				packet_point3->hrbzh_trade_packet.bit_map[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[3] = 0x81;
				packet_point3->hrbzh_trade_packet.bit_map[4] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[5] = 0xc0;
				packet_point3->hrbzh_trade_packet.bit_map[6] = 0x10;
				packet_point3->hrbzh_trade_packet.bit_map[7] = 0x00;

				packet_length = 8;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.bit_map, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%02d", strlen(pNode->BankCardNo));
				writelog(LOG_ERR, "account length=[%d]", strlen(pNode->BankCardNo));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.account_id, strlen(pNode->BankCardNo));
				_length += strlen(pNode->BankCardNo);

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.process_code, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_date_time, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.stan, packet_length);
				_length += packet_length;

//				writelog(LOG_ERR, "time1 =[%6.6s], time2 = [%6.6s]", packet_point3->hrbzh_trade_packet.time_trans, pNode->BankTime);
				packet_length = 6;
				memcpy(buf + _length, pNode->BankTime, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.date_trans, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.point_of_scc, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.aiic));
				writelog(LOG_ERR, "aiic length = [%d]", strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.aiic, strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += strlen(packet_point3->hrbzh_trade_packet.aiic);

				packet_length = 8;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_terminal_id, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_Id, packet_length);
				_length += packet_length;

				packet_length = 16;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.pid_data, packet_length);
				_length += packet_length;

				local_serial++;
			}
			else if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				memcpy(packet_point3->hrbzh_head.MsgType, BANK_HRBZH_TRADE_CODE_QUERYBALANCE, sizeof(packet_point3->hrbzh_head.MsgType));
				memcpy(packet_point3->hrbzh_trade_packet.msg_type_id, BANK_HRBZH_TRADE_CODE_QUERYBALANCE, sizeof(packet_point3->hrbzh_trade_packet.msg_type_id));
				//memcpy(all_bit_map, "01000111000111000000000010000001000000010000001100000000000000000000000000000000000000000000000000000000000000000000000000000000", sizeof(all_bit_map) - 1);
				memcpy(packet_point3->hrbzh_head.Prccde, "316500", sizeof(packet_point3->hrbzh_head.Prccde));
				memcpy(packet_point3->hrbzh_head.AcqInstID, "NT246501", sizeof(packet_point3->hrbzh_head.AcqInstID));
				memcpy(packet_point3->hrbzh_head.TermID, "NT246501", sizeof(packet_point3->hrbzh_head.TermID));
				memcpy(packet_point3->hrbzh_head.Apcode, "01", sizeof(packet_point3->hrbzh_head.Apcode));
				memcpy(packet_point3->hrbzh_head.SrvuID, "01420000", sizeof(packet_point3->hrbzh_head.SrvuID));
				memcpy(packet_point3->hrbzh_trade_packet.process_code, "316500", sizeof(packet_point3->hrbzh_trade_packet.process_code));
				sprintf(msg, "%d", serial_no);
				memcpy(packet_point3->hrbzh_trade_packet.stan, msg, strlen(msg));
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, pNode->BankDate, sizeof(pNode->BankDate));
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time + sizeof(pNode->BankDate), pNode->BankTime, 2);
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, "20", sizeof(packet_point3->hrbzh_trade_packet.point_of_scc));
				memcpy(packet_point3->hrbzh_trade_packet.aiic, "NT246501", 8);
				memcpy(packet_point3->hrbzh_trade_packet.css_id, "NT246501", 8);
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, "NT246501", 8);
			
				_length = sizeof(packet_point3->hrbzh_head);
				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.msg_type_id, packet_length);
				_length += packet_length;
				packet_point3->hrbzh_trade_packet.bit_map[0] = 0x62;
				packet_point3->hrbzh_trade_packet.bit_map[1] = 0x38;
				packet_point3->hrbzh_trade_packet.bit_map[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[3] = 0x81;
				packet_point3->hrbzh_trade_packet.bit_map[4] = 0x80;
				packet_point3->hrbzh_trade_packet.bit_map[5] = 0xc0;
				packet_point3->hrbzh_trade_packet.bit_map[6] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[7] = 0x00;
				packet_length = 8;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.bit_map, packet_length);
				_length += packet_length;
				sprintf(buf + _length, "%02d", strlen(pNode->BankCardNo));
				writelog(LOG_ERR, "account length=[%d]", strlen(pNode->BankCardNo));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.account_id, strlen(pNode->BankCardNo));
				_length += strlen(pNode->BankCardNo);
				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.process_code, packet_length);
				_length += packet_length;
				packet_length = 10;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_date_time, packet_length);
				_length += packet_length;
				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.stan, packet_length);
				_length += packet_length;
				packet_length = 6;
				memcpy(buf + _length, pNode->BankTime, packet_length);
				_length += packet_length;
				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.date_trans, packet_length);
				_length += packet_length;
				packet_length = 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.point_of_scc, packet_length);
				_length += packet_length;
				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.aiic));
				writelog(LOG_ERR, "aiic length = [%d]", strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.aiic, strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += strlen(packet_point3->hrbzh_trade_packet.aiic);
				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.css_id));
				writelog(LOG_ERR, "css_id length = [%d]", strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.css_id, strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += strlen(packet_point3->hrbzh_trade_packet.css_id);
				packet_length = 8;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_terminal_id, packet_length);
				_length += packet_length;
				packet_length = 15;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_Id, packet_length);
				_length += packet_length;
			}
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				sprintf(msg, "%06d", serial_no);
				writelog(LOG_ERR, "serial no = [%d], msg = [%s]", serial_no, msg);
				memcpy(packet_point3->hrbzh_head.MsgType, BANK_HRBZH_TRADE_CODE_TRANS, sizeof(packet_point3->hrbzh_head.MsgType));
				memcpy(packet_point3->hrbzh_trade_packet.msg_type_id, BANK_HRBZH_TRADE_CODE_TRANS, sizeof(packet_point3->hrbzh_trade_packet.msg_type_id));
//				memcpy(all_bit_map, "01000111000111000000000010000001000000011100001100010000000000000000000000000000000000000000000001100000000000000000000000000000", sizeof(all_bit_map) - 1);
				memcpy(packet_point3->hrbzh_head.Prccde, "280011", sizeof(packet_point3->hrbzh_head.Prccde));
				memcpy(packet_point3->hrbzh_head.AcqInstID, "24650000", sizeof(packet_point3->hrbzh_head.AcqInstID));
				memcpy(packet_point3->hrbzh_head.TermID, "24650000", sizeof(packet_point3->hrbzh_head.TermID));
				memcpy(packet_point3->hrbzh_head.Trcno, msg, strlen(msg));
				memcpy(packet_point3->hrbzh_head.Apcode, "01", sizeof(packet_point3->hrbzh_head.Apcode));
				memcpy(packet_point3->hrbzh_head.SrvuID, "00246500", sizeof(packet_point3->hrbzh_head.SrvuID));

				memset(packet_point3->hrbzh_trade_packet.account_id, '8', 19);	
				memcpy(packet_point3->hrbzh_trade_packet.process_code, "280011", sizeof(packet_point3->hrbzh_trade_packet.process_code));
				memset(packet_point3->hrbzh_trade_packet.trans_amount, 0x30, sizeof(packet_point3->hrbzh_trade_packet.trans_amount));
				memcpy(packet_point3->hrbzh_trade_packet.trans_amount + sizeof(packet_point3->hrbzh_trade_packet.trans_amount) - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));	
				memcpy(packet_point3->hrbzh_trade_packet.stan, msg, strlen(msg));
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, "24", sizeof(packet_point3->hrbzh_trade_packet.point_of_scc));
				memcpy(packet_point3->hrbzh_trade_packet.flush_trade_serial_no, msg, sizeof(packet_point3->hrbzh_trade_packet.flush_trade_serial_no));
				memcpy(packet_point3->hrbzh_trade_packet.aiic, "24650000", 8);
				memcpy(packet_point3->hrbzh_trade_packet.css_id, "00246500", 8);
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, "21441181", 8);
				memset(packet_point3->hrbzh_trade_packet.acceptor_Id, 0x20, 15);
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, "00246500", 8);
				packet_point3->hrbzh_trade_packet.encrypt_pwd[0] = '0';
				memcpy(packet_point3->hrbzh_trade_packet.encrypt_pwd + 1, pNode->BankCardPwd, strlen(pNode->BankCardPwd));
				memset(packet_point3->hrbzh_trade_packet.reserve_id1, 0x20, 12);
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 12, "20021211", 8);
				memset(packet_point3->hrbzh_trade_packet.reserve_id1 + 20, 0x20, 14);
				if (0 == memcmp(pNode->BankCardNo, "601382", 6))
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "OD", 2);
				}
				else if (0 == memcmp(pNode->BankCardNo, "456351", 6))
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "OV", 2);
				}
				else
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "01", 2);
				}
//				memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "01", 2);
				memset(packet_point3->hrbzh_trade_packet.reserve_id1 + 36, 0x20, 50);
				memset(packet_point3->hrbzh_trade_packet.reserve_id2, 0x30, 8);
				memset(packet_point3->hrbzh_trade_packet.reserve_id2 + 8, 0x20, 8);
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3, "21045101", 8);
				memset(packet_point3->hrbzh_trade_packet.reserve_id3 + 8, 0x20, 20);
//				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3 + 20 - strlen(pNode->CardNo), pNode->CardNo, strlen(pNode->CardNo));
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3 + 8, pNode->CardNo, strlen(pNode->CardNo));
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id4, pNode->BankCardNo, strlen(pNode->BankCardNo));

				_length = sizeof(packet_point3->hrbzh_head);
				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.msg_type_id, packet_length);
				_length += packet_length;
				packet_point3->hrbzh_trade_packet.bit_map[0] = 0xF2;
				packet_point3->hrbzh_trade_packet.bit_map[1] = 0x38;
				packet_point3->hrbzh_trade_packet.bit_map[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[3] = 0x91;
				packet_point3->hrbzh_trade_packet.bit_map[4] = 0x80;
				packet_point3->hrbzh_trade_packet.bit_map[5] = 0xc3;
				packet_point3->hrbzh_trade_packet.bit_map[6] = 0x08;
				packet_point3->hrbzh_trade_packet.bit_map[7] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[0] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[1] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[3] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[4] = 0x06;
				packet_point3->hrbzh_trade_packet.bit_map_ext[5] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[6] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[7] = 0x00;
				packet_length = 16;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.bit_map, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%02d", strlen(pNode->BankCardNo));
				writelog(LOG_ERR, "account length=[%d]", strlen(pNode->BankCardNo));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.account_id, strlen(pNode->BankCardNo));
				_length += strlen(pNode->BankCardNo);

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.process_code, packet_length);
				_length += packet_length;

				packet_length = 12;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_amount, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_date_time, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.stan, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, pNode->BankTime, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.date_trans, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.point_of_scc, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.flush_trade_serial_no, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.aiic));
				writelog(LOG_ERR, "aiic length = [%d]", strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.aiic, strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += strlen(packet_point3->hrbzh_trade_packet.aiic);

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.css_id));
				writelog(LOG_ERR, "css_id length = [%d]", strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.css_id, strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += strlen(packet_point3->hrbzh_trade_packet.css_id);

				packet_length = 8;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_terminal_id, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_Id, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%03d", strlen(packet_point3->hrbzh_trade_packet.encrypt_pwd));
				writelog(LOG_ERR, "encrypt_pwd length = [%d]", strlen(packet_point3->hrbzh_trade_packet.encrypt_pwd));
				_length += 3;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.encrypt_pwd, strlen(packet_point3->hrbzh_trade_packet.encrypt_pwd));
				_length += strlen(packet_point3->hrbzh_trade_packet.encrypt_pwd);

				sprintf(buf + _length, "%03d", strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				writelog(LOG_ERR, "reserve_id1 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				_length += 3;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id1, strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				_length += strlen(packet_point3->hrbzh_trade_packet.reserve_id1);

				packet_length = 16;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id2, packet_length);
				_length += packet_length;

				// ����28���ֽ�
				sprintf(buf + _length, "%02d", sizeof(packet_point3->hrbzh_trade_packet.reserve_id3));
//				writelog(LOG_ERR, "reserve_id3 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id3));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id3, sizeof(packet_point3->hrbzh_trade_packet.reserve_id3));
				_length += sizeof(packet_point3->hrbzh_trade_packet.reserve_id3);

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				writelog(LOG_ERR, "reserve_id4 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id4, strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				_length += strlen(packet_point3->hrbzh_trade_packet.reserve_id4);

			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				memcpy(packet_point3->hrbzh_head.MsgType, BANK_HRBZH_TRADE_CODE_DETRANS, sizeof(packet_point3->hrbzh_head.MsgType));
				memcpy(packet_point3->hrbzh_trade_packet.msg_type_id, BANK_HRBZH_TRADE_CODE_DETRANS, sizeof(packet_point3->hrbzh_trade_packet.msg_type_id));
//				memcpy(all_bit_map, "01001111000111000000000010001001000000010000001100000000000000000000000000000000000000000000001000100000000000000000000000000000", sizeof(all_bit_map) - 1);		
				memcpy(packet_point3->hrbzh_head.Prccde, "280011", sizeof(packet_point3->hrbzh_head.Prccde));
				memcpy(packet_point3->hrbzh_head.AcqInstID, "24650000", sizeof(packet_point3->hrbzh_head.AcqInstID));
				memcpy(packet_point3->hrbzh_head.TermID, "21045101", sizeof(packet_point3->hrbzh_head.TermID));
				memcpy(packet_point3->hrbzh_trade_packet.process_code, "280011", sizeof(packet_point3->hrbzh_trade_packet.process_code));
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, "22", sizeof(packet_point3->hrbzh_trade_packet.point_of_scc));
				sprintf(packet_point3->hrbzh_trade_packet.flush_trade_serial_no, "%06d", pNode->RecvNo);
				sprintf(pNode->TransMoney, "%d", atoi(trim(pNode->TransMoney)) * 100);
				writelog(LOG_ERR, "transfer money = [%s], flush serial_no = [%d]", pNode->TransMoney, pNode->RecvNo);
				memset(packet_point3->hrbzh_trade_packet.trans_amount, 0x30, sizeof(packet_point3->hrbzh_trade_packet.trans_amount));
				memcpy(packet_point3->hrbzh_trade_packet.trans_amount + sizeof(packet_point3->hrbzh_trade_packet.trans_amount) - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));

				memcpy(packet_point3->hrbzh_trade_packet.aiic, "24650000", 8);
				writelog(LOG_ERR, "hrbzh trade packet aiic = [%s], length = [%d]",packet_point3->hrbzh_trade_packet.aiic, strlen(packet_point3->hrbzh_trade_packet.aiic));
				memcpy(packet_point3->hrbzh_trade_packet.css_id, "00246500", 8);
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, "21441181", 8);
				memset(packet_point3->hrbzh_trade_packet.acceptor_Id, 0x20, 15);
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, "00246500", 8);
				
				memset(packet_point3->hrbzh_trade_packet.reserve_id1, 0x20, 12);
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 12, "20021211", 8);
				memset(packet_point3->hrbzh_trade_packet.reserve_id1 + 20, 0x20, 14);
				if (0 == memcmp(pNode->BankCardNo, "601382", 6))
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "OD", 2);
				}
				else if (0 == memcmp(pNode->BankCardNo, "456351", 6))
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "OV", 2);
				}
				else
				{
					memcpy(packet_point3->hrbzh_trade_packet.reserve_id1 + 34, "01", 2);
				}
				memset(packet_point3->hrbzh_trade_packet.reserve_id1 + 36, 0x20, 50);

				memset(packet_point3->hrbzh_trade_packet.reserve_id2, 0x20, sizeof(packet_point3->hrbzh_trade_packet.reserve_id2));
				
				memset(packet_point3->hrbzh_trade_packet.original_data, 0x20, sizeof(packet_point3->hrbzh_trade_packet.original_data));
				memcpy(packet_point3->hrbzh_trade_packet.original_data + 4, packet_point3->hrbzh_trade_packet.flush_trade_serial_no, sizeof(packet_point3->hrbzh_trade_packet.flush_trade_serial_no));
				
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3, "21045101", 8);
				memset(packet_point3->hrbzh_trade_packet.reserve_id3 + 8, 0x20, 20);
				trim(pNode->CardNo);
				writelog(LOG_ERR, "detrans card no = [%s]", pNode->CardNo);
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3 + 8, pNode->CardNo, strlen(pNode->CardNo));
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id4, pNode->BankCardNo, strlen(pNode->BankCardNo));
				
				_length = sizeof(packet_point3->hrbzh_head);
				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.msg_type_id, packet_length);
				_length += packet_length;
				packet_point3->hrbzh_trade_packet.bit_map[0] = 0xF2;
				packet_point3->hrbzh_trade_packet.bit_map[1] = 0x38;
				packet_point3->hrbzh_trade_packet.bit_map[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map[3] = 0x91;
				packet_point3->hrbzh_trade_packet.bit_map[4] = 0x80;
				packet_point3->hrbzh_trade_packet.bit_map[5] = 0xc1;
				packet_point3->hrbzh_trade_packet.bit_map[6] = 0x08;
				packet_point3->hrbzh_trade_packet.bit_map[7] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[0] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[1] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[2] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[3] = 0x40;
				packet_point3->hrbzh_trade_packet.bit_map_ext[4] = 0x06;
				packet_point3->hrbzh_trade_packet.bit_map_ext[5] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[6] = 0x00;
				packet_point3->hrbzh_trade_packet.bit_map_ext[7] = 0x00;
				packet_length = 16;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.bit_map, packet_length);
				_length += packet_length;
				sprintf(buf + _length, "%02d", strlen(pNode->BankCardNo));
				writelog(LOG_ERR, "account length=[%d]", strlen(pNode->BankCardNo));

				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.account_id, strlen(pNode->BankCardNo));
				_length += strlen(pNode->BankCardNo);

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.process_code, packet_length);
				_length += packet_length;

				packet_length = 12;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_amount, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.trans_date_time, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.stan, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, pNode->BankTime, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.date_trans, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.point_of_scc, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.flush_trade_serial_no, packet_length);
				_length += packet_length;

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.aiic));
				writelog(LOG_ERR, "aiic length = [%d]", strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.aiic, strlen(packet_point3->hrbzh_trade_packet.aiic));
				_length += strlen(packet_point3->hrbzh_trade_packet.aiic);

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.css_id));
				writelog(LOG_ERR, "css_id length = [%d]", strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.css_id, strlen(packet_point3->hrbzh_trade_packet.css_id));
				_length += strlen(packet_point3->hrbzh_trade_packet.css_id);

				packet_length = 8;			// ����41����8���ֽ�,����ǿ��Ҫ������ֻ��д2���ֽ�,�����������
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_terminal_id, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.acceptor_Id, packet_length);
				_length += packet_length;
				
				sprintf(buf + _length, "%03d", strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				writelog(LOG_ERR, "reserve_id1 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				_length += 3;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id1, strlen(packet_point3->hrbzh_trade_packet.reserve_id1));
				_length += strlen(packet_point3->hrbzh_trade_packet.reserve_id1);

				// ��Ϊ����λͼ�����ԭ���������53����д16���ո�
				packet_length = 16;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id2, packet_length);
				_length += packet_length;
				
				packet_length = 42;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.original_data, packet_length);
				_length += packet_length;

				// ����28���ֽ�
				sprintf(buf + _length, "%02d", sizeof(packet_point3->hrbzh_trade_packet.reserve_id3));
//				writelog(LOG_ERR, "reserve_id3 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id3));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id3, sizeof(packet_point3->hrbzh_trade_packet.reserve_id3));
				_length += sizeof(packet_point3->hrbzh_trade_packet.reserve_id3);

				sprintf(buf + _length, "%02d", strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				writelog(LOG_ERR, "reserve_id4 length = [%d]", strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				_length += 2;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.reserve_id4, strlen(packet_point3->hrbzh_trade_packet.reserve_id4));
				_length += strlen(packet_point3->hrbzh_trade_packet.reserve_id4);
			}
			else 
			{
				return 0;
			}
			/*
			_length = sizeof(packet_point3->hrbzh_head);
			writelog(LOG_ERR, "hrbzh_head_length=[%d]", _length);
			for (int m = 0; m < 128; m++) 
			{ 
				Tbl8583[m].data = NULL;
				Tbl8583[m].length_in_byte = 0;
			}
			// set all bit map
			Set8583BitMap((char *)bcd_bit, FIELD1, FIELD2, FIELD3, FIELD4, FIELD7, FIELD11, FIELD12, FIELD13, FIELD17, FIELD25, FIELD28, FIELD32, FIELD33, FIELD39, FIELD41, FIELD42, FIELD47, FIELD48, FIELD52, FIELD53, FIELD90, FIELD102, FIELD103, 0);
			memcpy(packet_point3->hrbzh_trade_packet.bit_map, bcd_bit, 16);
			
			ret = ChangePacktTo8583((char *)packet_point3 + _length, Tbl8583, XCHANGE_IN);
			if (ret) 
			{ 
				writelog(LOG_ERR, "Func ChangePacktTo8583 Errcode=[%d]", ret);
				return ret; 
			}

			// set send bit map
			memset(bcd_bit, 0, sizeof(bcd_bit));
			ChangeBitBuf(all_bit_map, (char *)bcd_bit, XCHANGE_IN);
			memcpy(packet_point3->hrbzh_trade_packet.bit_map, bcd_bit, 16);
			ret = Change8583ToBuf(Tbl8583, buf + _length, XCHANGE_IN);
			if (ret) 
			{ 
				writelog(LOG_ERR, "Func Change8583ToBuf Errcode=[%d]", ret);
				return ret; 
			}

			Get8583DataLength((char *)bcd_bit, Tbl8583, &packet_length);
			*/
//			writelog(LOG_ERR, "hrbzh_packet_length=[%d]", (_length - sizeof(packet_point3->hrbzh_head)));
			sprintf(packet_point3->hrbzh_head.MsgLen, "%04d", _length - sizeof(packet_point3->hrbzh_head));																	// head
			sprintf(packet_point3->hrbzh_head.AllPacketLen, "%04d", _length - sizeof(packet_point3->hrbzh_head.AllPacketLen));			// head + packet_length
			packet_point3->hrbzh_head.PKgtype[0] = '0';
			memcpy(buf, &packet_point3->hrbzh_head, sizeof(packet_point3->hrbzh_head));
//			packet_length += sizeof(packet_point3->hrbzh_trade_packet.msg_type_id);
//			memcpy(buf + _length, packet_point3->hrbzh_trade_packet.msg_type_id, 4);																						// msg type											
//			writelog(LOG_ERR, "hrbzh_packet_length=[%d]", packet_length);
//			sprintf(packet_point3->hrbzh_head.MsgLen, "%04d", packet_length);
//			sprintf(packet_point3->hrbzh_head.AllPacketLen, "%04d", packet_length + _length);		
//			writelog(LOG_ERR, "pk type = [%d]", packet_point3->hrbzh_head.PKgtype[0]);
		}
		else
		{
			return 0;
		}
	}
	// �����������������
	else if (BUF_TO_PACKET == change_flag)
	{
		// �ź�����
		if (BANK_YNXH == bank_id)
		{
			packet_point = (BANK_YNXH_TRADE_STRUCT_PACKET *)packet;
			buf_length = 0;
			packet_length = 1;
			memcpy(packet_point->head.packet_head_length, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.head_flag, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 4;
			memcpy(packet_point->head.packet_length, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 11;
			memcpy(packet_point->head.dest_id, buf + buf_length, packet_length);			// buf + 6
			buf_length += packet_length;
			packet_length = 11;
			memcpy(packet_point->head.src_id, buf + buf_length, packet_length);			// buf + 17
			buf_length += packet_length;
			packet_length = 3;
			memcpy(packet_point->head.reserve_1, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.batch_no, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 8;
			memcpy(packet_point->head.trade_info, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.user_info, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 5;
			memcpy(packet_point->head.reject_code, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 4;
			memcpy(packet_point->msg_type, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 16;
			memcpy(packet_point->bit, buf + buf_length, packet_length);
			buf_length += packet_length;
			// ��ѯ���Ӧ��
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xE2)
				{
					writelog(LOG_ERR,"error byte0--[%d]\n", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]\n", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]\n", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]\n", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]\n", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]\n", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x84)
				{
					writelog(LOG_ERR,"error byte6--[%d]\n", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]\n", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]\n", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]\n", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]\n", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]\n", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)		
				{
					writelog(LOG_ERR,"error byte12--[%d]\n", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]\n", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]\n", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]\n", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}

				memcpy(str_length, buf + 66, 2);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				memcpy(packet_point->main_account, buf + 66, atoi(str_length) + 2);
				_length = strlen(packet_point->main_account);
				memcpy(packet_point->trade_deal_code, buf + 66 + _length, 6);
				memcpy(packet_point->trade_deal_time, buf + 72 + _length, 10);
				memcpy(packet_point->system_id, buf + 82 + _length, 6);
				memcpy(packet_point->accept_card_time, buf + 88 + _length, 6);
				memcpy(packet_point->accept_card_date, buf + 94 + _length, 4);
				memcpy(packet_point->shop_type, buf + 98 + _length, 4);
				memcpy(packet_point->service_input_code, buf + 102 + _length, 3);
				memcpy(packet_point->service_terms_code, buf + 105 + _length, 2);
				memcpy(str_length, buf + 107 + _length, 2);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->proxy_node_code, buf + 107 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->proxy_node_code);
				memcpy(str_length, buf + 107 + _length, 2);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->send_node_code, buf + 107 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->send_node_code);
				memcpy(packet_point->check_code, buf + 107 + _length, 12);
				memcpy(packet_point->answser_code, buf + 119 + _length, 2);
				memcpy(packet_point->device_phy, buf + 121 + _length, 8);
				memcpy(packet_point->mark, buf + 129 + _length, 15);
				memcpy(packet_point->address, buf + 144 + _length, 40);
				memcpy(str_length, buf + 184 + _length, 3);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				memcpy(packet_point->append_data, buf + 184 + _length, atoi(str_length) + 3);
				_length += strlen(packet_point->append_data);
				memcpy(packet_point->trade_money_code, buf + 184 + _length, 3);
//				memcpy(str_length, buf + 187 + _length, 3);	// ���ֶεĳ���
//				printf("cur_balance length[%d]\n", atoi(str_length));
				memcpy(packet_point->cur_balance, buf + 187 + _length, 43);
				memcpy(str_length, buf + 230 + _length, 3);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				memcpy(packet_point->defalut_area, buf + 230 + _length, atoi(str_length) + 3);
				_length += strlen(packet_point->defalut_area);
				memset(str_length, 0, sizeof(str_length));
				memcpy(str_length, buf + 230 + _length, 2);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->accept_node_code, buf + 230 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->accept_node_code);
				memcpy(packet_point->packet_identity_code, buf + 230 + _length, 8);

				Trace_Bank_Package_YNXH(packet_point, "receivce query bank package");		// ������
				// ��ȡӦ���, �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
	//			strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE, 4);
	//			strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->cur_balance, SPLIT_VL);
				
				Caculate_String_MAC(packet_str, prs_next, mac);
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}
				
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x80)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
		
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->main_account, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->trade_deal_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->trade_money, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->accept_card_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->accept_card_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->service_input_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->service_terms_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->trade_money_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->defalut_area, buf + buf_length, packet_length);
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);

				// �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_TRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_TRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}

				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x80)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->main_account, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->trade_deal_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->trade_money, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->accept_card_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->accept_card_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->service_input_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->service_terms_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->trade_money_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->defalut_area, buf + buf_length, packet_length);
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);			
				
				// �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_DETRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_DETRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				Caculate_String_MAC(packet_str, prs_next, mac);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_ERR,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}

				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));	
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_COMPARE == trade_type)
			{
				if ((unsigned char)packet_point->bit[0] != 0x8A)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x22)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x40)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x01)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x40)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x80)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x04)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 12;
				memcpy(packet_point->liq_money, buf + buf_length, packet_length);			// ������
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->liquidate_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->liq_cur_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_trade_info length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_trade_info, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->transfer_count, buf + buf_length, packet_length);		// ת�ʱ���
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code [%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);
			}
			else 
			{
				NULL;
			}
		}
		// ����ũ�в�ѯ����
		else if (BANK_YNNH == bank_id)
		{
			// ��ѯ���, ���ð�ͷ
			packet_point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)packet;
			// ����ͷ��
			memcpy(&(packet_point2->ynnh_head), buf, sizeof(packet_point2->ynnh_head));
			buf_length += sizeof(packet_point2->ynnh_head);
//			printf("ynnh head=[%d]--buf_length=[%d]\n", sizeof(packet_point2->ynnh_head), buf_length);

			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				// ����ĸ���
				_length = sizeof(packet_point2->account_money);
				memcpy(packet_point2->bank_account, buf + buf_length, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->trade_money);
				memcpy(packet_point2->remain_money, buf + buf_length, _length);
			}
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				// Ȧ��ת��, ���ð�ͷ
				packet_point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)packet;
				// ����ͷ��
				memcpy(&(packet_point2->ynnh_head), buf, sizeof(packet_point2->ynnh_head));
//				buf_length += sizeof(packet_point2->ynnh_head);
			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
			
			}
			
			return 0;
		}
		// ���������з��ذ�
		else if (BANK_HRBZH == bank_id)
		{
			packet_point3 = (BANK_HRBZH_TRADE_STRUCT_PACKET *)packet;
			memcpy(packet_point3, buf, sizeof(packet_point3->hrbzh_head));
			_length = sizeof(packet_point3->hrbzh_head);
			memcpy(packet_point3->hrbzh_trade_packet.msg_type_id, buf + _length, MSG_LENGTH);				// ��Ϣ����			
			_length += MSG_LENGTH;
			if (BANK_TRADE_CODE_SIGN_IN == trade_type)
			{
				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map, buf + _length, packet_length);
				_length += packet_length;

				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[0] != 0x62)
				{
					writelog(LOG_ERR,"error byte0--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[2] != 0x80)
				{
					writelog(LOG_ERR,"error byte2--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[4] != 0x02)
				{
					writelog(LOG_ERR,"error byte4--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[5] != 0xc0)
				{
					writelog(LOG_ERR,"error byte5--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[6] != 0x10)
				{
					writelog(LOG_ERR,"error byte6--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte7--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[7]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.account_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.process_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.stan, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.time_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_capture, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.aiic, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.response_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, buf + _length, packet_length);
				_length += packet_length;
			}
			else if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map, buf + _length, packet_length);
				_length += packet_length;

				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[0] != 0x72)
				{
					writelog(LOG_ERR,"error byte0--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[2] != 0x80)
				{
					writelog(LOG_ERR,"error byte2--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[4] != 0x82)
				{
					writelog(LOG_ERR,"error byte4--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[5] != 0xc0)
				{
					writelog(LOG_ERR,"error byte5--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[6] != 0x00)
				{
					writelog(LOG_ERR,"error byte6--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte7--[%d]\n", packet_point3->hrbzh_trade_packet.bit_map[7]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.account_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.process_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 12;
				memcpy(packet_point3->hrbzh_trade_packet.trans_amount, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.stan, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.time_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_capture, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.aiic, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.css_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.response_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, buf + _length, packet_length);
				_length += packet_length;
			}
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map_ext, buf + _length, packet_length);
				_length += packet_length;

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point3->hrbzh_trade_packet.bit_map[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point3->hrbzh_trade_packet.bit_map[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[2] != 0x80)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point3->hrbzh_trade_packet.bit_map[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[3] != 0x91)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point3->hrbzh_trade_packet.bit_map[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[4] != 0x82)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point3->hrbzh_trade_packet.bit_map[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[5] != 0xc3)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point3->hrbzh_trade_packet.bit_map[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[6] != 0x08)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point3->hrbzh_trade_packet.bit_map[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point3->hrbzh_trade_packet.bit_map[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[0] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[1] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[2] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[3] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[4] != 0x06)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[5] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[6] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[7]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.account_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.process_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 12;
				memcpy(packet_point3->hrbzh_trade_packet.trans_amount, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.stan, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.time_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_capture, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(buf + _length, packet_point3->hrbzh_trade_packet.flush_trade_serial_no, packet_length);
				_length += packet_length;
				
				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.aiic, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.css_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.response_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 3;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 3;
				memcpy(packet_point3->hrbzh_trade_packet.encrypt_pwd, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 3;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 3;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id1, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 16;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id2, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id4, buf + _length, packet_length);
				_length += packet_length;
			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.bit_map_ext, buf + _length, packet_length);
				_length += packet_length;

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point3->hrbzh_trade_packet.bit_map[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point3->hrbzh_trade_packet.bit_map[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[2] != 0x80)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point3->hrbzh_trade_packet.bit_map[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[3] != 0x91)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point3->hrbzh_trade_packet.bit_map[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[4] != 0x82)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point3->hrbzh_trade_packet.bit_map[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[5] != 0xc1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point3->hrbzh_trade_packet.bit_map[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[6] != 0x08)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point3->hrbzh_trade_packet.bit_map[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point3->hrbzh_trade_packet.bit_map[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[0] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[1] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[2] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[3] != 0x40)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[4] != 0x06)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[5] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[6] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point3->hrbzh_trade_packet.bit_map_ext[7] != 0x00)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point3->hrbzh_trade_packet.bit_map_ext[7]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.account_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.process_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 12;
				memcpy(packet_point3->hrbzh_trade_packet.trans_amount, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 10;
				memcpy(packet_point3->hrbzh_trade_packet.trans_date_time, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.stan, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.time_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_trans, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 4;
				memcpy(packet_point3->hrbzh_trade_packet.date_capture, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.point_of_scc, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 6;
				memcpy(packet_point3->hrbzh_trade_packet.flush_trade_serial_no, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.aiic, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.css_id, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 2;
				memcpy(packet_point3->hrbzh_trade_packet.response_code, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 8;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_terminal_id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 15;
				memcpy(packet_point3->hrbzh_trade_packet.acceptor_Id, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 3;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 3;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id1, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 16;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id2, buf + _length, packet_length);
				_length += packet_length;
				
				packet_length = 42;
				memcpy(packet_point3->hrbzh_trade_packet.original_data, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				writelog(LOG_ERR,"reserve_id3 packet length = [%d], point length = [%d]", packet_length, _length);	
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id3, buf + _length, packet_length);
				_length += packet_length;

				packet_length = 2;
				memset(packet_str, 0, sizeof(packet_str));
				memcpy(packet_str, buf + _length, packet_length);
				packet_length = atoi(packet_str);
				_length += 2;
				memcpy(packet_point3->hrbzh_trade_packet.reserve_id4, buf + _length, packet_length);
				_length += packet_length;
			}
			else if (BANK_TRADE_CODE_COMPARE == trade_type)
			{
			
			}
			else
			{
				return 0;
			}
			/*
			for (int ii = 0; ii < 128; ii++)
			{
				Tbl8583[ii].data = NULL;
				Tbl8583[ii].length_in_byte = 0;
			}
			ret = Change8583ToBuf(Tbl8583, buf + _length, XCHANGE_OUT);
			if (ret) 
			{ 
				writelog(LOG_ERR, "Func Change8583ToBuf Errcode=[%d]", ret);
				return ret; 
			}

			Set8583BitMap((char *)bcd_bit, FIELD1, FIELD2, FIELD3, FIELD4, FIELD7, FIELD11, FIELD12, FIELD13, FIELD17, FIELD25, FIELD28, FIELD32, FIELD33, FIELD39, FIELD41, FIELD42, FIELD47, FIELD48, FIELD52, FIELD53, FIELD90, FIELD102, FIELD103, 0);
			memcpy(packet_point3->hrbzh_trade_packet.bit_map, bcd_bit, 16);
			ret = ChangePacktTo8583((char *)packet_point3 + _length, Tbl8583, XCHANGE_OUT);
			if (ret)
			{
				writelog(LOG_ERR, "Func ChangePacktTo8583 Errcode=[%d]", ret);
				return ret;
			}
			*/
		}
		else
		{
			NULL;
		}
	}
	else 
	{
		NULL;
	}
	
	return 0;
}

int Get_Bank_Error_Code(void *pTransPak, int bank_id)
{
	
	BANK_YNXH_TRADE_STRUCT_PACKET *point = NULL;
	BANK_YNNH_TRADE_STRUCT_PACKET *point2 = NULL;
	BANK_HRBZH_TRADE_STRUCT_PACKET *point3 = NULL;

	// �����ź�
	if (BANK_YNXH == bank_id)
	{
		point = (BANK_YNXH_TRADE_STRUCT_PACKET *)pTransPak;
		// ��Щ������δ���ṩ, �Ժ�̨��־Ϊ׼
		writelog(LOG_ERR,"reject_code[%s]--answser_code[%s]",point->head.reject_code,point->answser_code);
		if (0 == strcmp(point->answser_code, "00"))
		{
			return 0;
		}
		else if (0 == strcmp(point->answser_code, "01"))
		{
			return E_CONNECT_PUBLISH_BANK;	// ���뷢������ϵ
		}
		else if (0 == strcmp(point->answser_code, "03"))
		{
			return E_INVALID_SHOP;	// ��Ч�̻�
		}
		else if (0 == strcmp(point->answser_code, "05"))
		{
			return E_CVN_FAILED;	// �������
		}
		else if (0 == strcmp(point->answser_code, "06"))
		{
			return E_TRADE_FAILED;	// ���׳���
		}
		else if (0 == strcmp(point->answser_code, "12"))
		{
			return E_INVALIED_TRADE;	// ��Ч����
		}
		else if (0 == strcmp(point->answser_code, "13"))
		{
			return E_INVALIED_MONEY; // ��Ч���
		}
		else if (0 == strcmp(point->answser_code, "56"))
		{
			return E_INVALIED_CARD;	// ��Ч����
		}
		else if (0 == strcmp(point->answser_code, "22"))
		{
			return E_TROUBLE_DOUBT;	// ���ϻ���
		}
		else if (0 == strcmp(point->answser_code, "25"))
		{
			return E_FIND_INIT_TRADE;	// �Ҳ���ԭʼ����
		}
		else if (0 == strcmp(point->answser_code, "40"))
		{
			return E_TRANS_FUNC_NONSUPPORT;	// �����ܲ�֧��
		}
		else if (0 == strcmp(point->answser_code, "41"))
		{
			return E_TRANS_BANKCARD_LOST;	// ��ʧ��
		}
		else if (0 == strcmp(point->answser_code, "42"))
		{
			return E_NO_BANK_ACCOUNT;	// �޴��˻�
		}
		else if (0 == strcmp(point->answser_code, "51"))
		{
			return E_TRANS_BANKACC_NOMONEY;	// �ʽ���
		}
		else if (0 == strcmp(point->answser_code, "54"))
		{
			return E_CARD_OUTOFDATE;	// ���ڿ�
		}
		else if (0 == strcmp(point->answser_code, "55"))
		{
			return E_INVALID_PIN;	// ����ȷ��PIN
		}
		else if (0 == strcmp(point->answser_code, "57"))
		{
			return E_CARDHOLDER_TRADE;	// ������ֿ��˽��н���
		}
		else if (0 == strcmp(point->answser_code, "61"))
		{
			return E_TRANS_TRANSMONEY_OUTRANGE;	// �����������
		}
		else if (0 == strcmp(point->answser_code, "65"))
		{
			return E_OUTOF_TRADE_COUNTS;	// �������״���
		}
		else if (0 == strcmp(point->answser_code, "75"))
		{
			return E_OUTOFPIN_INPUT;	// �������״���
		}
		else if (0 == strcmp(point->answser_code, "90"))
		{
			return E_BANK_SETTLE_ACCOUNTS;	// �������ս���
		}
		else if (0 == strcmp(point->answser_code, "A0"))
		{
			return E_TRANS_BANK_RECVERR;		// ���з������ݳ���
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;	// ��ʱ��֧�ִ˹���
		}
	}
	// ����ũ��
	else if (BANK_YNNH == bank_id)
	{
		point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)pTransPak;
		// ��Щ������δ���ṩ, �Ժ�̨��־Ϊ׼
		writelog(LOG_ERR,"error_code=[%4.4s]", point2->ynnh_head.error_code);
		if (0 == strncmp(point2->ynnh_head.error_code, "0000", sizeof(point2->ynnh_head.error_code)))
		{
			return 0;
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;	// ��ʱ��֧�ִ˹���
		}
	}
	else if (BANK_HRBZH == bank_id)
	{
		point3 = (BANK_HRBZH_TRADE_STRUCT_PACKET *)pTransPak;
		writelog(LOG_ERR, "error_code=[%2.2s]", point3->hrbzh_trade_packet.response_code);
		if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "00", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return 0;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "14", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_BANK_ACCOUNT_LOGOUT;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "Q0", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_BANK_ACCOUNT_TYPE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "Q1", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_BANK_ACCOUNTID_TYPE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "QB", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_NO_BANK_ACCOUNT;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "QK", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_NO_BANK_ACCOUNT;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "QV", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_INVALIED_MONEY;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "R2", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_INVALIED_TRADE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "R7", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_FUNDS_SHORTAGE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "RI", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_BANK_MONEY_UNDER_LOWEST;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "RN", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_BANK_MONEY_UNDER_TRADE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "RP", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_FUNDS_SHORTAGE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "V6", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_CVN_FAILED;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "VC", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_INVALIED_CARD;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "V9", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_TRADE_FAILED;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "1C", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_TRADE_CLOSE;
		}
		else if (0 == strncmp(point3->hrbzh_trade_packet.response_code, "1B", sizeof(point3->hrbzh_trade_packet.response_code)))
		{
			return E_MAIN_SYSTEM_NOT_OPEN;
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	else
	{
		return 0;
	}

	return 0;
}

int Trade_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, int trade_type, int packet_flag, 
							  ST_BANK_CONFIG *pBank, INNER_TRANS_REQUEST * pNode)
{	
	if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
	{
		// ���������
		if (0 == packet_flag)
		{
		}
		else	
		{
			NULL;				// Ӧ���ڴ�ʵ��
		}
	}
	
	return 0;
}

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg)
{
	int count = 1;
	printf("%s\n", msg);
	printf("---------------------------------------------------------------------------\n");

	for	(int jj = 0; jj < _8583_length; jj += 16)
	{
		if (10 == format)
		{
			printf("[%d] BYTE DEC 16 bit %d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d\n", count,
			_8583_buf[jj], _8583_buf[jj + 1], _8583_buf[jj + 2], _8583_buf[jj + 3], _8583_buf[jj + 4], _8583_buf[jj + 5], 
			_8583_buf[jj + 6], _8583_buf[jj + 7], _8583_buf[jj + 8], _8583_buf[jj + 9], _8583_buf[jj + 10], _8583_buf[jj + 11], 
			_8583_buf[jj + 12], _8583_buf[jj + 13], _8583_buf[jj + 14], _8583_buf[jj + 15]);
			count++;
		}
		else
		{
			printf("[%d] BYTE HEX 16 bit %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n", count,
			_8583_buf[jj], _8583_buf[jj + 1], _8583_buf[jj + 2], _8583_buf[jj + 3], _8583_buf[jj + 4], _8583_buf[jj + 5], 
			_8583_buf[jj + 6], _8583_buf[jj + 7], _8583_buf[jj + 8], _8583_buf[jj + 9], _8583_buf[jj + 10], _8583_buf[jj + 11], 
			_8583_buf[jj + 12], _8583_buf[jj + 13], _8583_buf[jj + 14], _8583_buf[jj + 15]);
			count++;
		}
	}
	printf("---------------------------------------------------------------------------\n");

	return ;
}

int Bank_AdjustCompareFile(INNER_TRANS_REQUEST *pNode, ST_BANK *bank, void *var_object1, void *var_object2, void *var_object3)
{
	char path_name[256]="";
	char file_name[256]="";
	char packet_str[516] = "";					// �źϱ����������
	char prs_next[516] = "";					// �źϼ��ܺ����Կ
	char mac[9] = "";							// �źϼ�����mac��Կ
	int ret=0;
	int cnt=0;
	int i=0;
	
	if (BANK_YNXH == bank->iBankID)
	{
		// 1. �Ӵ����bank�л�ȡ�����ļ�·��
		BANK_FILE_ADJUST *file_adjust = (BANK_FILE_ADJUST *)var_object2;

		// 2. �ж�MACֵ, Ч���ļ�
		memset(packet_str, 0, sizeof(packet_str));
//		strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_COMPARE, 4);
//		strcat(packet_str, SPLIT_VL);
		PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_COMPARE, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->liq_money, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->trade_deal_time, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->system_id, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->shop_type, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->service_terms_code, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->proxy_node_code + 2, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->send_node_code + 2, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->answser_code, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->device_phy, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->mark, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->append_trade_info + 3, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->transfer_count, SPLIT_VL);
				
		Caculate_FS_MAC(packet_str, file_adjust->file_path_name, prs_next, mac);		// Ч���Ŀ¼�е��ļ�
		printf("����ֶ�=[%s]--�����ֶ�=[%s]--�ļ�·��=[%s]\n", packet_str, prs_next, file_adjust->file_path_name);
		if (0 != strncmp(file_adjust->packet_identity_code, mac, 8))
		{
			writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, file_adjust->packet_identity_code);
			return E_TRANS_BANK_RECVERR;
		}
	}

	return 0;
}

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet)
{
	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;

	// �������ú�����
	int req_packet_length = 0;					// �ź��������ܳ���
	int ans_packet_length = 0;					// �ź�Ӧ�����ܳ���
	char prs_next[516] = "";					// �źϼ��ܺ����Կ
	char mac[9] = "";							// �źϼ�����mac��Կ
	char packet_str[516] = "";					// �źϱ������ 
	char packet_send_buf[1892] = "";			// ���ͱ���buf
	char packet_recv_buf[1892] = "";			// ���ܱ���buf
	BANK_FILE_ADJUST *file_adjust;				// ��ҪЧ��Ķ����ļ�����
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// ������
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// Ӧ����
	file_adjust = (BANK_FILE_ADJUST*)recv_packet;
	
	if (BANK_YNXH == bank->iBankID)
	{
		// ��Ϸ������ݱ���
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_COMPARE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ����������ݱ���
		Trace_Bank_Package_YNXH(&ynxh_req, "send compare file bank package");
			
		// �������ݱ��ĺͽ���Ӧ�����ݱ���
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, ans_packet_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ���Ӧ�����ݱ���
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_COMPARE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ���Ӧ�����ݱ���
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce compare file bank package");

		// �жϴ�����
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]--card_id=[%s]", g_Bank.BankUnit[i].szBankAccountNO, ret, pNode->CardNo);
			return ret;
		}

		// ���˵�ʱ�����ݰ�, �ȴ�ȡ���ļ������Ч��Ͷ���
		memcpy(file_adjust->liq_money, ynxh_ans.liq_money, sizeof(file_adjust->liq_money) - 1);
		writelog(LOG_ERR, "file_adjust_time=[%s], trade_deal_time=[%s]", file_adjust->trade_deal_time, ynxh_ans.trade_deal_time);
		memcpy(file_adjust->trade_deal_time, ynxh_ans.trade_deal_time, sizeof(file_adjust->trade_deal_time) - 1);
		memcpy(file_adjust->system_id, ynxh_ans.system_id, sizeof(file_adjust->system_id) - 1);
		memcpy(file_adjust->shop_type, ynxh_ans.shop_type, sizeof(file_adjust->shop_type) - 1);
		memcpy(file_adjust->service_terms_code, ynxh_ans.service_terms_code, sizeof(file_adjust->service_terms_code) - 1);
		memcpy(file_adjust->proxy_node_code, ynxh_ans.proxy_node_code, sizeof(file_adjust->proxy_node_code) - 1);
		memcpy(file_adjust->send_node_code, ynxh_ans.send_node_code, sizeof(file_adjust->send_node_code) - 1);
		memcpy(file_adjust->answser_code, ynxh_ans.answser_code, sizeof(file_adjust->answser_code) - 1);
		memcpy(file_adjust->device_phy, ynxh_ans.device_phy, sizeof(file_adjust->device_phy) - 1);
		memcpy(file_adjust->mark, ynxh_ans.mark, sizeof(file_adjust->mark) - 1);
		memcpy(file_adjust->append_trade_info, ynxh_ans.append_trade_info, sizeof(file_adjust->append_trade_info) - 1);	
		memcpy(file_adjust->transfer_count, ynxh_ans.transfer_count, sizeof(file_adjust->transfer_count) - 1);
		memcpy(file_adjust->packet_identity_code, ynxh_ans.packet_identity_code, sizeof(file_adjust->packet_identity_code) - 1);
		memcpy(file_adjust->file_path_name, bank->comp_file_path, sizeof(file_adjust->file_path_name) - 1);
		strcat(file_adjust->file_path_name, file_adjust->append_trade_info + 3);			// �ļ�·�� + �ļ�����
	}
	else
	{
		return 0;
	}

	return 0;
}


