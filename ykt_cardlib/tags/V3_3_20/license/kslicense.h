#if !defined(_kslicense_h_)
#define _kslicense_h_

#include <map>
#include <list>
#include <string>
#include "openssl/rsa.h"




#define LCS_OK 0
#define LCS_FILE_ERR 1 // 文件格式错误
#define LCS_DECRYPT_ERR 2 // 解密错误
#define LCS_ENCRYPT_ERR 3 // 加密错误
#define LCS_VERIFY_ERR 4 // 校验文件错误
#define LCS_WRITE_FILE_ERR 5 // 写文件错误
#define LCS_READ_FILE_ERR 6 // 读文件错误
#define LCS_MEMORY_ERR 7 // 内存操作出错
#define LCS_UNAUTH_ERR 8 // 未授权
#define LCS_NOFILENAME_ERR 9 // 未指定文件名
#define LCS_PARAM_NOSET 10 // 参数未设置
#define LCS_NOTSUPPORT 11 // 不支持的操作或者参数
#define LCS_PARAM_FORMAT_ERR 12 // 参数格式错误
#define LCS_LECK_MEMORY 13 // 申请内存错误


typedef struct {
	std::string param_name;
	std::string param_summary;
	std::string param_value;
	int param_flag;
}ks_cllcns_param_t;

typedef std::map<std::string,std::string> STRING_MAP_TYPE;
typedef std::map<std::string,ks_cllcns_param_t> LICENSE_PARAM_TYPE;
// 权限模块
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
	// 加载 public key 文件
	int load_public_key_file(const char *key_path = NULL);
	// 使用key 值直接授权
	int set_public_key(const char *key);
	// 加载 private key 文件
	int load_private_key_file(const char *key_path = NULL);
	// 加载授权文件
	int load_license_file(const char *lc_path = NULL);
	// 获取授权文件中的公共参数
	int get_public_param(const char *param_name,char *param_value,int maxlen);
	int get_public_int_param(const char *param_name,int *param_value);
	// 获取所有参数名
	int get_all_parameters(std::list<ks_cllcns_param_t> &params);
	// 获取授权文件中的私有参数
	int get_private_param(const char *key,const char *param_name,char *param_value,int maxlen);
	// 更新授权文件中的公共参数
	int update_public_param(const char *param_name,const char *param_summary,char *param_value);
	// 更新授权文件中的私有参数
	int update_private_param(const char *key,const char *param_name,const char *param_summary,char *param_value);
	// 生成密钥文件
	int generate_key_file(const char *privkey,const char *pubkey);
	// 保存license文件
	int save_license_file(const char *license_file = NULL);
	// 删除密钥
	int delete_param(const char *param_name);
	void delete_all_param();
};
#endif // _kslicense_h_

