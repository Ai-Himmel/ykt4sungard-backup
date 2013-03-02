#ifndef  __ERRDEF_H_
#define  __ERRDEF_H_

#define E_COMMON_ERR						9999	//
#define E_999_BASE			    390000
#define E_999_0X00                     390000	//�ڿ�����
#define E_999_0X01                     390001	//�Ƿ���
#define E_999_0X02                     390002	//��;�ο�
#define E_999_0X03                     390003	//Ǯ����ʽ��
#define E_999_0X05                     390005	//�޷�д��
#define E_999_0X10                     390016	//�������
#define E_999_0x99			    390153      // ��ȷ
#define E_999_0XA0                     390160	//����ʱ����ڴ�
#define E_999_0XA1                     390161	//��������
#define E_999_0XA2                     390162	//ʱ��������
#define E_999_0XFA                     390250	//��ֵ����
#define E_999_0XFE                     390254	//��������
#define E_999_0XFF			    390255	//���ײ��ɹ�

#define E_999_AMT                      100000	//�ϴ���ˮ���׷����������
#define E_999_CARD_BALANCE    100001	//�ϴ���ˮ���뿨�������
#define E_999_CRC                       100002	//�ϴ���ˮCRCУ�����
#define E_999_DATE                     100003	//�ϴ���ˮ������������
#define E_999_TIME                     100004	//�ϴ���ˮ����ʱ������
#define E_ACTNO_INVALID                 100005	//�˺���Ч
#define E_ACTNO_NOT_EXIST               100006	//�ʺŲ�����
#define E_APP_NO_IS_NULL                100007	//Ӧ�ó�����Ϊ��
#define E_AREA_FIDNULL                  100008	//��������Ϊ��
#define E_AREA_ROOTUNIQUE               100009	//���������и��ڵ�ֻ����һ��
#define E_BALANCE_NOW                   100010	//ϵͳ���ڽ��ʣ��޷�ͬʱ����
#define E_BALANCE_SHORTAGE              100011	//�ʻ�����
#define E_CARDNO_LOST                      100012	//���Ѿ���ʧ
#define E_CARDNORMAL                    100013	//��������״̬,��������ʧ\�˿�����.
#define E_CARDNOTAVAILABILITY           100014	//���Ĺ�ʧ��Ч����δ��,���ܲ���.
#define E_CARDNO_INVALID                100015	//������Ч
#define E_CARDNO_NOT_EXIST              100016	//���Ų�����
#define E_CARDSTATE_NOTWRITEFAIL        100017	//��״̬����д��δ�ɹ�״̬
#define E_CARD_STATE_ERROR              100018	//�˿�״̬����
#define E_CHANGE_FLAG                   100019	//����ȫ�ֽ��ʱ�־����
#define E_CHECK_INITKEY                 100020	//ƥ���ʼ��Կʧ��
#define E_CREATE_SHARE_MEMORY           100021	//���������ڴ�ʧ��
#define E_CUTTYPEFEE_D                  100022	//�ͻ��������ѱ�ɾ������
#define E_CUTTYPEFEE_I                  100023	//�ͻ��������ѱ�������
#define E_CUTTYPEFEE_N                  100024	//�ͻ��������ѱ�����ؼ�¼
#define E_CUTTYPEFEE_R                  100025	//�ͻ��������ѱ��ȡ����
#define E_CUTTYPEFEE_U                  100026	//�ͻ��������ѱ���´���
#define E_CUTTYPE_NOT_EXIST             100027	//�ͻ���𲻴���
#define E_DATE_FMT                      100028	//���ڸ�ʽ����ȷ
#define E_DAYEND_STATUS                 100029	//ϵͳ��������״̬ҵ��ϵͳ������ͣ
#define E_DB_ACCOUNT_D                  100030	//�ʻ���ɾ������
#define E_DB_ACCOUNT_I                  100031	//�ʻ���������
#define E_DB_ACCOUNT_N                  100032	//���ʻ�������ؼ�¼
#define E_DB_ACCOUNT_R                  100033	//�ʻ����ȡ����
#define E_DB_ACCOUNT_U                  100034	//�ʻ�����´���
#define E_DB_ALARMLEVEL_D               100035	//���伶����Ϣ��ɾ������
#define E_DB_ALARMLEVEL_I               100036	//���伶����Ϣ��������
#define E_DB_ALARMLEVEL_N               100037	//���伶����Ϣ���޼�¼
#define E_DB_ALARMLEVEL_R               100038	//���伶����Ϣ�������
#define E_DB_ALARMLEVEL_U               100039	//���伶����Ϣ����´���
#define E_DB_ALARMOP_D                  100040	//���������¼��ɾ������
#define E_DB_ALARMOP_I                  100041	//���������¼��������
#define E_DB_ALARMOP_N                  100042	//���������¼������ؼ�¼
#define E_DB_ALARMOP_R                  100043	//���������¼���ѯ����
#define E_DB_ALARMOP_U                  100044	//���������¼����´���
#define E_DB_ALARM_D                    100045	//������Ϣ��ɾ������
#define E_DB_ALARM_I                    100046	//������Ϣ��������
#define E_DB_ALARM_N                    100047	//������Ϣ���޼�¼
#define E_DB_ALARM_R                    100048	//������Ϣ�������
#define E_DB_ALARM_U                    100049	//������Ϣ����´���
#define E_DB_APP_FUNC_LIST_D            100050	//�������б�ɾ������
#define E_DB_APP_FUNC_LIST_I            100051	//�������б�������
#define E_DB_APP_FUNC_LIST_N            100052	//�������б�����ؼ�¼
#define E_DB_APP_FUNC_LIST_R            100053	//�������б��ѯ����
#define E_DB_APP_FUNC_LIST_U            100054	//�������б���´���
#define E_DB_AREA_D                     100055	//�����ɾ������
#define E_DB_AREA_I                     100056	//�����������
#define E_DB_AREA_N                     100057	//������ѯ����ؼ�¼
#define E_DB_AREA_R                     100058	//������ȡ����
#define E_DB_AREA_U                     100059	//������޸Ĵ���
#define E_DB_AUTHCARD_D                 100060	//��Ȩ����Ϣ��ɾ������
#define E_DB_AUTHCARD_I                 100061	//��Ȩ����Ϣ��������
#define E_DB_AUTHCARD_N                 100062	//��Ȩ����Ϣ������ؼ�¼
#define E_DB_AUTHCARD_R                 100063	//��Ȩ����Ϣ���ѯ����
#define E_DB_AUTHCARD_U                 100064	//��Ȩ����Ϣ����´���
#define E_DB_AUTHEN_LOG_BAK_D           100065	//��֤��ˮ��鵵ɾ������
#define E_DB_AUTHEN_LOG_BAK_I           100066	//��֤��ˮ��鵵�������
#define E_DB_AUTHEN_LOG_BAK_U           100067	//��֤��ˮ��鵵���´���
#define E_DB_BLACK_SHEET_D              100068	//��������ɾ������
#define E_DB_BLACK_SHEET_I              100069	//��������������
#define E_DB_BLACK_SHEET_LOG_D          100070	//��������־��ɾ������
#define E_DB_BLACK_SHEET_LOG_I          100071	//��������־��������
#define E_DB_BLACK_SHEET_LOG_N          100072	//��������־������ؼ�¼
#define E_DB_BLACK_SHEET_LOG_R          100073	//��������־���ѯ����
#define E_DB_BLACK_SHEET_LOG_U          100074	//��������־����´���
#define E_DB_BLACK_SHEET_N              100075	//������������ؼ�¼
#define E_DB_BLACK_SHEET_R              100076	//���������ѯ����
#define E_DB_BLACK_SHEET_U              100077	//����������´���
#define E_DB_CARDDBINCON_D              100078	//��ؿ��ⲻƽ�쳣��ɾ������
#define E_DB_CARDDBINCON_I              100079	//��ؿ��ⲻƽ�쳣��������
#define E_DB_CARDDBINCON_N              100080	//��ؿ��ⲻƽ�쳣������ؼ�¼
#define E_DB_CARDDBINCON_R              100081	//��ؿ��ⲻƽ�쳣���ѯ����
#define E_DB_CARDDBINCON_U              100082	//��ؿ��ⲻƽ�쳣����´���
#define E_DB_CARDLOSSINFO_D             100083	//����Ч�ڱ�ɾ������
#define E_DB_CARDLOSSINFO_I             100084	//����Ч�ڱ�������
#define E_DB_CARDLOSSINFO_N             100085	//����Ч�ڱ�����ؼ�¼
#define E_DB_CARDLOSSINFO_R             100086	//����Ч�ڱ��ѯ����
#define E_DB_CARDLOSSINFO_U             100087	//����Ч�ڱ���´���
#define E_DB_CARDMESS_D                 100088	//��������Ϣ��ɾ������
#define E_DB_CARDMESS_I                 100089	//��������Ϣ��������
#define E_DB_CARDMESS_N                 100090	//��������Ϣ������ؼ�¼
#define E_DB_CARDMESS_R                 100091	//��������Ϣ���ѯ����
#define E_DB_CARDMESS_U                 100092	//��������Ϣ����´���
#define E_DB_CARDOPERATE_D              100093	//����쳣��������ˮ��ɾ������
#define E_DB_CARDOPERATE_I              100094	//����쳣��������ˮ��������
#define E_DB_CARDOPERATE_N              100095	//����쳣��������ˮ������ؼ�¼
#define E_DB_CARDOPERATE_R              100096	//����쳣��������ˮ���ѯ����
#define E_DB_CARDOPERATE_U              100097	//����쳣��������ˮ����´���
#define E_DB_CARDSTRUT_D                100098	//������ṹ��Ϣ��ɾ������
#define E_DB_CARDSTRUT_I                100099	//������ṹ��Ϣ��������
#define E_DB_CARDSTRUT_N                100100	//������ṹ��Ϣ���ѯ����ؼ�¼
#define E_DB_CARDSTRUT_R                100101	//������ṹ��Ϣ���ȡ����
#define E_DB_CARDSTRUT_U                100102	//������ṹ��Ϣ����´���
#define E_DB_CARD_D                     100103	//����Ϣ��ɾ������
#define E_DB_CARD_I                     100104	//����Ϣ��������
#define E_DB_CARD_N                     100105	//����Ϣ������ؼ�¼
#define E_DB_CARD_R                     100106	//����Ϣ���ѯ����
#define E_DB_CARD_U                     100107	//����Ϣ����´���
#define E_DB_CHECKOUT_HIS_D             100108	//��ʷ������ˮ��ɾ������
#define E_DB_CHECKOUT_HIS_I             100109	//��ʷ������ˮ��������
#define E_DB_CHECKOUT_HIS_N             100110	//��ʷ������ˮ������ؼ�¼
#define E_DB_CHECKOUT_HIS_R             100111	//��ʷ������ˮ���ѯ����
#define E_DB_CHECKOUT_HIS_U             100112	//��ʷ������ˮ����´���
#define E_DB_COMMIT                     100113	//�����ύʧ��
#define E_DB_COSUME_HIS_D               100114	//������ʷת����ˮ��ɾ������
#define E_DB_COSUME_HIS_I               100115	//������ʷת����ˮ��������
#define E_DB_COSUME_HIS_N               100116	//������ʷ��ˮ������ؼ�¼
#define E_DB_COSUME_HIS_R               100117	//������ʷת����ˮ���ѯ����
#define E_DB_COSUME_HIS_U               100118	//������ʷת����ˮ����´���
#define E_DB_COSUME_LOG_D               100119	//��ˮ���ݱ�ɾ������
#define E_DB_COSUME_LOG_I               100120	//��ˮ���ݱ�������
#define E_DB_COSUME_LOG_N               100121	//��ˮ���ݱ�����ؼ�¼
#define E_DB_COSUME_LOG_R               100122	//��ˮ���ݱ��ѯ����
#define E_DB_COSUME_LOG_U               100123	//��ˮ���ݱ���´���
#define E_DB_COSUME_lOG_BAK_D           100124	//������ˮ��鵵ɾ������
#define E_DB_COSUME_lOG_BAK_I           100125	//������ˮ��鵵�������
#define E_DB_COSUME_lOG_BAK_U           100126	//������ˮ��鵵���´���
#define E_DB_CUR_SYSPARA_D              100127	//ȫ�ֲ�����ʽ��ɾ������
#define E_DB_CUR_SYSPARA_I              100128	//ȫ�ֲ�����ʽ��������
#define E_DB_CUR_SYSPARA_N              100129	//ȫ�ֲ�����ʽ���ѯ����ؼ�¼
#define E_DB_CUR_SYSPARA_R              100130	//ȫ�ֲ�����ʽ���ȡ����
#define E_DB_CUR_SYSPARA_RE             100131	//ȫ�ֲ�����ʶ�����ظ�
#define E_DB_CUR_SYSPARA_U              100132	//ȫ�ֲ�����ʽ���޸Ĵ���
#define E_DB_CUSTOMER_D                 100133	//�ͻ���Ϣ��ɾ������
#define E_DB_CUSTOMER_I                 100134	//�ͻ���Ϣ��������
#define E_DB_CUSTOMER_N                 100135	//�ͻ���Ϣ������ؼ�¼
#define E_DB_CUSTOMER_P                 100136	//�ͻ���Ϣ��ѯ��ִ�� EXEC SQL PREPARE ʱ����
#define E_DB_CUSTOMER_QUERY_N           100137	//�ͻ���Ϣ��ѯ����ؼ�¼
#define E_DB_CUSTOMER_QUERY_P           100138	//׼����̬��ѯ������
#define E_DB_CUSTOMER_R                 100139	//�ͻ���Ϣ���ѯ����
#define E_DB_CUSTOMER_U                 100140	//�ͻ���Ϣ����´���
#define E_DB_CUTTYPEFEE_D               100141	//�ͻ�����ɾ������
#define E_DB_CUTTYPEFEE_I               100142	//�ͻ�����������
#define E_DB_CUTTYPEFEE_N               100143	//�ͻ���������ؼ�¼
#define E_DB_CUTTYPEFEE_P               100144	//�ͻ�����ѯ��ִ�� EXEC SQL PREPARE ʱ����
#define E_DB_CUTTYPEFEE_R               100145	//�ͻ������ѯ����
#define E_DB_CUTTYPEFEE_U               100146	//�ͻ�������´���
#define E_DB_DEPARTMENT_D               100147	//��λ��ɾ������
#define E_DB_DEPARTMENT_I               100148	//��λ��������
#define E_DB_DEPARTMENT_N               100149	//��λ���ѯ����
#define E_DB_DEPARTMENT_R               100150	//��λ����´���
#define E_DB_DEPARTMENT_U               100151	//��λ������ؼ�¼
#define E_DB_DEPOSIT_LOG_BAK_D          100152	//��ֵ��ˮ��鵵ɾ������
#define E_DB_DEPOSIT_LOG_BAK_I          100153	//��ֵ��ˮ��鵵�������
#define E_DB_DEPOSIT_LOG_BAK_U          100154	//��ֵ��ˮ��鵵���´���
#define E_DB_DEPT_D                     100155	//��λ��Ϣ��ɾ������
#define E_DB_DEPT_I                     100156	//��λ��Ϣ��������
#define E_DB_DEPT_N                     100157	//��λ��Ϣ������ؼ�¼
#define E_DB_DEPT_R                     100158	//��λ��Ϣ���ѯ����
#define E_DB_DEPT_U                     100159	//��λ��Ϣ����´���
#define E_DB_DEVASSET_D                 100160	//�豸�ʲ���ɾ������
#define E_DB_DEVASSET_I                 100161	//�豸�ʲ���������
#define E_DB_DEVASSET_N                 100162	//�豸�ʲ����޼�¼
#define E_DB_DEVASSET_R                 100163	//�豸�ʲ��������
#define E_DB_DEVASSET_U                 100164	//�豸�ʲ�����´���
#define E_DB_DEVICE_D                   100165	//�豸ע���ɾ������
#define E_DB_DEVICE_I                   100166	//�豸ע���������
#define E_DB_DEVICE_LOG_D               100167	//�豸ǩ��/ǩ����־��ɾ������
#define E_DB_DEVICE_LOG_I               100168	//�豸ǩ��/ǩ����־��������
#define E_DB_DEVICE_LOG_N               100169	//�豸ǩ��/ǩ����־���ѯ�޼�¼
#define E_DB_DEVICE_LOG_R               100170	//�豸ǩ��/ǩ����־���ȡ����
#define E_DB_DEVICE_LOG_U               100171	//�豸ǩ��/ǩ����־���޸Ĵ���
#define E_DB_DEVICE_N                   100172	//�豸ע����ѯ�޼�¼
#define E_DB_DEVICE_R                   100173	//�豸ע����ȡ����
#define E_DB_DEVICE_U                   100174	//�豸ע����޸Ĵ���
#define E_DB_DEVI_LOGIN                 100175	//�豸û��ǩ��������ǩ��
#define E_DB_DEVI_MATCH                 100176	//�豸��־����ϵͳ��־ƥ��ʧ��
#define E_DB_DEVMONERR_D                100177	//�豸����쳣���ɾ������
#define E_DB_DEVMONERR_I                100178	//�豸����쳣���������
#define E_DB_DEVMONERR_N                100179	//�豸����쳣�������ؼ�¼
#define E_DB_DEVMONERR_R                100180	//�豸����쳣����ѯ����
#define E_DB_DEVMONERR_U                100181	//�豸����쳣�����´���
#define E_DB_DEVMONITOR_D               100182	//�豸��ر�ɾ������
#define E_DB_DEVMONITOR_I               100183	//�豸��ر�������
#define E_DB_DEVMONITOR_N               100184	//�豸��ر�����ؼ�¼
#define E_DB_DEVMONITOR_R               100185	//�豸��ر��ѯ����
#define E_DB_DEVMONITOR_U               100186	//�豸��ر���´���
#define E_DB_DEVTIME_D                  100187	//�豸ʱ������ñ�ɾ������
#define E_DB_DEVTIME_I                  100188	//�豸ʱ������ñ�������
#define E_DB_DEVTIME_N                  100189	//�豸ʱ������ñ��޼�¼
#define E_DB_DEVTIME_R                  100190	//�豸ʱ������ñ������
#define E_DB_DEVTIME_U                  100191	//�豸ʱ������ñ���´���
#define E_DB_DICTIONARY_D               100192	//�����ֵ��ɾ������
#define E_DB_DICTIONARY_I               100193	//�����ֵ��������
#define E_DB_DICTIONARY_N               100194	//�����ֵ���ѯ����ؼ�¼
#define E_DB_DICTIONARY_R               100195	//�����ֵ���ѯ����
#define E_DB_DICTIONARY_RE              100196	//�����ֵ��ظ�ע��
#define E_DB_DICTIONARY_U               100197	//�����ֵ����´���
#define E_DB_EMPLOYEE_D                 100198	//Ա����Ϣ��ɾ������
#define E_DB_EMPLOYEE_I                 100199	//Ա����Ϣ��������
#define E_DB_EMPLOYEE_N                 100200	//Ա����Ϣ������ؼ�¼
#define E_DB_EMPLOYEE_R                 100201	//Ա����Ϣ���ѯ����
#define E_DB_EMPLOYEE_U                 100202	//Ա����Ϣ����´���
#define E_DB_ERRCODE_D                  100203	//�������ɾ������
#define E_DB_ERRCODE_I                  100204	//�������������
#define E_DB_ERRCODE_N                  100205	//��������ѯ����ؼ�¼
#define E_DB_ERRCODE_R                  100206	//��������ѯ����
#define E_DB_ERRCODE_U                  100207	//���������´���
#define E_DB_ERROR                      100208	// ���ݿ����
#define E_DB_LINKMAN_N                  100209	//������ϵ�˱�����ؼ�¼
#define E_DB_LINKMAN_R                  100210	//������ϵ�˱��ȡ����
#define E_DB_MESLIST_D                  100211	//��Ϣ������Ϣ��ɾ������
#define E_DB_MESLIST_E                  100212	//��ϢID����
#define E_DB_MESLIST_I                  100213	//��Ϣ������Ϣ��������
#define E_DB_MESLIST_N                  100214	//��Ϣ������Ϣ������ؼ�¼
#define E_DB_MESLIST_R                  100215	//��Ϣ������Ϣ���ѯ����
#define E_DB_MESLIST_U                  100216	//��Ϣ������Ϣ����´���
#define E_DB_MESLIST_X                  100217	//��Ϣ������Ϣ����
#define E_DB_MODULE_AUTH_D              100218	//Ȩ��ģ���ɾ������
#define E_DB_MODULE_AUTH_I              100219	//Ȩ��ģ���������
#define E_DB_MODULE_AUTH_N              100220	//Ȩ��ģ�������ؼ�¼
#define E_DB_MODULE_AUTH_R              100221	//Ȩ��ģ����ѯ����
#define E_DB_MODULE_AUTH_RE             100222	//Ȩ��ģ���ظ�ע��
#define E_DB_MODULE_AUTH_U              100223	//Ȩ��ģ�����´���
#define E_DB_NOTFOUND                   100224	// �����Ϊ��
#define E_DB_OLD_SYSPARA_D              100225	//ȫ�ֲ�����ʱ��ɾ������
#define E_DB_OLD_SYSPARA_I              100226	//ȫ�ֲ�����ʱ��������
#define E_DB_OLD_SYSPARA_N              100227	//ȫ�ֲ�����ʱ���ѯ����ؼ�¼
#define E_DB_OLD_SYSPARA_R              100228	//ȫ�ֲ�����ʱ���ȡ����
#define E_DB_OLD_SYSPARA_U              100229	//ȫ�ֲ�����ʱ���޸Ĵ���
#define E_DB_OPERATOR_D                 100230	//����Աע���ɾ������
#define E_DB_OPERATOR_I                 100231	//����Աע���������
#define E_DB_OPERATOR_LOG_D             100232	//����Ա��½�ǳ���־��ɾ������
#define E_DB_OPERATOR_LOG_I             100233	//����Ա��½�ǳ���־��������
#define E_DB_OPERATOR_LOG_N             100234	//����Ա��½�ǳ���־������ؼ�¼
#define E_DB_OPERATOR_LOG_R             100235	//����Ա��½�ǳ���־���ѯ����
#define E_DB_OPERATOR_LOG_U             100236	//����Ա��½�ǳ���־����´���
#define E_DB_OPERATOR_N                 100237	//����Աע�������ؼ�¼
#define E_DB_OPERATOR_R                 100238	//����Աע����ѯ����
#define E_DB_OPERATOR_RE                100239	//����Ա�����Ѵ���
#define E_DB_OPERATOR_U                 100240	//����Աע�����´���
#define E_DB_OPER_MAIN_FUNC_D           100241	//����Ա�����ܺ�ɾ������
#define E_DB_OPER_MAIN_FUNC_I           100242	//����Ա�����ܺŲ������
#define E_DB_OPER_MAIN_FUNC_N           100243	//����Ա�����ܺű�����ؼ�¼
#define E_DB_OPER_MAIN_FUNC_R           100244	//����Ա�����ܺŲ�ѯ����
#define E_DB_OPER_MAIN_FUNC_U           100245	//����Ա�����ܺŸ��´���
#define E_DB_OPER_SITE_D                100246	//����Ա����½վ���ɾ������
#define E_DB_OPER_SITE_I                100247	//����Ա����½վ���������
#define E_DB_OPER_SITE_N                100248	//����Ա����½վ�������ؼ�¼
#define E_DB_OPER_SITE_R                100249	//����Ա����½վ����ѯ����
#define E_DB_OPER_SITE_RE               100250	//����Ա��½վ���ظ�ע��
#define E_DB_OPER_SITE_U                100251	//����Ա����½վ�����´���
#define E_DB_PHYDEVICE_D                100252	//�豸����ṹ��Ϣ��ɾ������
#define E_DB_PHYDEVICE_I                100253	//�豸����ṹ��Ϣ��������
#define E_DB_PHYDEVICE_N                100254	//�豸����ṹ��Ϣ���ѯ����ؼ�¼
#define E_DB_PHYDEVICE_R                100255	//�豸����ṹ��Ϣ���ȡ����
#define E_DB_PHYDEVICE_U                100256	//�豸����ṹ��Ϣ���޸Ĵ���
#define E_DB_REPORT_ACTIVE_D            100257	//���������ɾ������
#define E_DB_REPORT_ACTIVE_I            100258	//���������������
#define E_DB_REPORT_ACTIVE_N            100259	//�������������ؼ�¼
#define E_DB_REPORT_ACTIVE_R            100260	//����������ȡ����
#define E_DB_REPORT_ACTIVE_U            100261	//�����������´���
#define E_DB_REVISE_LOG_BAK_D           100262	//������ˮ��鵵ɾ������
#define E_DB_REVISE_LOG_BAK_I           100263	//������ˮ��鵵�������
#define E_DB_REVISE_LOG_BAK_U           100264	//������ˮ��鵵���´���
#define E_DB_ROLLBACK                   100265	//����ع�ʧ��
#define E_DB_SHOPDEPTFEE_D              100266	//�����̻�������ϸ��ͼɾ������
#define E_DB_SHOPDEPTFEE_I              100267	//�����̻�������ϸ��ͼ�������
#define E_DB_SHOPDEPTFEE_N              100268	//�����̻�������ϸ��ͼ����ؼ�¼
#define E_DB_SHOPDEPTFEE_R              100269	//�����̻�������ϸ��ͼ��ȡ����
#define E_DB_SHOPDEPTFEE_U              100270	//�����̻�������ϸ��ͼ���´���
#define E_DB_SHOP_D                     100271	//�̻���Ϣ��ɾ������
#define E_DB_SHOP_I                     100272	//�̻���Ϣ��������
#define E_DB_SHOP_LOG_D                 100273	//�̻���Ϣ��ʱ��ɾ������
#define E_DB_SHOP_LOG_I                 100274	//�̻���Ϣ��ʱ��������
#define E_DB_SHOP_LOG_N                 100275	//�̻���Ϣ��ʱ������ؼ�¼
#define E_DB_SHOP_LOG_R                 100276	//�̻���Ϣ��ʱ���ȡ����
#define E_DB_SHOP_LOG_U                 100277	//�̻���Ϣ��ʱ����´���
#define E_DB_SHOP_N                     100278	//�̻���Ϣ������ؼ�¼
#define E_DB_SHOP_POS_D                 100279	//�̻��豸��Ϣ��ɾ������
#define E_DB_SHOP_POS_I                 100280	//�̻��豸��Ϣ��������
#define E_DB_SHOP_POS_LOG_D             100281	//�̻��豸��Ϣ��ʱ��ɾ������
#define E_DB_SHOP_POS_LOG_I             100282	//�̻��豸��Ϣ��ʱ��������
#define E_DB_SHOP_POS_LOG_N             100283	//�̻��豸��Ϣ��ʱ������ؼ�¼
#define E_DB_SHOP_POS_LOG_R             100284	//�̻��豸��Ϣ��ʱ���ѯ����
#define E_DB_SHOP_POS_LOG_U             100285	//�̻��豸��Ϣ��ʱ����´���
#define E_DB_SHOP_POS_N                 100286	//�̻��豸��Ϣ������ؼ�¼
#define E_DB_SHOP_POS_R                 100287	//�̻��豸��Ϣ���ѯ����
#define E_DB_SHOP_POS_U                 100288	//�̻��豸��Ϣ����´���
#define E_DB_SHOP_R                     100289	//�̻���Ϣ���ѯ����
#define E_DB_SHOP_U                     100290	//�̻���Ϣ����´���
#define E_DB_SITE_INFO_D                100291	//վ���ɾ������
#define E_DB_SITE_INFO_I                100292	//վ���������
#define E_DB_SITE_INFO_N                100293	//վ�������ؼ�¼
#define E_DB_SITE_INFO_R                100294	//վ����ѯ����
#define E_DB_SITE_INFO_RE               100295	//��½վ���ظ�ע��
#define E_DB_SITE_INFO_U                100296	//վ�����´���
#define E_DB_SPECIALITY_D               100297	//רҵ��Ϣ��ɾ������
#define E_DB_SPECIALITY_I               100298	//רҵ��Ϣ��������
#define E_DB_SPECIALITY_N               100299	//רҵ��Ϣ������ؼ�¼
#define E_DB_SPECIALITY_R               100300	//רҵ��Ϣ���ѯ����
#define E_DB_SPECIALITY_U               100301	//רҵ��Ϣ����´���
#define E_DB_STUDENT_D                  100302	//ѧ����Ϣ��ɾ������
#define E_DB_STUDENT_I                  100303	//ѧ����Ϣ��������
#define E_DB_STUDENT_N                  100304	//ѧ����Ϣ������ؼ�¼
#define E_DB_STUDENT_R                  100305	//ѧ����Ϣ���ѯ����
#define E_DB_STUDENT_U                  100306	//ѧ����Ϣ����´���
#define E_DB_SUBJECT_D                  100307	//��Ŀ��ɾ������
#define E_DB_SUBJECT_I                  100308	//��Ŀ��������
#define E_DB_SUBJECT_N                  100309	//��Ŀ������ؼ�¼
#define E_DB_SUBJECT_R                  100310	//��Ŀ���ȡ����
#define E_DB_SUBJECT_U                  100311	//��Ŀ����´���
#define E_DB_SUBSIDY_LOG_BAK_D          100312	//������ˮ��鵵ɾ������
#define E_DB_SUBSIDY_LOG_BAK_I          100313	//������ˮ��鵵�������
#define E_DB_SUBSIDY_LOG_BAK_U          100314	//������ˮ��鵵���´���
#define E_DB_SUBSIDY_WAITING_BAK_D      100315	//��д����ˮ��鵵ɾ������
#define E_DB_SUBSIDY_WAITING_BAK_I      100316	//��д����ˮ��鵵�������
#define E_DB_SUBSIDY_WAITING_BAK_U      100317	//��д����ˮ��鵵���´���
#define E_DB_SUBSYSTEM_D                100318	//��ϵͳע���ɾ������
#define E_DB_SUBSYSTEM_I                100319	//��ϵͳע���������
#define E_DB_SUBSYSTEM_N                100320	//��ϵͳע����ѯ����޼�¼
#define E_DB_SUBSYSTEM_R                100321	//��ϵͳע����ȡ����
#define E_DB_SUBSYSTEM_SIGN             100322	//��ϵͳ��δǩ��ȴ����ǩ������
#define E_DB_SUBSYSTEM_U                100323	//��ϵͳע����޸Ĵ���
#define E_DB_SUBSYS_LOG_D               100324	//��ϵͳǩ��/ǩ����־��ɾ������
#define E_DB_SUBSYS_LOG_I               100325	//��ϵͳǩ��/ǩ����־��������
#define E_DB_SUBSYS_LOG_N               100326	//��ϵͳǩ��/ǩ����־���ѯ����޼�¼
#define E_DB_SUBSYS_LOG_R               100327	//��ϵͳǩ��/ǩ����־���ȡ����
#define E_DB_SUBSYS_LOG_U               100328	//��ϵͳǩ��/ǩ����־���޸Ĵ���
#define E_DB_SYSKEY_D                   100329	//��ſ��Ʊ�ɾ������
#define E_DB_SYSKEY_I                   100330	//��ſ��Ʊ�������
#define E_DB_SYSKEY_N                   100331	//��ſ��Ʊ�����ؼ�¼
#define E_DB_SYSKEY_R                   100332	//��ſ��Ʊ��ȡ����
#define E_DB_SYSKEY_U                   100333	//��ſ��Ʊ���´���
#define E_DB_SYSPARA_D                  100334	//ϵͳ������ɾ������
#define E_DB_SYSPARA_I                  100335	//ϵͳ������������
#define E_DB_SYSPARA_N                  100336	//ϵͳ����������ؼ�¼
#define E_DB_SYSPARA_R                  100337	//ϵͳ�������ȡ����
#define E_DB_SYSPARA_U                  100338	//ϵͳ��������´���
#define E_DB_SYSSTATE_D                 100339	//���ϵͳ״̬�쳣��ɾ������
#define E_DB_SYSSTATE_I                 100340	//���ϵͳ״̬�쳣��������
#define E_DB_SYSSTATE_N                 100341	//���ϵͳ״̬�쳣������ؼ�¼
#define E_DB_SYSSTATE_R                 100342	//���ϵͳ״̬�쳣���ѯ����
#define E_DB_SYSSTATE_U                 100343	//���ϵͳ״̬�쳣����´���
#define E_DB_SYSTIME_D                  100344	//ϵͳʱ���ɾ������
#define E_DB_SYSTIME_I                  100345	//ϵͳʱ���������
#define E_DB_SYSTIME_N                  100346	//ϵͳʱ�������ؼ�¼
#define E_DB_SYSTIME_R                  100347	//ϵͳʱ����ѯ����
#define E_DB_SYSTIME_U                  100348	//ϵͳʱ�����´���
#define E_DB_TABLE_DBCARD_D             100349	//���ⲻƽ����ɾ������
#define E_DB_TABLE_DBCARD_I             100350	//���ⲻƽ����������
#define E_DB_TABLE_DBCARD_N             100351	//���ⲻƽ��������ؼ�¼
#define E_DB_TABLE_DBCARD_R             100352	//���ⲻƽ���������
#define E_DB_TABLE_DBCARD_U             100353	//���ⲻƽ������´���
#define E_DB_TABLE_ERRACC_D             100354	//���ʲ�������ɾ������
#define E_DB_TABLE_ERRACC_I             100355	//���ʲ�������������
#define E_DB_TABLE_ERRACC_N             100356	//���ʲ�����������ؼ�¼
#define E_DB_TABLE_ERRACC_R             100357	//���ʲ������������
#define E_DB_TABLE_ERRACC_U             100358	//���ʲ���������´���
#define E_DB_TRADEACT_D                 100359	//��¼���ñ�ɾ������
#define E_DB_TRADEACT_I                 100360	//��¼���ñ�������
#define E_DB_TRADEACT_N                 100361	//��¼���ñ�����ؼ�¼
#define E_DB_TRADEACT_R                 100362	//��¼���ñ��ȡ����
#define E_DB_TRADEACT_U                 100363	//��¼���ñ���´���
#define E_DB_TRADELOG_BAK_D             100364	//������ϸ��鵵ɾ������
#define E_DB_TRADELOG_BAK_I             100365	//������ϸ��鵵�������
#define E_DB_TRADELOG_D                 100366	//������ϸ��ɾ������
#define E_DB_TRADELOG_I                 100367	//������ϸ��������
#define E_DB_TRADELOG_N                 100368	//������ϸ������ؼ�¼
#define E_DB_TRADELOG_R                 100369	//������ϸ���ѯ����
#define E_DB_TRADELOG_U                 100370	//������ϸ����´���
#define E_DB_TRADESERIALERROR_D         100371	//����쳣������ˮ��ɾ������
#define E_DB_TRADESERIALERROR_I         100372	//����쳣������ˮ��������
#define E_DB_TRADESERIALERROR_N         100373	//����쳣������ˮ������ؼ�¼
#define E_DB_TRADESERIALERROR_R         100374	//����쳣������ˮ���ѯ����
#define E_DB_TRADESERIALERROR_U         100375	//����쳣������ˮ����´���
#define E_DB_TRADESERIAL_D              100376	//��ˮ���ݱ�ɾ������
#define E_DB_TRADESERIAL_I              100377	//��ˮ���ݱ�������
#define E_DB_TRADESERIAL_N              100378	//��ˮ���ݱ�����ؼ�¼
#define E_DB_TRADESERIAL_R              100379	//��ˮ���ݱ��ѯ����
#define E_DB_TRADESERIAL_U              100380	//��ˮ���ݱ���´���
#define E_DB_TRANSFER_LOG_BAK_D         100381	//ת����ˮ��鵵ɾ������
#define E_DB_TRANSFER_LOG_BAK_I         100382	//ת����ˮ��鵵�������
#define E_DB_TRANSFER_LOG_BAK_U         100383	//ת����ˮ��鵵���´���
#define E_DB_TRANSFER_LOG_D             100384	//ת����ˮ��ɾ������
#define E_DB_TRANSFER_LOG_I             100385	//ת����ˮ��������
#define E_DB_TRANSFER_LOG_N             100386	//ת����ˮ������ؼ�¼
#define E_DB_TRANSFER_LOG_R             100387	//ת����ˮ���ȡ����
#define E_DB_TRANSFER_LOG_U             100388	//ת����ˮ����´���
#define E_DB_TRAN_D                     100389	//����쳣ת����ˮ��ɾ������
#define E_DB_TRAN_I                     100390	//����쳣ת����ˮ��������
#define E_DB_TRAN_N                     100391	//����쳣ת����ˮ������ؼ�¼
#define E_DB_TRAN_R                     100392	//����쳣ת����ˮ���ѯ����
#define E_DB_TRAN_U                     100393	//����쳣ת����ˮ����´���
#define E_DB_T_REPORT_BANK_TRANSFER_D   100394	//���л�����ɾ������
#define E_DB_T_REPORT_BANK_TRANSFER_I   100395	//���л�����������
#define E_DB_T_REPORT_BANK_TRANSFER_N   100396	//���л���������ؼ�¼
#define E_DB_T_REPORT_BANK_TRANSFER_R   100397	//���л������ȡ����
#define E_DB_T_REPORT_BANK_TRANSFER_U   100398	//���л�������´���
#define E_DB_T_REPORT_OPER_D            100399	//���������ɾ������
#define E_DB_T_REPORT_OPER_I            100400	//���������������
#define E_DB_T_REPORT_OPER_N            100401	//�������������ؼ�¼
#define E_DB_T_REPORT_OPER_R            100402	//����������ȡ����
#define E_DB_T_REPORT_OPER_U            100403	//�����������´���
#define E_DB_T_REPORT_RICH_DEBT_D       100404	//�ʲ���ծ��ɾ������
#define E_DB_T_REPORT_RICH_DEBT_I       100405	//�ʲ���ծ��������
#define E_DB_T_REPORT_RICH_DEBT_N       100406	//�ʲ���ծ������ؼ�¼
#define E_DB_T_REPORT_RICH_DEBT_R       100407	//�ʲ���ծ���ȡ����
#define E_DB_T_REPORT_RICH_DEBT_U       100408	//�ʲ���ծ����´���
#define E_DB_T_REPORT_SHOP_BALANCE_D    100409	//�̻������ɾ������
#define E_DB_T_REPORT_SHOP_BALANCE_I    100410	//�̻������������
#define E_DB_T_REPORT_SHOP_BALANCE_N    100411	//�̻����������ؼ�¼
#define E_DB_T_REPORT_SHOP_BALANCE_R    100412	//�̻�������ȡ����
#define E_DB_T_REPORT_SHOP_BALANCE_U    100413	//�̻��������´���
#define E_DB_T_REPORT_TRANS_COMP_D      100414	//ת�˶��ʱ�ɾ������
#define E_DB_T_REPORT_TRANS_COMP_I      100415	//ת�˶��ʱ�������
#define E_DB_T_REPORT_TRANS_COMP_N      100416	//ת�˶��ʱ�����ؼ�¼
#define E_DB_T_REPORT_TRANS_COMP_R      100417	//ת�˶��ʱ��ȡ����
#define E_DB_T_REPORT_TRANS_COMP_U      100418	//ת�˶��ʱ���´���
#define E_DB_T_TRANSFER_LOG_D           100419	//ת����ˮ��ɾ������
#define E_DB_T_TRANSFER_LOG_I           100420	//ת����ˮ��������
#define E_DB_T_TRANSFER_LOG_N           100421	//ת����ˮ������ؼ�¼
#define E_DB_T_TRANSFER_LOG_R           100422	//ת����ˮ���ȡ����
#define E_DB_T_TRANSFER_LOG_U           100423	//ת����ˮ����´���
#define E_DB_VIEW_DBCARD_D              100424	//���ⲻƽ��ͼɾ������
#define E_DB_VIEW_DBCARD_I              100425	//���ⲻƽ��ͼ�������
#define E_DB_VIEW_DBCARD_N              100426	//���ⲻƽ��ͼû�м�¼
#define E_DB_VIEW_DBCARD_R              100427	//���ⲻƽ��ͼ������
#define E_DB_VIEW_DBCARD_U              100428	//���ⲻƽ��ͼ���´���
#define E_DB_VIEW_ERRACC_D              100429	//���ʲ�����ͼɾ������
#define E_DB_VIEW_ERRACC_I              100430	//���ʲ�����ͼ�������
#define E_DB_VIEW_ERRACC_N              100431	//���ʲ�����ͼ����ؼ�¼
#define E_DB_VIEW_ERRACC_R              100432	//���ʲ�����ͼ������
#define E_DB_VIEW_ERRACC_U              100433	//���ʲ�����ͼ���´���
#define E_DB_VIEW_TOTALACC_N            100434	//������ͼ����ؼ�¼
#define E_DB_VIEW_TOTALACC_R            100435	//������ͼ������
#define E_DB_V_REPORT_BANK_TRANSFER_D   100436	//���л�����ͼɾ������
#define E_DB_V_REPORT_BANK_TRANSFER_I   100437	//���л�����ͼ�������
#define E_DB_V_REPORT_BANK_TRANSFER_N   100438	//���л�����ͼ����ؼ�¼
#define E_DB_V_REPORT_BANK_TRANSFER_R   100439	//���л�����ͼ��ȡ����
#define E_DB_V_REPORT_BANK_TRANSFER_U   100440	//���л�����ͼ���´���
#define E_DB_V_REPORT_OPER_D            100441	//���������ͼɾ������
#define E_DB_V_REPORT_OPER_I            100442	//���������ͼ�������
#define E_DB_V_REPORT_OPER_N            100443	//���������ͼ����ؼ�¼
#define E_DB_V_REPORT_OPER_R            100444	//���������ͼ��ȡ����
#define E_DB_V_REPORT_OPER_U            100445	//���������ͼ���´���
#define E_DB_V_REPORT_RICH_DEBT_D       100446	//�ʲ���ծ��ͼɾ������
#define E_DB_V_REPORT_RICH_DEBT_I       100447	//�ʲ���ծ��ͼ�������
#define E_DB_V_REPORT_RICH_DEBT_N       100448	//�ʲ���ծ��ͼ����ؼ�¼
#define E_DB_V_REPORT_RICH_DEBT_R       100449	//�ʲ���ծ��ͼ��ȡ����
#define E_DB_V_REPORT_RICH_DEBT_U       100450	//�ʲ���ծ��ͼ���´���
#define E_DB_V_REPORT_SHOP_BALANCE_D    100451	//�̻�������ͼɾ������
#define E_DB_V_REPORT_SHOP_BALANCE_I    100452	//�̻�������ͼ�������
#define E_DB_V_REPORT_SHOP_BALANCE_N    100453	//�̻�������ͼ����ؼ�¼
#define E_DB_V_REPORT_SHOP_BALANCE_R    100454	//�̻�������ͼ��ȡ����
#define E_DB_V_REPORT_SHOP_BALANCE_U    100455	//�̻�������ͼ���´���
#define E_DB_V_REPORT_TRANS_COMP_D      100456	//ת�˶�����ͼɾ������
#define E_DB_V_REPORT_TRANS_COMP_I      100457	//ת�˶�����ͼ�������
#define E_DB_V_REPORT_TRANS_COMP_N      100458	//ת�˶�����ͼ����ؼ�¼
#define E_DB_V_REPORT_TRANS_COMP_R      100459	//ת�˶�����ͼ��ȡ����
#define E_DB_V_REPORT_TRANS_COMP_U      100460	//ת�˶�����ͼ���´���
#define E_DB_WARRANT_D                  100461	//ƾ֤��ɾ������
#define E_DB_WARRANT_I                  100462	//ƾ֤��������
#define E_DB_WARRANT_N                  100463	//ƾ֤������ؼ�¼
#define E_DB_WARRANT_R                  100464	//ƾ֤���ȡ����
#define E_DB_WARRANT_U                  100465	//ƾ֤����´���
#define E_DB_WATCH_LOG_BAK_D            100466	//Ѳ����ˮ��鵵ɾ������
#define E_DB_WATCH_LOG_BAK_I            100467	//Ѳ����ˮ��鵵�������
#define E_DB_WATCH_LOG_BAK_U            100468	//Ѳ����ˮ��鵵���´���
#define E_DEPT_HAVE_CHILDREN            100469	//�õ�λ���¼���λ�ʲ���ɾ��
#define E_ENTER_ACCOUNT                 100470	//����ʧ��
#define E_ERROR_DATE                    100471	// ����ת��ʧ��
#define E_ERROR_ENDDATE                 100472	// �ս�����ת��ʧ��
#define E_ERROR_INIDATE                 100473	// ��ʼ����ת��ʧ��
#define E_ERROR_IN_COMM_WITH_BANK       100474	//������ͨ�Ŵ���
#define E_ERROR_WHEN_RECORDING_ACCOUNT  100475	//�ǻ�Ʒ�¼ʱ����
#define E_FAT_SHP_ID_NOT_EXIST          100477	//���̻�������
#define E_FEERATIO_TOO_HIGH             100478	//���ѱ���̫��
#define E_FEETYPE_NOT_EXIST             100479	//�����ڸ��շѷ�ʽ
#define E_FUNC_SET_NO_DEF               100503	//����Ա��Ȩ�޼�����û�и�ģ��Ķ���
#define E_GETAVAILABILITY               100504	//������ʽ��ʱ��ÿ�����Ч�ڴ���
#define E_GETAVAILABILITY_TEMP          100505	//������ʱ��ʱ��ÿ�����Ч�ڴ���
#define E_GET_DYNAKEY                   100506	//ȡ��̬��Կ����
#define E_GET_INITKEY                   100507	//ȡ��ʼ��Կ����
#define E_GET_READCARDKEY               100508	//ȡ�ö�����Կ����
#define E_INPUT_DATA_INVAILD            100509	//������������
#define E_INPUT_NODATE                  100510	//����Ϊ��
#define E_INPUT_NOENDTIME               100511	//����ʱ��Ϊ��
#define E_INPUT_NOFUNCNO                100512	//����Ĺ��ܺ�Ϊ��
#define E_INPUT_NOOPERATOR              100513	//����Ա����Ϊ��
#define E_INPUT_NOSTARTTIME             100514	//��ʼʱ��Ϊ��
#define E_JOIN_SHARE_MEMORY             100515	//���������ڴ�ʧ��
#define E_LOGINTOBANK_FAIL              100516	//ϵͳ��½������ʧ��
#define E_LOGINTOBANK_NO                100517	//ϵͳδ��½������
#define E_MAC_FAIL                      100518	//MACУ�����
#define E_NO_APP_DEFINE                 100519	//ϵͳ��û�и�Ӧ�ó���Ķ���
#define E_NO_BANK_CARD_INFO             100520	//�ÿ���δ�����п�,���ڷ���������ϵ
#define E_NO_SUCH_CARD                  100521	//��Ч�Ŀ���Ϣ,�޴�У԰��
#define E_NO_THIS_SYMBOL                100522	//û��������ܱ�־
#define E_OPER_LOGIN_LIMIT              100523	//�޵�½��վ��Ȩ��
#define E_OPER_LOGIN_RE                 100524	//�˲���Ա�ѵ�½
#define E_OPER_NO_MODULE_RIGHT          100525	//�˲���Աû�е�½��ģ���Ȩ��
#define E_PASSWORD_WRONG                100526	//����Ա��½�������
#define E_PATCH_CARD                    100527	//���쿨����,�ÿͻ��������쿨
#define E_PERSON_ACC                    100528	//�˶Ը�������ƽ
#define E_PUBLISH_CARD                  100529	//������ʽ������,�ÿͻ��Ѿ����й���
#define E_PUBLISH_TEMPCARD              100530	//������ʱ������,�ÿͻ�����������ʱ��
#define E_REC_ACCOUNT                   100531	//�ǻ�Ʒ�¼����
#define E_SEARCH_FLAG                   100532	//��ȫ�ֽ��ʱ�־����
#define E_SERIALNO_NOT_EXIST            100533	//��ˮ�Ų�����
#define E_SHOP_HAVE_CHILDREN            100534	//���̻����¼��̻��ʲ���ɾ��
#define E_SHP_ID_NOT_EXIST              100535	//�̻��Ų�����
#define E_SITE_ALREADY_LOGIN            100536	//���в���Ա�󶨴�վ����޷�ɾ��
#define E_SUBSYSREQUESTINVALID          100537	//��ϵͳ����Ϊ�Ƿ�,��̬��Կ����ϵͳ��ʶ����ȷ
#define E_SUBSYSTEM_RELOGIN             100538	//��ϵͳ��IP��������ַ�����ظ�
#define E_TIMESTAMP_FMT                 100539	//ʱ�����ʽ����ȷ
#define E_TIME_FMT                      100540	//ʱ���ʽ����ȷ
#define E_TOTAL_ACC                     100541	//�˶����˲�ƽ
#define E_TRADE_DETAIL_EXIST            100542	//������ˮ�Ѵ���
#define E_WHEN_SEARCH_CARD              100543	//��Ѱ����Ϣ�����
#define E_XML_KEY_NOTFOUND              100544	//XML���û�ҵ�
#define E_CARD_ACC_NO_EQ			100545	//����������˻�����
#define E_DB_ACCOUNT_E			100546		//�˻����¼�ظ�
#define E_DB_TRADESERIAL_E		100547		//��ˮ���¼�ظ�
#define E_DEPOSIT_FEE			100548		//Ѻ�������
#define E_COST_FEE				100549		//���ɱ��ѽ�����
#define E_IN_FEE					100550		//����ѽ�����
#define E_CUSTOMER_NOT_EXIST 	100551		//�ͻ��Ų�����
#define E_CARDNOFREEZE				100552		//��������״̬,�������ⶳ����
#define E_CUSTOMER_LOGOUT			100553		//�ÿͻ���ע��
#define E_ACTNO_EXIST				100554		//�˻��Ѵ���
#define E_CASH_LACK					100555		//�ý����ֽ���
#define E_CARD_PUBLISHED			100556		//�ÿ��Ѿ�����ʹ��
#define E_CUSTOMER_HAVE_CARD		100557		//�ÿͻ��Ѿ����й���
#define E_DB_CARD_E					100558		//����Ϣ���¼�ظ�
#define E_NORMALCARD_NOLOST		100559		//�ÿͻ���ʽ��δ��ʧ,���ܰ���ʱ��
#define E_TEMPCARD_NOLOST			100560		//�ÿͻ���һ����ʱ��������ʹ��,�����ٰ���ʱ��
#define E_NORMALCARD_NOT_REACH_ENDDATE		100561		//�ÿ���ʧ��δ��������ʽ��������
#define E_CARD_TYPE_NOT_EXIST		100562		//�����Ͳ�����
#define E_TMPCARDNO_NOT_EXIST	100563			//��ʱ���Ų�����
#define E_DB_TRADECODE_D            100564		//���״���ɾ������
#define E_DB_TRADECODE_I            100565		//���״���������
#define E_DB_TRADECODE_N            100566		//���״�������ؼ�¼
#define E_DB_TRADECODE_R            100567		//���״����ȡ����
#define E_DB_TRADECODE_U            100568		//���״�����´���
#define E_SUBSYSTEM_DELSTATE    100569		//��ϵͳ״̬��ΪԤע�ᡢע���ǩ��������ɾ��
#define E_TMPCARDNO_DIFFER	100570			//��ʱ�����Ų���
#define E_CARDNO_DIFFER		100571			//��ʽ�����Ų���
#define E_ACTNO_LOGOUT			100572			//�˻��Ѿ�ע��
#define E_TMPCARD_NOT_REACH_ENDDATE		100573		//��ʱ����ʧ��δ��������ʽ��������
#define E_INPUT_CARDNO_CANNOT_NULL		100574		//����Ŀ��Ų���Ϊ��
#define E_INPUT_CARDNO						100575		//�����������
#define E_INPUT_SERIALNO					100576		//��ˮ���������
#define E_CARDNO_LOGOUT					100577		//�ÿ��Ѿ�ע��
#define E_CARDNO_NOLOST					100578		//�ÿ�û�й�ʧ
#define E_FIRST_DEAL_TMPCARD				100579		//���Ȱ���ÿͻ���ʱ�����˿�����
#define E_CARD_PHYNO_DIFFER				100580		//������ID����
#define E_CARDNO_FREEZE					100581		//�ÿ��Ѿ�������
#define E_CARDNO_NOFREEZE					100582		//�ÿ�û�ж���
#define E_CARDNO_WFAIL						100583		//�ÿ��ϴν�����д��ʧ�ܣ����Ȳ�д�����ܽ���
#define E_SHOP_HAVE_DEVICE					100584		//���̻�������豸δɾ��
#define E_BACK_CARD_FOR_NORCARD			100585		//�ÿͻ���������ʹ�õ���ʱ��,���˻���ʱ��,���ܽ��
#define E_BACK_CARD_FOR_TMPCARD			100586		//�ÿͻ���������ʹ�õ���ʱ��,�ÿ����ܽ��,������˿�����
#define E_BACK_CARD_FOR_NORCARD2			100587		//�ÿͻ���������ʹ�õ���ʽ��,�ÿ����ܽ��,������˿�����
#define E_CARD_PWD_DIFFER					100588		//�����벻��
#define E_CUTTYPE_IN_USE					100589		//�ÿͻ�����Ѿ���ʹ��,������ֱ��ɾ��
#define E_AMT_EXCEED_MAX					100590		//��ֵ���������
#define E_DEV_WORK_TIME_CONFLICT			100591		//���豸�Ĳ�ͬ��Ŀ�Ĳ�ͬ����ʱ���֮���ʱ�����������10��������
#define E_DB_SHOP_POS_LOG_E				100592		//�̻��豸��ʱ���¼�ظ�
#define E_SHOP_HAVE_SUB_NODE				100593		//���̻����¼��̻�,����ɾ��
#define E_SHP_ACC_NO_RECKONING			100594		//���̻���ǰ�ʻ����ʽ�δ����
#define E_EXIST_SAME_SHOP_NAME			100595		//����ͬ�����̻�����,�뻻���̻�����
#define E_PWD_NULL							100596		//���벻�ܿ�
#define E_PWD_LEN							100597		//����λ������ȷ,,������6λ����
#define E_DEVICE_DELSTATE            			100598		//�豸״̬��Ϊע���ǩ��,����ɾ��
#define E_SUBSYS_LOGONIPMAC            		100599		//ǰ�û�ע����IP/MAC����Ϊ��
#define E_SUBSYS_DELDEVICE 	           		100600		//����ϵͳ���¼��豸û��ȫ��ע��,��Ҫ��ע�����¼��豸
#define E_DEVICE_SUBDEV	 	           		100601		//���豸���¼��豸û��ȫ��ע��,��Ҫ��ע�����¼��豸
#define E_DEVICE_DEVSHOP	 	           		100602		//���豸�ѱ��������ĳ���̻�,��Ҫ��ɾ���豸���̻��Ķ�Ӧ��ϵ
#define E_AREA_DEL			 	           		100603		//���������¼��ڵ�,����ɾ��,Ӧ��ɾ�����¼��ڵ�
#define E_OPERLOGON_UNREG	 	           		100604		//����Ա�Ѿ�ע��,���ܵ�½
#define E_DB_SITE_INFO_NETRE                		100605		//��վ������ƻ�IP��MAC��ַ�Ѿ�����,�����ظ�
#define E_DB_DEVICE_RE                			100606		//�豸���ƻ��豸����ID���豸IP�ظ�
#define E_AREA_RENAME	                			100607		//�������Ʋ����ظ�
#define E_SUBSYSTEM_NOT_EXIST				100608		//��ǰ�û�ϵͳ������
#define E_DYN_KEY_DIFFER					100609		//��̬��Կ����
#define E_DEVPHYID_NULL					100610		//�ն��豸����ID����Ϊ��
#define E_DB_RCVDTL_D						100611		//����������ˮ��ɾ������
#define E_DB_RCVDTL_E						100612		//����������ˮ���¼�ظ�
#define E_DB_RCVDTL_N						100613		//����������ˮ������ؼ�¼
#define E_DB_RCVDTL_R						100614		//����������ˮ���ȡ����
#define E_DB_RCVDTL_U						100615		//����������ˮ����´���
#define E_DB_DBCONN						100616		//���ݿ�����ʧ��
#define E_DB_DICINVALID						100617		//���ܶ�С��2000�������ֵ������б༭
#define E_FE_REGIST                                           100618          	//��ǰ�û��Ѿ�ע��
#define E_IP_MAC_NO_MATCH               			100619  		//IP��������ַ��ƥ��
#define E_SYSNAME_SAME						100620  		//��ϵͳ���Ʋ����ظ�
#define E_DEVICE_NOT_EXIST					100621		//��ϵͳ��û�д��豸
#define E_VALIDDATE_TOO_SHORT				100622		//�ͻ������и����ͻ���Ч�ڲ�������̫��
#define E_DEV_NOT_IN_WORKTIME				100623		//�豸���ڹ���ʱ��
#define E_EIME_MUST_GT_BTIME				100624		//����ʱ����������ʼʱ��
#define E_EDATE_MUST_GE_BDATE			100625		//�������ڱ�����ڵ�����ʼ����
#define E_DB_PHOTO_D                     			100626		//��Ƭ��ɾ������
#define E_DB_PHOTO_I                    			100627		//��Ƭ��������
#define E_DB_PHOTO_N                     			100628		//��Ƭ������ؼ�¼
#define E_DB_PHOTO_R                     			100629		//��Ƭ���ѯ����
#define E_DB_PHOTO_U                     			100630		//��Ƭ����´���
#define E_DB_STUEMPNO_RE                     		100631		//ѧ���Ų����ظ�
#define E_SUBSYSTEM_OFFLINE				100632		//ǰ�û�δ����,���豸�޷�ͨѶ
#define E_TXCODE_NOT_EXIST					100633		//���������
#define E_DEV_SUBSYS						100634		//���豸���ϼ����豸������ϵͳ����ͬ
#define E_INPUT_CARDPHYID					100635		//����Ŀ�����ID����
#define E_SYNCCUT_RUN						100636		//�ͻ�ͬ��������������
#define E_DEV_LPORT							100637		//�豸���ϼ��豸ֻ���ǻ��ʹ���Ϊ"������"��LPORT����ڵ�
#define E_TX_SERIAL_CZ						100638		//�ý����Ѿ�����,�����ظ�����
#define E_TX_SERIAL_CANNOT_CZ				100639		//�ý��ײ��ܳ���
#define E_CARDNO_SERIAL_NE					100640		//��������ˮ�п��Ų���
#define E_TX_CANNOT_DEAL					100641		//�ý�����ˮ����ִ�иý���
#define E_SHOP_ACTNO_NOT_EXIST			100642		//�̻��ʻ�������
#define E_CARD_ACTNO_NOT_EXIST			100643		//�ֿ����ʻ�������
#define E_DB_V_BLKLST_R              				100644		//��������ͼ��ѯ����
#define E_DB_CURSOR_DECLARE				100645		//�α�����ʧ��,����SQL����﷨
#define E_DB_CURSOR_OPEN					100646		//�α�򿪳���
#define E_DB_CURSOR_FETCH					100647		//�α�FETCH  ����
#define E_DB_CURSOR_CLOSE					100648		//�α�ر� ����
#define E_STUNO_NOT_EXIST					100649		//ѧ/���Ų�����
#define E_INPUT_SHOWCARDNO				100650		//��ʾ������������
#define E_SHOWCARDNO_EXIST				100651		//��ʾ�����Ѵ���
#define E_OPER_NOT_EXIST					100652		//����Ա������
#define E_AUTH_OPER_NOT_EXIST				100653		//��Ȩ����Ա������
#define E_OPER_AND_AUTH_OPER_EQ			100654		//��Ȩ����Ա���ܺ͵�ǰ����Ա��ͬ
#define E_AUTH_OPER_PWD					100655		//��Ȩ����Ա�����
#define E_TX_SERIAL							100656		//������ˮ����,��˶���ˮ
#define E_DB_SAVDTL_I                     			100657		//��ֵ��ϸ��¼��������
#define E_DB_SAVDTL_E                     			100658		//��ֵ��ϸ��¼���¼�ظ�
#define E_DB_SAVDTL_N                     			100659		//��ֵ��ϸ��¼������ؼ�¼
#define E_DB_SAVDTL_R                     			100660		//��ֵ��ϸ��¼���ȡ����
#define E_DB_SAVDTL_U                     			100661		//��ֵ��ϸ��¼����´���
#define E_DB_SAVDTL_D                     			100662		//��ֵ��ϸ��¼��ɾ������
#define E_INPUT_SHOWID						100663		//��ʾ������������
#define E_INPUT_AMT							100664		//�����������
#define E_CUTTYPE_CANNOT_DO				100665		//�ÿͻ�����������ý���
#define E_INPUT_DATE						100666		//������������
#define E_INPUT_TIME						100667		//ʱ����������
#define E_BEYOND_MAXNUM_TRADECODE		100668		//���������ó��������
#define E_BEYOND_MAXNUM_SPLITCFG			100669		//��¼���ó��������
#define E_BEYOND_MAXNUM_SUBJECT			100670		//��Ŀ���ó��������
#define E_BEYOND_MAXNUM_CFGIDX			100671		//�������ó��������
#define E_TXCODE_NOT_CONFIG				100672		//�������¼δ����
#define E_SPLIT_CFG							100673		//��¼��������
#define E_DB_CFGSPLIT_N                     		100674		//��¼���ñ�����ؼ�¼
#define E_DB_CFGSPLIT_R                     			100675		//��¼���ñ��ѯ����
#define E_DB_CFGIDX_N                     			100676		//�������ñ�����ؼ�¼
#define E_DB_CFGIDX_R                     			100677		//�������ñ��ѯ����
#define E_DB_CFGTXFEE_N                     		100678		//�շ����ñ�����ؼ�¼
#define E_DB_CFGTXFEE_R                     		100679		//�շ����ñ��ѯ����
#define E_DB_SUBUPDATE_I				100680			//��ϵͳ����������������
#define E_DB_SUBUPDATE_E				100681			//��ϵͳ�����������¼�ظ�
#define E_DB_SUBUPDATE_N				100682			//��ϵͳ��������������ؼ�¼
#define E_DB_SUBUPDATE_R				100683			//��ϵͳ�����������ȡ����
#define E_DB_SUBUPDATE_U				100684			//��ϵͳ������������´���
#define E_DB_SUBUPDATE_D				100685			//��ϵͳ����������ɾ������
#define E_EXP_NOT_CFG					100686			//���ʽδ����
#define E_EXP_CFG						100687			//���ʽ���ô���
#define E_ACTNO_IDX_NOT_CFG			100688			//�˺�����δ����
#define E_ACTNO_IDX_CFG				100689			//�˺��������ô���
#define E_DB_FEETYPE_N					100690			//�շ���������ؼ�¼
#define E_DB_FEETYPE_R					100691			//�շ������ȡ����
#define E_CUSTOMER_NO_FEE_TYPE		100692			//�ÿͻ�û���շ����
#define E_DB_SPEFEE_I					100693			//�����շѲ�����������
#define E_DB_SPEFEE_U					100694			//�����շѲ�������´���
#define E_DB_SPEFEE_R					100695			//�����շѲ������ȡ����
#define E_DB_SPEFEE_D					100696			//�����շѲ�����ɾ������
#define E_DB_SPEFEE_N					100697			//�����շѲ���������ؼ�¼
#define E_DB_SPEFEE_E					100698			//�����շѲ������¼�Ѵ���
#define E_CUSTOMER_NO_RIGHT			100699			//�ÿͻ�û��Ȩ�޽��б����
#define E_INPUT_CARD_TXCNT				100700			//�����״�����������
#define E_INPUT_CARD_BALA				100701			//���������������
#define E_CARD_CHANGE					100702			//�ÿ�����ʱд��ʧ��,���Ȼ���
#define E_OLDCARDINFO_NOSAVE			100703			//ԭ����Ϣδ����,���ܻ���
#define E_CARD_TXCNT					100704			//���ݿ��п����״�������
#define E_CARD_BALA						100705			//���ݿ��п��������
#define E_DB_CUSTOMER_TMP_R			100706			//�ͻ���Ϣ��ʱ���ȡ����
#define E_DB_CUSTOMER_TMP_I			100707			//�ͻ���Ϣ��ʱ��������
#define E_DB_CUSTOMER_TMP_U			100708			//�ͻ���Ϣ��ʱ����´���
#define E_DB_CUSTOMER_TMP_D			100709			//�ͻ���Ϣ��ʱ��ɾ������
#define E_DB_CUSTOMER_TMP_E			100710			//�ͻ���Ϣ��ʱ���¼�Ѵ���
#define E_DB_CUSTOMER_TMP_N			100711			//�ͻ���Ϣ��ʱ������ؼ�¼
#define E_INPUT_BATCH_NO				100712			//�������κ���������
#define E_BLACKLIST_VERSION_DIFF		100713			//�汾�Ų�ƥ��
#define E_BLACKLIST_VERSION			100714			//�汾�Ŵ���
#define E_NOCARD						100715			//�޿�,���ܽ���
#define E_AMT_LACK						100716			//�ý��׽���,�޷�����
#define E_EXIST_FREEZE_CARD			100717			//�ÿͻ��п�������,���ܲ����¿�
#define E_INPUT_AUTH_OPER_NULL		100718			//����������Ȩ����Ա������
#define E_CARD_STATE_NOT_CHANGE          100719			//��״̬���ǻ���δ�ɹ�״̬
#define E_DB_DIFF_TRANSFER_R			100720			//ת�ʶ��ʱ��ȡ����
#define E_DB_DIFF_TRANSFER_I			100721			//ת�ʶ��ʲ������
#define E_DB_DIFF_TRANSFER_U			100722			//ת�ʶ��ʱ���´���
#define E_DB_DIFF_TRANSFER_D			100723			//ת�ʶ��ʱ�ɾ������
#define E_DB_DIFF_TRANSFER_E			100724			//ת�ʶ��ʱ��¼�Ѵ���
#define E_DB_DIFF_TRANSFER_N			100725			//ת�ʶ��ʱ�����ؼ�¼
#define E_INPUT_BILLNO					100732			//Ʊ�ݺ�����������
#define E_DB_CUTINFO_UPD_R			100741			// �ͻ���Ϣ���±��ȡ����
#define E_DB_CUTINFO_UPD_I				100742			// �ͻ���Ϣ���±�������
#define E_DB_CUTINFO_UPD_U			100743			// �ͻ���Ϣ���±���´���
#define E_DB_CUTINFO_UPD_D			100744			// �ͻ���Ϣ���±�ɾ������
#define E_DB_CUTINFO_UPD_E			100745			// �ͻ���Ϣ���±������Ѵ���
#define E_DB_CUTINFO_UPD_N			100746			// �ͻ���Ϣ���±�����ؼ�¼
#define E_INPUT_GROUP_NAME			100747			//���������������
#define E_MSG_ID_NULL					100748			//��ϢID����Ϊ��
#define E_MSG_ID_NOT_EXIST				100749			//��ϢID������
#define E_FEE_CODE_SCOPE_ERR			100750			//�շѿ�Ŀ��Χ����ȷ
#define E_NOT_SUPPORT_FEE_CODE		100751			//�豸û�д򿪿�Ŀ�շѿ���
#define E_DEVTYPE_NOT_JSP				100758			//���豸�����Ž��豸
#define E_FEE_CODE_INUSE				100760			//���豸�Ѿ�ʹ�ÿ�Ŀ����
#define E_CARDNO_CARDLIST_NOT_EXIST	100761			//�Ž���Ա��������û�иÿ���
#define E_RIGHT_ALREADY_ASSIGN		100762			//�ò���Ա�Ը��豸Ȩ���Ѿ������
#define E_DB_PREPARE					100769			//��ѯSQL�﷨����
#define E_OPER_NO_RIGHT_FOR_DEVICE	100770			//����Ա�Ը��豸û�й���Ȩ��
#define E_DB_CFGTXFEE_I                     	100771			//�շ����ñ�����ؼ�¼
#define E_DB_CFGTXFEE_D                     	100772			//�շ����ñ��ѯ����
#define E_DB_CFGTXFEE_E				100773      		//�շ����ñ��¼�ظ�
#define E_DB_FEETYPE_I					100774			//�շ�����������
#define E_DB_FEETYPE_D					100775			//�շ�����ɾ������
#define E_DB_FEETYPE_E					100776			//�շ������¼�Ѵ���
#define E_DB_FEETYPE_U					100777			//�շ�������´���

