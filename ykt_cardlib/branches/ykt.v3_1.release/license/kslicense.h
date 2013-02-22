#if !defined(_kslicense_h_)
#define _kslicense_h_

#include <map>
#include <list>
#include <string>
#include "openssl/rsa.h"




#define LCS_OK 0
#define LCS_FILE_ERR 1 // �ļ���ʽ����
#define LCS_DECRYPT_ERR 2 // ���ܴ���
#define LCS_ENCRYPT_ERR 3 // ���ܴ���
#define LCS_VERIFY_ERR 4 // У���ļ�����
#define LCS_WRITE_FILE_ERR 5 // д�ļ�����
#define LCS_READ_FILE_ERR 6 // ���ļ�����
#define LCS_MEMORY_ERR 7 // �ڴ��������
#define LCS_UNAUTH_ERR 8 // δ��Ȩ
#define LCS_NOFILENAME_ERR 9 // δָ���ļ���
#define LCS_PARAM_NOSET 10 // ����δ����
#define LCS_NOTSUPPORT 11 // ��֧�ֵĲ������߲���
#define LCS_PARAM_FORMAT_ERR 12 // ������ʽ����
#define LCS_LECK_MEMORY 13 // �����ڴ����


typedef struct {
	std::string param_name;
	std::string param_summary;
	std::string param_value;
	int param_flag;
}ks_cllcns_param_t;

typedef std::map<std::string,std::string> STRING_MAP_TYPE;
typedef std::map<std::string,ks_cllcns_param_t> LICENSE_PARAM_TYPE;
// Ȩ��ģ��
class ks_cardlib_license
{
public:
	ks_cardlib_license();
	~ks_cardlib_license();
	typedef enum {PARAM_PUB=0,PARAM_PRIV=1} PARAM_FLAG;

	static const char LCNS_HEADER[];
	static const char LCNS_SEP;
	static const char LCNS_EXPIRED_DATE[];
	static const char LCNS_CUST_ID[];
	static const char LCNS_VERSION[];
	static const int LCNS_VER_LEN = 4;
	static const long LCNS_MAX_FILE_SIZE = 1024 * 1024;
	static const long LCNS_PARAM_MAX_LEN = 2048;
	static const long LCNS_EXTEND_SIZE = 2048;
private:
	std::string m_public_key_file;
	std::string m_private_key_file;
	std::string m_license_file;
	LICENSE_PARAM_TYPE m_public_param;
	LICENSE_PARAM_TYPE m_private_param;
	RSA *m_public_rsa;
	RSA *m_private_rsa;
	char m_license_ver[20];
	int m_is_load_pub_key;
	int m_is_load_priv_key;
	unsigned char * m_file_buffer;
	int m_file_buffer_size;
	int m_file_buffer_pos;
	int m_file_buffer_len;
	int m_current_file_size;
	int make_rsa();
	void free_rsa();
	void free_pub_rsa();
	void free_priv_rsa();
	int load_publickey();
	int load_privatekey();
	int decrypt_license_file(FILE *fp);
	int save_key_2_file(const char *file,const unsigned char *key,int key_len);
	int save_license_2_file(FILE *fp);
	int save_license_header(FILE *fp);
	int save_public_param(FILE *fp);
	int save_private_param(FILE *fp);
	inline int write_file(FILE *fp,const unsigned char *buf,int len);
	int load_license_header(FILE *fp,int &pos);
	int load_license_data(FILE *fp,int &pos);
	inline int read_file(FILE *fp,unsigned char *buf,int &len);
	inline int do_update_public_param(const char *param_name,const char *param_value,const char *param_comments);
	inline int extend_file_buffer(int size);
	inline void free_file_buffer();
	int parse_data_file(const char *decrypt_buffer,std::string &value,int &pos);
	int save_data_file(unsigned char *encrypt_buffer,const std::string &value,int &pos);
public:
	inline int is_load_pubkey() const { return m_is_load_pub_key == 1; }
	inline int is_load_privkey() const { return m_is_load_priv_key == 1; }
	// ���� public key �ļ�
	int load_public_key_file(const char *key_path = NULL);
	// ʹ��key ֱֵ����Ȩ
	int set_public_key(const char *key);
	// ���� private key �ļ�
	int load_private_key_file(const char *key_path = NULL);
	// ������Ȩ�ļ�
	int load_license_file(const char *lc_path = NULL);
	// ��ȡ��Ȩ�ļ��еĹ�������
	int get_public_param(const char *param_name,char *param_value,int maxlen);
	int get_public_int_param(const char *param_name,int *param_value);
	// ��ȡ���в�����
	int get_all_parameters(std::list<ks_cllcns_param_t> &params);
	// ��ȡ��Ȩ�ļ��е�˽�в���
	int get_private_param(const char *key,const char *param_name,char *param_value,int maxlen);
	// ������Ȩ�ļ��еĹ�������
	int update_public_param(const char *param_name,const char *param_summary,char *param_value);
	// ������Ȩ�ļ��е�˽�в���
	int update_private_param(const char *key,const char *param_name,const char *param_summary,char *param_value);
	// ������Կ�ļ�
	int generate_key_file(const char *privkey,const char *pubkey);
	// ����license�ļ�
	int save_license_file(const char *license_file = NULL);
	// ɾ����Կ
	int delete_param(const char *param_name);
	void delete_all_param();
};
#endif // _kslicense_h_