#define E_DB_PHOTOTMP_R				100826			//��Ƭ��ʱ���ȡ����
#define E_DB_PHOTOTMP_I				100827			//��Ƭ��ʱ��������
#define E_DB_PHOTOTMP_U				100828			//��Ƭ��ʱ����´���
#define E_DB_PHOTOTMP_D				100829			//��Ƭ��ʱ��ɾ������
#define E_DB_PHOTOTMP_E				100830			//��Ƭ��ʱ���¼�Ѵ���
#define E_DB_PHOTOTMP_N				100831			//��Ƭ��ʱ������ؼ�¼
#define E_SYS_CALL						100832			//ϵͳ����ʧ��
#define E_DYNAMIC_STMT_EXECUTE		100833			//ִ�ж�̬���ʧ��
#define E_DB_SYS_UPDATE_R				100834			//��ϵͳ�������ȡ����
#define E_DB_SYS_UPDATE_I				100835			//��ϵͳ������������
#define E_DB_SYS_UPDATE_U				100836			//��ϵͳ��������´���
#define E_DB_SYS_UPDATE_D				100837			//��ϵͳ������ɾ������
#define E_DB_SYS_UPDATE_E				100838			//��ϵͳ�������¼�Ѵ���
#define E_DB_SYS_UPDATE_N				100839			//��ϵͳ����������ؼ�¼
#define E_SUBSYS_FUNC_NOT_EXISTS		100840			//��ϵͳ���ܲ�����
#define E_INPUT_ACTNO_NULL				100841			//�������ʺ�
#define E_INPUT_2ACTNO_EQ				100842			//����������ʺŲ�����ͬ
#define E_INPUT_OPER_PWD				100843			//����Ĳ���Ա�������
#define E_INPUT_OPER_NULL				100844			//���������Ա��
#define E_INPUT_OPER_EXIST				100845			//����Ĳ���Ա������
#define E_INPUT_AMT_NULL				100846			//��������
#define E_INPUT_2OPER_EQ				100847			//��������Ա�Ų�����ͬ
#define E_TB_CUSTOMER_ENDTIME			100848			//�ͻ���Ϣ���иÿͻ���Ԥ�Ʊ�ҵ��������
#define E_TB_CUSTOMER_NO_ENDTIME 	100849			//�ͻ���Ϣ���иÿͻ�û��Ԥ�Ʊ�ҵ����,���ֹ����뿨����Ч��
#define E_NO_NEXT_TRADE				100850			//û����һ����ˮ,�ݲ�����
#define E_INPUT_DEPOSIT_TYPE			100851			//��������Ч�ĳ�ֵ��ʽ
#define E_DB_SUBSIDY_I					100852			//������Ϣ��������
#define E_DB_SUBSIDY_U					100853			//������Ϣ����´���
#define E_DB_SUBSIDY_R					100854			//������Ϣ���ȡ����
#define E_DB_SUBSIDY_D					100855			//������Ϣ��ɾ������
#define E_DB_SUBSIDY_N					100856			//������Ϣ������ؼ�¼
#define E_DB_SUBSIDY_E					100857			//������Ϣ���¼�Ѵ���
#define E_DB_SUBSIDYTMP_I				100858			//������Ϣ��ʱ��������
#define E_DB_SUBSIDYTMP_U				100869			//������Ϣ��ʱ����´���
#define E_DB_SUBSIDYTMP_R				100860			//������Ϣ��ʱ���ȡ����
#define E_DB_SUBSIDYTMP_D				100861			//������Ϣ��ʱ��ɾ������
#define E_DB_SUBSIDYTMP_N				100862			//������Ϣ��ʱ������ؼ�¼
#define E_DB_SUBSIDYTMP_E				100863			//������Ϣ��ʱ���¼�Ѵ���
#define E_INPUT_STUEMP_NO				100864			//ѧ/������������
#define E_INPUT_SUMMARY				100865			//ժҪ���ݲ���Ϊ��
#define E_DB_DOOR_DEV_HAS_MORE_WT		100866			//�Ž�ͬһ�컹��δ�´���ʱ���
#define E_DEVICE_PARAM_ERR				100867			//�豸��������
#define E_USER_NO_SUBSIDY				100868			//û�в���������ȡ
#define E_SHOP_IS_NOT_LEAF				100869			//�̻�����Ҷ�ӽڵ�

#define E_DB_CONFDEV_I					100870			//�����豸��������
#define E_DB_CONFDEV_U					100871			//�����豸����´���
#define E_DB_CONFDEV_R					100872			//�����豸���ȡ����
#define E_DB_CONFDEV_D					100873			//�����豸��ɾ������
#define E_DB_CONFDEV_N					100874			//�����豸������ؼ�¼
#define E_DB_CONFDEV_E					100875			//�����豸���¼�Ѵ���
#define E_DB_CONFATTLST_I					100876			//����ǩ����������
#define E_DB_CONFATTLST_U					100877			//����ǩ������´���
#define E_DB_CONFATTLST_R					100878			//����ǩ�����ȡ����
#define E_DB_CONFATTLST_D					100879			//����ǩ����ɾ������
#define E_DB_CONFATTLST_N					100880			//����ǩ��������ؼ�¼
#define E_DB_CONFATTLST_E					100882			//����ǩ�����¼�Ѵ���

//���ⲻƽ���������
#define E_NOT_REATH_CARDDB_NOBALA_TIMES		100883		//���˻����ⲻƽ����̫�̣���������
#define E_INPUT_DATE_TIME_ERROR			100884			//��ѡ��ȱʧ����ˮ�Ž��в���ˮ����
#define E_FEETYPE_IN_USE					100885			//���շ������ʹ�ã�������ɾ��
#define E_DEPT_CODE_IN_USE					100886			//�ò��Ŵ�����ʹ�ã�����ɾ��
#define E_SPECIALITY_CODE_IN_USE			100887			//��רҵ������ʹ�ã�����ɾ��
#define E_AREA_CODE_IN_USE				100886			//�����������ʹ�ã�����ɾ��
#define E_GLOBAL_PARAM_ERROR				110001			//ϵͳ��������

#define E_DB_TRADECODE_SHOP_I				110008			//���״����̻���Ϣ��������
#define E_DB_TRADECODE_SHOP_U			110009			//���״����̻���Ϣ����´���
#define E_DB_TRADECODE_SHOP_R				110010			//���״����̻���Ϣ���ȡ����
#define E_DB_TRADECODE_SHOP_D			110011			//���״����̻���Ϣ��ɾ������
#define E_DB_TRADECODE_SHOP_N			110012			//���״����̻���Ϣ������ؼ�¼
#define E_DB_TRADECODE_SHOP_E				110013			//���״����̻���Ϣ���¼�Ѵ���
#define E_CARD_INFO_NOT_FOUND				100890			//�޸ÿ������Ϣ
#define E_CARD_INFO_MUST_NEW_CARD			100891			//�ÿ�ֻ���¿�����
#define E_CARD_INFO_MUST_SECOND_CARD		100892			//�ÿ�ֻ�ܲ��쿨����
#define E_CARD_INFO_PHY_ID_DUP				100893			//�ÿ��ظ�����
#define E_DB_WRITEFAILED_I                107001           //���д��ʧ�ܱ�ʧ��
#define E_DB_WRITEFAILED_R               107002           //��ȡд��ʧ�ܱ�ʧ��
#define E_DB_WRITEFAILED_N               107003           //д��ʧ�ܱ�����ؼ�¼
#define E_DB_WRITEFAILED_U               107004           //����д��ʧ�ܱ����
#define E_WRITEFAILED_DEAL_FLAG_N         107008           //û�б��д��ʧ��Ǯ����־
#define E_CARD_REWRITE_REMAIN            107010           //�˿�����Ǯ����δ�в�д��� 
#define E_PACKET_LIMIT_EXCEED             106001           //СǮ�������޶�
#define E_DB_DEVICE_IN_ACCOUNT            107020           //���豸�ɼ����������
#define E_DB_DEVICE_COLLECT_LOG_I         107021           //�����豸�ɼ������

#define E_DB_GROUP_I						100895			//����Ա���������
#define E_DB_GROUP_U						100896			//����Ա�����´���
#define E_DB_GROUP_R						100897			//����Ա����ȡ����
#define E_DB_GROUP_D						100898			//����Ա���ɾ������
#define E_DB_GROUP_N						100899			//����Ա�������ؼ�¼
#define E_DB_GROUP_E						100900			//����Ա����¼�Ѵ���
#define E_DB_GROUP_DE						100901			//����Ա��������ע����
#define E_DB_OPER_GROUP_I					100902			//����Ա�����������
#define E_DB_OPER_GROUP_U					100903			//����Ա�������´���
#define E_DB_OPER_GROUP_R					100904			//����Ա������ȡ����
#define E_DB_OPER_GROUP_D					100905			//����Ա�����ɾ������
#define E_DB_OPER_GROUP_N					100906			//����Ա���������ؼ�¼
#define E_DB_OPER_GROUP_E					100907			//����Ա������¼�Ѵ���
#define E_DB_OPER_GROUP_DE				100908			//����Ա����������ע����¼

#define E_OPER_HAS_MONEY					100909			//����Ա�˻��������,����ע��

#define E_DB_GRP_CASH_RPT_I				100910			//����Ա���ֽ��������
#define E_DB_GRP_CASH_RPT_U				100911			//����Ա���ֽ����´���
#define E_DB_GRP_CASH_RPT_R				100912			//����Ա���ֽ���ȡ����
#define E_DB_GRP_CASH_RPT_D				100913			//����Ա���ֽ��ɾ������
#define E_DB_GRP_CASH_RPT_N				100914			//����Ա���ֽ������ؼ�¼
#define E_DB_GRP_CASH_RPT_E				100915			//����Ա���ֽ���¼�Ѵ���

#define E_DB_MEAL_TYPE_I					100916			//�ʹα�������
#define E_DB_MEAL_TYPE_U					100917			//�ʹα���´���
#define E_DB_MEAL_TYPE_R					100918			//�ʹα��ȡ����
#define E_DB_MEAL_TYPE_D					100919			//�ʹα�ɾ������
#define E_DB_MEAL_TYPE_N					100920			//�ʹα�����ؼ�¼
#define E_DB_MEAL_TYPE_E					100921			//�ʹα��¼�Ѿ�����

#define E_DB_SHOP_MEAL_I					100922			//�̻��ʹα�������
#define E_DB_SHOP_MEAL_U					100923			//�̻��ʹα���´���
#define E_DB_SHOP_MEAL_R					100924			//�̻��ʹα��ȡ����
#define E_DB_SHOP_MEAL_D					100925			//�̻��ʹα�ɾ������
#define E_DB_SHOP_MEAL_N					100926			//�̻��ʹα�����ؼ�¼
#define E_DB_SHOP_MEAL_E					100927			//�̻��ʹα��¼�Ѿ�����

#define E_DB_V_REPORT_DEVICE_MEAL_I		100928			//�̻��豸�ʹ���ͼ�������
#define E_DB_V_REPORT_DEVICE_MEAL_U		100929			//�̻��豸�ʹ���ͼ���´���
#define E_DB_V_REPORT_DEVICE_MEAL_R		100930			//�̻��豸�ʹ���ͼ��ȡ����
#define E_DB_V_REPORT_DEVICE_MEAL_D		100931			//�̻��豸�ʹ���ͼɾ������
#define E_DB_V_REPORT_DEVICE_MEAL_N		100932			//�̻��豸�ʹ���ͼ����ؼ�¼
#define E_DB_V_REPORT_DEVICE_MEAL_E		100933			//�̻��豸�ʹ���ͼ��¼�Ѿ�����

#define E_DB_T_REPORT_DEVICE_MEAL_I		100934			//�̻��豸�ʹα�������
#define E_DB_T_REPORT_DEVICE_MEAL_U		100935			//�̻��豸�ʹ���ͼ���´���
#define E_DB_T_REPORT_DEVICE_MEAL_R		100936			//�̻��豸�ʹ���ͼ��ȡ����
#define E_DB_T_REPORT_DEVICE_MEAL_D		100937			//�̻��豸�ʹ���ͼɾ������
#define E_DB_T_REPORT_DEVICE_MEAL_N		100938			//�̻��豸�ʹ���ͼ����ؼ�¼
#define E_DB_T_REPORT_DEVICE_MEAL_E		100939			//�̻��豸�ʹ���ͼ��¼�Ѿ�����

#define E_SHOP_MEAL_TYPE_CONFLICT			100940			//�޸�����̻��ʹη����г�ͻ
#define E_MEAL_TYPE_ID_NOFOUND			100941			//ָ���ĲʹκŲ�����

#define E_DB_OPER_AUTHCARD_I				100942			//����Ա��Ȩ����������
#define E_DB_OPER_AUTHCARD_U				100943			//����Ա��Ȩ�����´���
#define E_DB_OPER_AUTHCARD_R				100944			//����Ա��Ȩ����ȡ����
#define E_DB_OPER_AUTHCARD_D				100945			//����Ա��Ȩ��ɾ������
#define E_DB_OPER_AUTHCARD_N				100946			//����Ա��Ȩ������ؼ�¼
#define E_DB_OPER_AUTHCARD_E				100947			//����Ա��Ȩ����¼�Ѿ�����
#define E_AUTHCARD_NOT_EXISTS				100950			//��Ȩ��������
#define E_AUTHCARD_HAS_CANCEL			100951			//��Ȩ����ע��
#define E_AUTHCARD_IS_LOSS					100952			//��Ȩ���Ѿ���ʧ
#define E_OPER_ALREADY_HAS_AUTHCARD		100953			//����Ա�Ѿ�����Ȩ��
#define E_PHYSICAL_NO_IS_IN_USE			100954			//�ÿ��Ѿ�����������Աʹ��

#define E_DB_CUT_RLTN_I				110015			//�ͻ����п��Ű󶨹�ϵ��������
#define E_DB_CUT_RLTN_U				110016			//�ͻ����п��Ű󶨹�ϵ����´���
#define E_DB_CUT_RLTN_R				110017			//�ͻ����п��Ű󶨹�ϵ���ȡ����
#define E_DB_CUT_RLTN_D				110018			//�ͻ����п��Ű󶨹�ϵ��ɾ������
#define E_DB_CUT_RLTN_N				110019			//�ͻ����п��Ű󶨹�ϵ������ؼ�¼
#define E_DB_CUT_RLTN_E				110020			//�ͻ����п��Ű󶨹�ϵ���¼�Ѵ���
#define E_DB_CUT_RLTN_TMP_I				110021			//�ͻ����п��Ű󶨹�ϵ��ʱ��������
#define E_DB_CUT_RLTN_TMP_U				110022			//�ͻ����п��Ű󶨹�ϵ��ʱ����´���
#define E_DB_CUT_RLTN_TMP_R				110023			//�ͻ����п��Ű󶨹�ϵ��ʱ���ȡ����
#define E_DB_CUT_RLTN_TMP_D				110024			//�ͻ����п��Ű󶨹�ϵ��ʱ��ɾ������
#define E_DB_CUT_RLTN_TMP_N				110025			//�ͻ����п��Ű󶨹�ϵ��ʱ������ؼ�¼
#define E_DB_CUT_RLTN_TMP_E				110026			//�ͻ����п��Ű󶨹�ϵ��ʱ���¼�Ѵ���

/////////////////////////////////////////////////////////////////////////////////
// ͨ�ô�����Ϣ���뷶Χ 190000 - 199999
#define E_CUSTOMER_HASNO_NORM_CARD		190001			//�ͻ���������
#define E_MES_GROUP_NOT_DEFINED			190002			//��Ϣ����δ������
#define E_SHOP_NOT_LEAF_GETFEE			190003			//��Ҷ�ӽڵ㲻����ȡ����
//////////////////////////////////////////////////////////////////////////////
// �Ž��ཻ�״����뷶Χ 130000 - 139999

#define E_DB_DOOR_TIMESECT_I				130001			//�Ž�ʱ��α�������
#define E_DB_DOOR_TIMESECT_U				130002			//�Ž�ʱ��α���´���
#define E_DB_DOOR_TIMESECT_R				130003			//�Ž�ʱ��α��ȡ����
#define E_DB_DOOR_TIMESECT_D				130004			//�Ž�ʱ��α�ɾ������
#define E_DB_DOOR_TIMESECT_N				130005			//�Ž�ʱ��α�����ؼ�¼
#define E_DB_DOOR_TIMESECT_E				130006			//�Ž�ʱ��α��¼�Ѵ���
#define E_DB_DOOR_WEEKS_I					130007			//�Ž�ʱ������������
#define E_DB_DOOR_WEEKS_U					130008			//�Ž�ʱ��������´���
#define E_DB_DOOR_WEEKS_R					130009			//�Ž�ʱ�������ȡ����
#define E_DB_DOOR_WEEKS_D					130010			//�Ž�ʱ������ɾ������
#define E_DB_DOOR_WEEKS_N					130011			//�Ž�ʱ����������ؼ�¼
#define E_DB_DOOR_WEEKS_E					130012			//�Ž�ʱ�������¼�Ѵ���
#define E_DOOR_WEEK_TIME_IDX				130013			//�Ž�ʱ�����ʱ��θ�������ȷ
#define E_DOOR_WEEK_NO					130014			//�Ž�ʱ��������ڲ���ȷ
#define E_DB_DOOR_WEEK_TIMES_I			130015			//�Ž�ʱ��������ñ�������
#define E_DB_DOOR_WEEK_TIMES_U			130016			//�Ž�ʱ��������ñ���´���
#define E_DB_DOOR_WEEK_TIMES_R			130017			//�Ž�ʱ��������ñ��ȡ����
#define E_DB_DOOR_WEEK_TIMES_D			130018			//�Ž�ʱ��������ñ�ɾ������
#define E_DB_DOOR_WEEK_TIMES_N			130019			//�Ž�ʱ��������ñ�����ؼ�¼
#define E_DB_DOOR_WEEK_TIMES_E			130020			//�Ž�ʱ��������ñ��¼�Ѵ���
#define E_DB_DOOR_HOLIDAY_R			130021			//�Ž��ڼ��ձ��ȡ����
#define E_DB_DOOR_HOLIDAY_I			130022			//�Ž��ڼ��ձ�������
#define E_DB_DOOR_HOLIDAY_U			130023			//�Ž��ڼ��ձ���´���
#define E_DB_DOOR_HOLIDAY_D			130024			//�Ž��ڼ��ձ�ɾ������
#define E_DB_DOOR_HOLIDAY_E			130025			//�Ž��ڼ��ձ��¼�Ѵ���
#define E_DB_DOOR_HOLIDAY_N			130026			//�Ž��ڼ��ձ�����ؼ�¼
#define E_DOOR_HOLIDAY_MAX_FLAG		130027			//��ȡ�Ž��ڼ����������������
#define E_DOOR_HOLIDAY_EXCEED			130028			//�Ž��ڼ��ո����������ֵ
#define E_DB_DOOR_HOLIDAY_TIME_R			130029			//�Ž��ڼ���ʱ��α��ȡ����
#define E_DB_DOOR_HOLIDAY_TIME_I			130030			//�Ž��ڼ���ʱ��α�������
#define E_DB_DOOR_HOLIDAY_TIME_U			130031			//�Ž��ڼ���ʱ��α���´���
#define E_DB_DOOR_HOLIDAY_TIME_D			130032			//�Ž��ڼ���ʱ��α�ɾ������
#define E_DB_DOOR_HOLIDAY_TIME_E			130033			//�Ž��ڼ���ʱ��α��¼�Ѵ���
#define E_DB_DOOR_HOLIDAY_TIME_N			130034			//�Ž��ڼ���ʱ��α�����ؼ�¼
#define E_DB_DOOR_GROUP_R				130035			//�Ž�����ȡ����
#define E_DB_DOOR_GROUP_I				130036			//�Ž����������
#define E_DB_DOOR_GROUP_U				130037			//�Ž������´���
#define E_DB_DOOR_GROUP_D				130038			//�Ž����ɾ������
#define E_DB_DOOR_GROUP_E				130039			//�Ž�����¼�Ѵ���
#define E_DB_DOOR_GROUP_N				130040			//�Ž��������ؼ�¼
#define E_OPER_NO_RIGHT_FOR_DOOR_GROUP 130041		//����Ա���Ž������Ȩ��
#define E_DOOR_GROUP_IN_USE			130042			//�Ž����Ѿ�ʹ��
#define E_DB_DOOR_GROUP_MEMBER_R		130043			//�Ž����豸���ȡ����
#define E_DB_DOOR_GROUP_MEMBER_I		130044			//�Ž����豸��������
#define E_DB_DOOR_GROUP_MEMBER_U	130045			//�Ž����豸����´���
#define E_DB_DOOR_GROUP_MEMBER_D	130046			//�Ž����豸��ɾ������
#define E_DB_DOOR_GROUP_MEMBER_E		130047			//�Ž����豸���¼�Ѵ���
#define E_DB_DOOR_GROUP_MEMBER_N	130048			//�Ž����豸������ؼ�¼
#define E_DOOR_WEEK_MUST_SET			130049			//�Ž��ܱ�������ʱ�����
#define E_DB_DOOR_TIME_GROUP_R		130050			//�Ž����豸���ȡ����
#define E_DB_DOOR_TIME_GROUP_I		130051			//�Ž����豸��������
#define E_DB_DOOR_TIME_GROUP_U		130052			//�Ž����豸����´���
#define E_DB_DOOR_TIME_GROUP_D		130053			//�Ž����豸��ɾ������
#define E_DB_DOOR_TIME_GROUP_E		130054			//�Ž����豸���¼�Ѵ���
#define E_DB_DOOR_TIME_GROUP_N		130055			//�Ž����豸������ؼ�¼
#define E_DOOR_GROUP_CANCEL			130056			//�Ž����ѱ�ע��
#define E_DB_DOOR_OPER_RIGHT_R		130057			//�Ž���Ȩ�ޱ��ȡ����
#define E_DB_DOOR_OPER_RIGHT_I		130058			//�Ž���Ȩ�ޱ�������
#define E_DB_DOOR_OPER_RIGHT_U		130059			//�Ž���Ȩ�ޱ���´���
#define E_DB_DOOR_OPER_RIGHT_D		130060			//�Ž���Ȩ�ޱ�ɾ������
#define E_DB_DOOR_OPER_RIGHT_E		130061			//�Ž���Ȩ�ޱ��¼�Ѵ���
#define E_DB_DOOR_OPER_RIGHT_N		130062			//�Ž���Ȩ�ޱ�����ؼ�¼
#define E_DB_DOOR_GRP_OPER_RIGHT_R	130063			//�Ž���Ȩ�ޱ��ȡ����
#define E_DB_DOOR_GRP_OPER_RIGHT_I	130064			//�Ž���Ȩ�ޱ�������
#define E_DB_DOOR_GRP_OPER_RIGHT_U	130065			//�Ž���Ȩ�ޱ���´���
#define E_DB_DOOR_GRP_OPER_RIGHT_D	130066			//�Ž���Ȩ�ޱ�ɾ������
#define E_DB_DOOR_GRP_OPER_RIGHT_E	130067			//�Ž���Ȩ�ޱ��¼�Ѵ���
#define E_DB_DOOR_GRP_OPER_RIGHT_N	130068			//�Ž���Ȩ�ޱ�����ؼ�¼
#define E_DB_DOOR_CARDLIST_R			130069			//�Ž�����Ա�������ȡ����
#define E_DB_DOOR_CARDLIST_I			130070			//�Ž�����Ա������������
#define E_DB_DOOR_CARDLIST_U			130071			//�Ž�����Ա��������´���
#define E_DB_DOOR_CARDLIST_D			130072			//�Ž�����Ա������ɾ������
#define E_DB_DOOR_CARDLIST_E			130073			//�Ž�����Ա�������¼�Ѵ���
#define E_DB_DOOR_CARDLIST_N			130074			//�Ž�����Ա����������ؼ�¼
#define E_DB_DOOR_DEV_WEEK_R			130075			//�Ž��豸�����ܱ��ȡ����
#define E_DB_DOOR_DEV_WEEK_I			130076			//�Ž��豸�����ܱ�������
#define E_DB_DOOR_DEV_WEEK_U			130077			//�Ž��豸�����ܱ���´���
#define E_DB_DOOR_DEV_WEEK_D			130078			//�Ž��豸�����ܱ�ɾ������
#define E_DB_DOOR_DEV_WEEK_E			130079			//�Ž��豸�����ܱ��¼�Ѵ���
#define E_DB_DOOR_DEV_WEEK_N			130080			//�Ž��豸�����ܱ��޴˼�¼
#define E_DOOR_DEV_WEEK_EXCEED		130081			//�Ž��豸�����ܳ�������
#define E_DOOR_DEV_WEEK_IN_USE		130082			//�Ž��豸�����ܶη����ظ�
#define E_DOOR_DEV_TIMESECT_EXCEED	130083			//�Ž�ʱ��γ�������
#define E_DB_DOOR_DEV_TMSC_R			130084			//�Ž��豸ʱ��α��ȡ����
#define E_DB_DOOR_DEV_TMSC_I			130085			//�Ž��豸ʱ��α�������
#define E_DB_DOOR_DEV_TMSC_U			130086			//�Ž��豸ʱ��α���´���
#define E_DB_DOOR_DEV_TMSC_D			130087			//�Ž��豸ʱ��α�ɾ������
#define E_DB_DOOR_DEV_TMSC_E			130088			//�Ž��豸ʱ��α��¼�Ѵ���
#define E_DB_DOOR_DEV_TMSC_N			130089			//�Ž��豸ʱ��α��޴˼�¼
#define E_DOOR_DEV_TIMESECT_INUSE  130090			//�Ž�ʱ����Ѿ�ʹ��
#define E_DOOR_DEV_TIMEGROUP_EXCEED 130091		//�Ž�ʱ����鳬������
#define E_DOOR_DEV_HOLIDAY_EXCEED	 130092			//�Ž��ڼ��ճ�������
#define E_DOOR_DEV_TIMEGROUP_INUSE 130093			//�Ž�ʱ�������ʹ��
#define E_DOOR_DEV_HOLIDAY_INUSE	130094			//�Ž��ڼ�������ʹ��
#define E_DB_DOOR_DEV_TG_R			130095			//�Ž��豸ʱ�������ȡ����
#define E_DB_DOOR_DEV_TG_I			130096			//�Ž��豸ʱ������������
#define E_DB_DOOR_DEV_TG_U			130097			//�Ž��豸ʱ��������´���
#define E_DB_DOOR_DEV_TG_D			130098			//�Ž��豸ʱ������ɾ������
#define E_DB_DOOR_DEV_TG_E			130099			//�Ž��豸ʱ�������¼�Ѵ���
#define E_DB_DOOR_DEV_TG_N			130100			//�Ž��豸ʱ�������޴˼�¼
#define E_DB_DOOR_DEV_HLD_R			130101			//�Ž����ڼ��ձ��ȡ����
#define E_DB_DOOR_DEV_HLD_I			130102			//�Ž����ڼ��ձ�������
#define E_DB_DOOR_DEV_HLD_U			130103			//�Ž����ڼ��ձ���´���
#define E_DB_DOOR_DEV_HLD_D			130104			//�Ž����ڼ��ձ�ɾ������
#define E_DB_DOOR_DEV_HLD_E			130105			//�Ž����ڼ��ձ��¼�Ѵ���
#define E_DB_DOOR_DEV_HLD_N			130106			//�Ž����ڼ��ձ�����ؼ�¼
#define E_DB_DOOR_TXDTL_R				130107			//�Ž���ˮ���ȡ����
#define E_DB_DOOR_TXDTL_I				130108			//�Ž���ˮ��������
#define E_DB_DOOR_TXDTL_U				130109			//�Ž���ˮ����´���
#define E_DB_DOOR_TXDTL_D				130110			//�Ž���ˮ��ɾ������
#define E_DB_DOOR_TXDTL_E				130111			//�Ž���ˮ���¼�Ѵ���
#define E_DB_DOOR_TXDTL_N				130112			//�Ž���ˮ������ؼ�¼
#define E_DB_DOOR_TXDTL_HIS_R			130113			//�Ž���ʷ��ˮ��ȡ����
#define E_DB_DOOR_TXDTL_HIS_I			130114			//�Ž���ʷ��ˮ�������
#define E_DB_DOOR_TXDTL_HIS_U			130115			//�Ž���ʷ��ˮ���´���
#define E_DB_DOOR_TXDTL_HIS_D			130116			//�Ž���ʷ��ˮɾ������
#define E_DB_DOOR_TXDTL_HIS_E			130117			//�Ž���ʷ��ˮ��¼�Ѵ���
#define E_DB_DOOR_TXDTL_HIS_N			130118			//�Ž���ʷ��ˮ����ؼ�¼
#define E_DB_DOOR_DEVICE_NO_RIGHT	130119			//����Աû���Ž�����Ȩ��
#define E_DB_DOOR_DEV_GRP_NO_RIGHT	130120			//����Աû���Ž������Ȩ��

#define E_INPUT_WEEK					100795			//�������ڲ���ȷ
#define E_INPUT_ERROR					100796			//�������ݲ���ȷ
#define E_INPUT_GROUP_ID				100797			//������ID����
#define E_INPUT_DEVICE_ID				100798			//�����豸ID����
#define E_INPUT_DOOR_HOLIDAY_ID		100816			//�����Ž��ڼ���ID����
#define E_DEVICE_TYPE_NOT_FIT			100817			//�豸���Ͳ���ȷ


/*************************************************************************
����ཻ�״�����
*/
#define E_FAN_ACC_INSUFFICIENT			200100			//����˻�����
#define E_FAN_ACC_NOT_EXISTS				200101			//����˻�������
#define E_FAN_OPER_INVALID					200102			//���ײ���Ա��֤ʧ��
#define E_FAN_ACC_TRADE_ERR				200103			//���ײ���ʧ��
#define E_FAN_SERIAL_NOT_EXISTS			200104			//������ˮ�Ų�����
#define E_FAN_INSUFFICIENT_PRI				200105			//����Ȩ�޲���
#define E_FAN_ALREADY_RUSHED				200106			//�Ѿ�������
#define E_FAN_SHOP_HAS_NO_LEAF			200107			//�̻���Ҷ�ӽڵ�
#define E_FAN_SHOP_NOT_INDEP				200108			//�̻����Ƕ�������
#define E_INPUT_GROUP_OR_OPER				200109			//�������Ż��߲���Ա���쳣
#define E_INPUT_NOW_OR_PAST				200110			//�������ʷ���ߵ����쳣


////////////////////////////////////////////////////////
/// ת�˺�̨������
#define  E_TRANS_BANKCARD_LOST         	108001	//���п���ʧ
#define  E_TRANS_BANKACC_STATERR        108002	//�����ʻ�״̬����
#define  E_TRANS_BANKACC_NOMONEY        108003	//���п�����
#define  E_TRANS_BANKCARD_PWDERR        108005	//���п��������
#define  E_TRANS_SCHCARD_LOST         	108101	//У԰����ʧ
#define  E_TRANS_SCHCARD_FREEZE         108102	//У԰������
#define  E_TRANS_SCHCARD_UNLOSTING      108103	//�ֿ����Ѿ�Ϊ���״̬
#define  E_TRANS_SCHCARD_LOSTING        108104	//�ֿ����Ѿ�Ϊ��ʧ״̬
#define  E_TRANS_SCHACC_NOEXIT         	108105	//��У԰���ʻ�������
#define  E_TRANS_SCHACC_DESTORY         108106	//�ֿ����Ѿ�����
#define  E_TRANS_RELATION_ERR         	108107	//��Ӧ��ϵ����
#define  E_TRANS_SCHCARD_PWDERR         108108	//У԰�������
#define  E_TRANS_TRANSMONEY_OUTRANGE    108109	//ת�ʽ�����Χ
#define  E_TRANS_ACCMONEY_OUTRANGE      108110	//У԰��������Χ
#define  E_TRANS_BANK_NODECIDE         	108111	//����δ������
#define  E_TRANS_BANK_NOANSWER         	108112	//���г�ʱ����Ӧ��
#define  E_TRANS_BANK_NETERR         	108113	//�����������
#define  E_TRANS_BANK_SERVICE_NOEXIT    108114	//����û������
#define  E_TRANS_RELATION_NOEXIT        108115	//û�ж�Ӧ��ϵ
#define  E_TRANS_FUNC_NONSUPPORT        108116	//�˹����ݲ���֧��
#define  E_TRANS_BANK_RECVERR         	108117	//���з������ݴ���
#define  E_TRANS_SCHOOL_NETERR         	108118	//У԰���������
#define  E_TRANS_INNER_TIMEOUT         	108119	//�ڲ���ʱ
#define  E_TRANS_TERM_NOLOGIN         	108120	//�ն�δ��½
#define  E_TRANS_SCHCARD_TWICE		108121	//�ͻ��ж��ſ�
#define  E_TRANS_SCHCARD_WFAIL	108122	// У԰��д��ʧ��
#define  E_DB_SUBSYSPARAMS_D               108123	//��ϵͳ������ɾ������
#define  E_DB_SUBSYSPARAMS_I                108124	//��ϵͳ������������
#define  E_DB_SUBSYSPARAMS_N               108125	//��ϵͳ�������ѯ����޼�¼
#define  E_DB_SUBSYSPARAMS_R               108126	//��ϵͳ�������ȡ����
#define  E_DB_SUBSYSPARAMS_E               108127	//��ϵͳ�������Ѵ���
#define  E_TRANS_UNKNOW_ERROR         	109000	//����δ֪����
#define E_BOC_RET_98 109001 //�����ļ������쳣����������ʻ������Ƿ������� 
#define E_BOC_RET_99 109002 //����ϵͳ��δ������ 
#define E_BOC_RET_01 109003 //�ʺ������п����ļ���δ���塣 
#define E_BOC_RET_02 109004 //��ƿ�Ŀδ������ 
#define E_BOC_RET_03 109005 //�ʺ�״̬�������� 
#define E_BOC_RET_04 109006 //ת�������ʻ������� 
#define E_BOC_RET_05 109007 //�û����벻���ڡ� 
#define E_BOC_RET_06 109008 //������������һ�ƿ�Ŀ���� 
#define E_BOC_RET_07 109009 //�������ʴ��� 
#define E_BOC_RET_08 109010 //���ڼ������ 
#define E_BOC_RET_09 109011 //���״���������RS/6000 
#define E_BOC_RET_10 109012 //������Ϣ�������� 
#define E_BOC_RET_0A 109013 //������Ϣ�������RS/6000 
//#define E_BOC_RET_0B 109014 //��δ����绰���з��� 
#define E_BOC_RET_0C 109015 //���ʺ�δ����绰���з��� 
#define E_BOC_RET_0D 109016 //�ý����ѳ����������ظ�������RS/6000 
#define E_BOC_RET_0E 109017 //�������ϵͳδ������ 
#define E_BOC_RET_0F 109018 //����������ʽ����� 
#define E_BOC_RET_0G 109019 //����Ƽ�δ���֡� 
#define E_BOC_RET_11 109020 //���״�����δ���۴��������� 
#define E_BOC_RET_12 109021 //ת�浽���ÿ��ʻ�������������ʻ��� 
#define E_BOC_RET_13 109022 //����һ��ͨ���۽��״�������20�Σ��뵽���в�ӡ���ۡ� 
#define E_BOC_RET_14 109023 //����ʻ��������� 
#define E_BOC_RET_15 109024 //��ĸ��ʻ���ֹ�ۡ� 
#define E_BOC_RET_16 109025 //����ʻ��ѱ�ɳ��ڲ��������뵽���н���� 
#define E_BOC_RET_17 109026 //��Ķ���һ��ͨ�������ѵ�60�Ρ��뵽���л����´��ۡ� 
#define E_BOC_RET_18 109027 //�ñʶ��ڴ��״̬����������������֧ȡ�� 
#define E_BOC_RET_19 109028 //�ñʴ��δ֧ȡ�����ܳ�����RS/6000. 
#define E_BOC_RET_20 109029 //���ʻ����Ǹ���֧Ʊ�ʻ��� 
#define E_BOC_RET_21 109030 //�ñʶ��ڴ��Ļ������������֧Ʊ���߽�ǿ��ʻ�������� 
#define E_BOC_RET_22 109031 //������Ϣ��������������ϵ�� 
#define E_BOC_RET_23 109032 //��֧Ʊ���Ǹ���֧Ʊ����δ������ 
#define E_BOC_RET_24 109033 //�Բ�������ʻ��ɱ������㣬��֧Ʊ���ܱ����� 
#define E_BOC_RET_25 109034 //�Բ��𣬸�֧Ʊ�ѶҸ��������ٱ����� 
#define E_BOC_RET_26 109035 //��֧Ʊδ�۳��� 
#define E_BOC_RET_27 109036 //��֧Ʊ��ֹ�ۡ� 
#define E_BOC_RET_28 109037 //�������Ӧ����ͬһ���ʺš� 
#define E_BOC_RET_29 109038 //��������ʻ������� 
#define E_BOC_RET_30 109039 //��������������Ҵ����ظ��� 
#define E_BOC_RET_31 109040 //������Ļ��Ҵ��벻�ǿɶһ��Ļ�����. 
#define E_BOC_RET_32 109041 //������δ��������Ѵ���60�� 
#define E_BOC_RET_33 109042 //������Ĵ��ڴ��� 
#define E_BOC_RET_34 109043 //�����������Ҵ����ڴ��� 
#define E_BOC_RET_35 109044 //���������Ҵ����ڴ��� 
#define E_BOC_RET_36 109045 //ת���ʺŵĻ��Ҵ����ʻ������ת���ʺŲ������ 
#define E_BOC_RET_37 109046 //֧Ʊ����δ���롣 
#define E_BOC_RET_38 109047 //��¼�Ѵ��ڣ��ظ���¼�� 
#define E_BOC_RET_39 109048 //�������ѯ���ʺš� 
#define E_BOC_RET_40 109049 //����Ҫ��ѯ�Ľ������ϲ����ڡ� 
#define E_BOC_RET_41 109050 //�����ļ�δ�򿪣����Ѷ����. 
#define E_BOC_RET_42 109051 //TRACE 
#define E_BOC_RET_43 109052 //������֧ȡ�� 
#define E_BOC_RET_44 109053 //���������� 
#define E_BOC_RET_45 109054 //��Ĵ��۽��״�������60�Σ��뵽���л����´��ۡ� 
#define E_BOC_RET_46 109055 //������Ľ����������� 
#define E_BOC_RET_A9 109056 //��Ϣ�����봦����벻�����RS/6000 
#define E_BOC_RET_S1 109057 //��Ļ���һ��ͨ�ʺ�δ����绰���з��� 
#define E_BOC_RET_S2 109058 //��ĸ���֧Ʊ�ʺ�δ����绰���з��� 
#define E_BOC_RET_S3 109059 //��Ķ���һ��ͨ�ʺ�δ����绰���з��� 
#define E_BOC_RET_S4 109060 //������ÿ��ʺ�δ����绰���з��� 
#define E_BOC_RET_S5 109061 //��Ľ�ǿ��ʺ�δ����绰���з��� 
#define E_BOC_RET_R0 109062 //������¼δ���֣�TRACE 
#define E_BOC_RET_R1 109063 //�ʻ����㣬���ܳ����� 
#define E_BOC_RET_R2 109064 //����������RS/6000 
#define E_BOC_RET_R3 109065 //���������Ŵ���RS/6000 
#define E_BOC_RET_R4 109066 //�ý��ײ����������RS/6000 
#define E_BOC_RET_W3 109067 //��ѯ�������ʳ���50�ʡ� 
#define E_BOC_RET_W4 109068 //��ѯ�Ĵ�����ϳ���50�ʣ���������һ�ʴ�����š�RS/6000 
#define E_BOC_RET_W1 109069 //��ѯ��ʷ�������ϳ���60�ʣ��������������š�RS/6000 
#define E_BOC_RET_W5 109070 //�Թ���ѯ���������ϳ���11�ʣ��������ѯ 
#define E_BOC_RET_W2 109071 //����һ��ͨ�������ѹ�60�Σ����㵽���л����´��ۡ� 
#define E_BOC_RET_W8 109072 //������ѯ�ĶԹ���ʷ���ײ��ɹ��� 
#define E_BOC_RET_61 109073 //�޷�������Ϣ���С� 
#define E_BOC_RET_62 109074 //�޷����������ڴ� 
#define E_BOC_RET_63 109075 //�޷������źŵ� 
#define E_BOC_RET_64 109076 //���ݿ�������� 
#define E_BOC_RET_65 109077 //д��Ϣ����ʧ�� 
#define E_BOC_RET_66 109078 //ȡ��򿪻�ʱ����ǿ�������� 
#define E_BOC_RET_67 109079 //����Ϣ����ʧ�� 
#define E_BOC_RET_68 109080 //ϵͳͣ�� 
//#define E_BOC_RET_69 109081 //ǰ�������Ӧ��ϵͳͣ�� 
#define E_BOC_RET_80 109082 //�ʻ������ 
#define E_BOC_RET_70 109083 //8583���ݴ��� 
#define E_BOC_RET_71 109084 //��Ч������ѯ 
#define E_BOC_RET_72 109085 //��������ʧ�� 
#define E_BOC_RET_73 109086 //�û�δ������ȯת�ʷ��� 
//#define E_BOC_RET_74 109087 //ǰ�������Ӧ��ϵͳͨ���жϡ� 
#define E_BOC_RET_75 109088 //��������ͨ���жϡ� 
#define E_BOC_RET_76 109089 //����������ǩ�ˡ� 
#define E_BOC_RET_M1 109090 //�Ƿ����ġ� 
#define E_BOC_RET_M2 109091 //�޴��ն� 
#define E_BOC_RET_M3 109092 //�޴˲���Ա 
#define E_BOC_RET_M4 109093 //���ʻ��ѹ��� 
#define E_BOC_RET_M5 109094 //��Ч��� 
#define E_BOC_RET_M6 109095 //����������޴� 
#define E_BOC_RET_M7 109096 //����������޶� 
#define E_BOC_RET_M8 109097 //�ʻ�δ�Ǽ� 
#define E_BOC_RET_M9 109098 //�ʻ��Ǽǲ�ƥ�� 
#define E_BOC_RET_M0 109099 //֤ȯϵͳ���� 
#define E_BOC_RET_MA 109100 //���֤���� 
#define E_BOC_RET_MB 109101 //��Ӧ��ϵͳ����ͨ�Ŵ��� 
#define E_BOC_RET_MC 109102 //����֤ȯ�������� 
#define E_BOC_RET_MD 109103 //��Ӧ��ϵͳͨ�����ݸ�ʽ���� 
#define E_BOC_RET_F1 109104 //����������ɹ� 
#define E_BOC_RET_F2 109105 //��������Ļ�ۣ����н����޷����� 
#define E_BOC_RET_F3 109106 //ί�е�������������ѳɹ��ɽ����ҵ��� 
#define E_BOC_RET_W7 109107 //ί�е���������ҵ����׼�ʱ�ɹ��ɽ� 
#define E_BOC_RET_F4 109108 //�Ƿ�������������� 
#define E_BOC_RET_F5 109109 //�Ƿ������������������ 
#define E_BOC_RET_F6 109110 //��������Ļ��ң����ղ��ܽ������������ 
#define E_BOC_RET_F7 109111 //�������ɻ�����������޶�õ��ڶ�����Ԫ 
#define E_BOC_RET_F8 109112 //��ʿ���ɻ�����������޶�õ��ڶ�����Ԫ 
#define E_BOC_RET_FA 109113 //�������ί�н����ѳ��� 
#define E_BOC_RET_FB 109114 //�������ί�н��ײ����ڡ� 
#define E_BOC_RET_FC 109115 //�������ί�н��׳ɽ�ʧ�ܡ� 
#define E_BOC_RET_FD 109116 //�������ί�н���δ�ɽ��� 
#define E_BOC_RET_C1 109117 //��Ч�Ŀ��š� 
#define E_BOC_RET_C2 109118 //��ѯ���ÿ���ʷ����ʱ�����������ѯ��ֹ���ڡ� 
#define E_BOC_RET_X1 109119 //���ÿ��ʻ��������뷢������ϵ�� 
#define E_BOC_RET_X4 109120 //��ѯ���ÿ�����ʧ�ܡ� 
#define E_BOC_RET_R8 109121 //���ÿ���ȡ�����ʧ�ܡ� 
#define E_BOC_RET_W6 109122 //�������ÿ��ʻ�͸֧���Ϊ�� 
#define E_BOC_RET_52 109123 //��ѯ���ÿ�����ʧ�ܡ� 
#define E_BOC_RET_Z1 109124 //�ѿ������ظ����� 
#define E_BOC_RET_Z3 109125 //���ϲ����� 
#define E_BOC_RET_Z0 109126 //������ 
#define E_BOC_RET_Z2 109127 //δ��Ԥ���� 
#define E_BOC_RET_74 109128 //ͨѶ״̬�� 
#define E_BOC_RET_69 109129 //δǩ�� 
#define E_BOC_RET_T0 109130 //����ģʽ�� 
#define E_BOC_RET_Z5 109131 //�ɷ����ϲ����� 
#define E_BOC_RET_Z6 109132 //�ѽɷ� 
#define E_BOC_RET_Z7 109133 //δ�ɷ� 
#define E_BOC_RET_P4 109134 //����� 
#define E_BOC_RET_PX 109135 //�ʻ����� 
#define E_BOC_RET_P6 109136 //���Ŵ� 
#define E_BOC_RET_Z9 109137 //����ʧ�� 
#define E_BOC_RET_Z8 109138 //���ڽ��н��Ѵ��� 
#define E_BOC_RET_ZA 109139 //��˾����� 
#define E_BOC_RET_ZC 109140 //��˾����� 
#define E_BOC_RET_ZZ 109141 //���ʲ�ƽ 
#define E_BOC_RET_T1 109142 //����ʱ��� 
#define E_BOC_RET_T2 109143 //Ԥ�������� 
#define E_BOC_RET_P0 109144 //���ʴ��� 
#define E_BOC_RET_P1 109145 //���»��������� 
#define E_BOC_RET_P2 109146 //�����ʺŲ����� 
#define E_BOC_RET_P3 109147 //�����ڵ��� 
#define E_BOC_RET_P5 109148 //��ǿ�״̬������ 
#define E_BOC_RET_P7 109149 //����ǿ������� 
#define E_BOC_RET_P8 109150 //дATMLOG���� 
#define E_BOC_RET_P9 109151 //����״̬������ 
#define E_BOC_RET_Q0 109152 //δ����绰���з��� 
#define E_BOC_RET_Q1 109153 //�ÿͻ������� 
#define E_BOC_RET_Q2 109154 //�ͻ���¼δ���� 
#define E_BOC_RET_Q3 109155 //���ͻ����� 
#define E_BOC_RET_Q4 109156 //�û����ʺŷǿͻ������ʺ� 
#define E_BOC_RET_Q5 109157 //д�ļ���ֵ�ظ� 
#define E_BOC_RET_Q8 109158 //�ʻ����� 
#define E_BOC_RET_Q9 109159 //��Ա�ֽ��� 
#define E_BOC_RET_ME 109160 //�ֻ��Ų����� 
#define E_BOC_RET_N1 109161 //�ͻ�״̬������ 
#define E_BOC_RET_N2 109162 //д�ֽ��ظ� 
#define E_BOC_RET_N3 109163 //д�ֽ𵵳��� 
#define E_BOC_RET_N4 109164 //Ԥ���ѽ������ʹ� 
#define E_BOC_RET_77 109165 //��ȡ�����ļ�ʧ�� 
#define E_BOC_RET_0B 109166 //δ������� 
#define E_BOC_RET_81 109167 //Ӧ��ϵͳ���ش��� 


#define E_MOBILE_TRANS_REQUEST 109168 //��ֵ������ʧ��
#define E_MOBILE_TRANS_CONNECT 109169 //��ֵ��������ʧ��
#define E_MOBILE_TRANS_NOT_CONNECT 109170 //��ֵ�����������
#define E_MOBILE_TRANS_TIME_OUT 109171 //��ֵ����ʱ��Ӧ��
#define E_MOBILE_CHECK_MAC 109172 //macУ�����
#define E_MOBILE_CHECK_FAIL 109173 //�ֻ����벻��ȷ
#define E_MOBILE_CHECK_UNKNOW 109174 //�ƶ��������ݴ���
#define E_MOBILE_TRANS_FAILURE 109175 //��ֵʧ��

#define E_ELEC_DB_CONN	109176 //���ݿ����Ӵ���
#define E_ELEC_CARD	109177 //һ��ͨ�˺��뷿�䲻��Ӧ
#define E_ELEC_ROOM	109178 // �����ڵķ���
#define E_ELEC_WORKSTAT 109179 //�����ڹ���վ
#define E_ELEC_DATA	109180 //����У�����
#define E_ELEC_DATA_LOSS 109181 //���ݶ�ʧ
#define E_ELEC_UNKNOW	109182 //δ֪����
#define E_TRANS_REQUEST 109183 //������ʧ��
#define E_TRANS_CONNECT 109184 //��������ʧ��
#define E_TRANS_NOT_CONNECT 109185 //�����������
#define E_TRANS_TIME_OUT 109186 //����ʱ��Ӧ��

#define E_INVALID_SHOP 109200 	//��Ч�̻�
#define E_CVN_FAILED 109201 	//CVNЧ��ʧ��
#define E_TRADE_FAILED 109202 	//���׳���
#define E_INVALIED_TRADE 109203 	//��Ч����
#define E_INVALIED_MONEY 109204 	//��Ч���
#define E_INVALIED_CARD 109205 	//��Ч����
#define E_TROUBLE_DOUBT 109206 	//���ϻ���
#define E_FIND_INIT_TRADE 109207 	//�Ҳ���ԭʼ����
#define E_OUTOFPIN_INPUT 109208 	//��������ĵ�PIN����
#define E_BANK_CARD_LOST 109209 	//�ÿ��Ѿ���ʧ
#define E_NO_BANK_ACCOUNT 109210 	//�������˻�
#define E_FUNDS_SHORTAGE 109211 	//�ʽ��ȱ
#define E_CARD_OUTOFDATE 109212 	//���ڿ�
#define E_INVALID_PIN 	109213 		//��Ч��PIN����
#define E_CARDHOLDER_TRADE 	109214 		//������ֿ��˽��н���
#define E_OUTOF_TRADE_COUNTS 	109215 		//�������״���
#define E_BANK_SETTLE_ACCOUNTS 	109216 		//�������ս���
#define E_BANK_MAC_FAILED 	109217 		//MACЧ��ʧ��
#define E_CONNECT_PUBLISH_BANK 	109218 		//���뷢������ϵ


#endif
