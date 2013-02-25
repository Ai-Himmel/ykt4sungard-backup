#include "kslicense.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "openssl/err.h"

#ifndef u_char
#define u_char unsigned char
#endif // u_char

const char ks_cardlib_license::LCNS_HEADER[] = "KSYKTLC";
const char ks_cardlib_license::LCNS_SEP = ':';
const char ks_cardlib_license::LCNS_EXPIRED_DATE[]="kscardlib.expired";
const char ks_cardlib_license::LCNS_CUST_ID[]="kscardlib.custid";
const char ks_cardlib_license::LCNS_VERSION[]="kscardlib.version";

ks_cardlib_license::ks_cardlib_license():m_public_rsa(NULL),m_private_rsa(NULL),
    m_is_load_pub_key(0),m_private_key_file(""),
    m_public_key_file(""),m_license_file(""),m_file_buffer(NULL),m_current_file_size(0),
    m_file_buffer_len(0),m_file_buffer_pos(0),m_file_buffer_size(0),m_is_load_priv_key(0) {
    //
    strcpy(m_license_ver,"1000");
}
ks_cardlib_license::~ks_cardlib_license() {
    free_file_buffer();
}

int ks_cardlib_license::make_rsa() {
    free_rsa();
    m_public_rsa = RSA_new();
    if(m_public_rsa == NULL)
        return LCS_MEMORY_ERR;
    m_private_rsa = RSA_new();
    if(m_private_rsa == NULL)
        return LCS_MEMORY_ERR;
    return 0;
}
void ks_cardlib_license::free_priv_rsa() {
    if(m_private_rsa != NULL) {
        RSA_free(m_private_rsa);
        m_private_rsa = NULL;
        m_is_load_priv_key = 0;
    }
}
void ks_cardlib_license::free_pub_rsa() {
    if(m_public_rsa != NULL) {
        RSA_free(m_public_rsa);
        m_public_rsa = NULL;
        m_is_load_pub_key = 0;
    }
}
void ks_cardlib_license::free_rsa() {
    free_priv_rsa();
    free_pub_rsa();
}
int ks_cardlib_license::load_publickey() {
    unsigned char buffer[2048];
    unsigned char *p;
    int ret;
    FILE *fp;
    fp = fopen(m_public_key_file.c_str(),"rb");
    if(fp == NULL)
        return LCS_READ_FILE_ERR;

    ret = fread(buffer,1,sizeof(buffer),fp);
    if(ret <= 0) {
        fclose(fp);
        return LCS_READ_FILE_ERR;
    }
    fclose(fp);

    p = buffer;
    m_public_rsa = d2i_RSAPublicKey(NULL,(const unsigned char**)&p,(long)ret);
    if(m_public_rsa == NULL)
        return LCS_VERIFY_ERR;
    return 0;
}
int ks_cardlib_license::load_public_key_file(const char *key_path /* = NULL */ ) {
    int ret;
    if(is_load_pubkey()) {
        free_pub_rsa();
    }
    m_public_key_file=key_path;
    ret = load_publickey();
    if(!ret)
        m_is_load_pub_key = 1;
    return ret;
}
// 使用key 值直接授权
int ks_cardlib_license::set_public_key(const char *key) {
    return -1;
}
int ks_cardlib_license::load_privatekey() {
    unsigned char buffer[2048];
    unsigned char *p;
    int ret;
    FILE *fp;
    fp = fopen(m_private_key_file.c_str(),"rb");
    if(fp == NULL)
        return LCS_READ_FILE_ERR;

    ret = fread(buffer,1,sizeof(buffer),fp);
    if(ret <= 0) {
        fclose(fp);
        return LCS_READ_FILE_ERR;
    }
    fclose(fp);

    p = buffer;
    m_private_rsa = d2i_RSAPrivateKey(NULL,(const unsigned char**)&p,(long)ret);
    if(m_private_rsa == NULL)
        return LCS_VERIFY_ERR;
    return 0;
}
// 加载 private key 文件
int ks_cardlib_license::load_private_key_file(const char *key_path /*= NULL*/) {
    int ret;
    if(is_load_privkey()) {
        free_priv_rsa();
    }
    m_private_key_file=key_path;
    ret = load_privatekey();
    if(!ret)
        m_is_load_priv_key = 1;
    return ret;
}

inline int ks_cardlib_license::read_file(FILE *fp,unsigned char *buf,int &len) {
    int read_len,max_len;
    max_len = len;
    read_len = 0;
    len = 0;
    do {
        read_len = fread(buf+len,1,max_len-len,fp);
        if(read_len == 0) {
            return 0;
        } else if(read_len < 0)
            return -1;
        len += read_len;
    } while(len < max_len);
    return 0;
}

inline int ks_cardlib_license::extend_file_buffer(int size) {
    void * p;
    if(m_file_buffer == NULL) {
        p = malloc(size);
        if(p == NULL) return LCS_LECK_MEMORY;
        m_file_buffer = (unsigned char*)p;
        m_file_buffer_size = size;
        m_file_buffer_len = 0;
    } else {
        m_file_buffer_size += size;
        p = realloc(m_file_buffer,m_file_buffer_size);
        if(p == NULL) return LCS_LECK_MEMORY;
        m_file_buffer = (unsigned char*) p;
    }
    return 0;
}
inline void ks_cardlib_license::free_file_buffer() {
    if(m_file_buffer != NULL) {
        free(m_file_buffer);
        m_file_buffer = NULL;
        m_file_buffer_size = 0;
        m_file_buffer_len = 0;
    }
}

int ks_cardlib_license::decrypt_license_file(FILE *fp) {
    int buffer_sect = 256;
    u_char decrypt_buffer[1024];
    u_char buffer[1024];
    int len,ret;
    memset(buffer,0,sizeof buffer);

    free_file_buffer();
    buffer_sect = BN_num_bytes(m_public_rsa->n);
    extend_file_buffer(buffer_sect);
    len = 0;
    do {
        len = buffer_sect;
        if(read_file(fp,buffer,len))
            return LCS_READ_FILE_ERR;
        if(len == 0)
            return 0;
#if 0
        if(len < sizeof(buffer) || (len + m_file_buffer_len >= m_current_file_size) ) {
            len = RSA_public_decrypt(len,buffer,decrypt_buffer,m_public_rsa,RSA_PKCS1_PADDING);
        } else {
            len = RSA_public_decrypt(len,buffer,decrypt_buffer,m_public_rsa,RSA_NO_PADDING);
        }
#else
        ret = len;
        len = RSA_public_decrypt(len,buffer,decrypt_buffer,m_public_rsa,RSA_PKCS1_PADDING);

        if(len == -1) {
            len = RSA_public_decrypt(ret,buffer,decrypt_buffer,m_public_rsa,RSA_NO_PADDING);
        }

#endif
        if(len == -1)
            return LCS_DECRYPT_ERR;
        if(m_file_buffer_len + len > m_file_buffer_size) {
            ret = extend_file_buffer(buffer_sect);
            if(ret)
                return ret;
        }
        memcpy(m_file_buffer+m_file_buffer_len,decrypt_buffer,len);
        m_file_buffer_len += len;
        // 不支持文件大小超过1M
        if(m_file_buffer_len > LCNS_MAX_FILE_SIZE)
            return LCS_NOTSUPPORT;
    } while(1);
    return 0;
}

int ks_cardlib_license::load_license_header(FILE *fp,int &pos) {
    char temp[256];
    char *p;
    int offset;
    char *decrypt_buffer;
    decrypt_buffer = (char*)m_file_buffer;
    offset = 0;
    // 文件头
    if(memcmp(LCNS_HEADER,decrypt_buffer,strlen(LCNS_HEADER))!=0) {
        return LCS_VERIFY_ERR;
    }
    offset += strlen(LCNS_HEADER);
    if(decrypt_buffer[offset++] != LCNS_SEP)
        return LCS_VERIFY_ERR;
    // 版本号
    memset(temp,0,sizeof temp);
    memcpy(temp,decrypt_buffer+offset,LCNS_VER_LEN);
    do_update_public_param(LCNS_VERSION,temp,NULL);
    offset += LCNS_VER_LEN;
    // 有效期
    if(decrypt_buffer[offset++] != LCNS_SEP)
        return LCS_VERIFY_ERR;
    memset(temp,0,sizeof temp);
    p = strchr(decrypt_buffer+offset,LCNS_SEP);
    if(p==NULL)
        return LCS_VERIFY_ERR;
    assert( (p-decrypt_buffer-offset) <= sizeof(temp) );
    memcpy(temp,decrypt_buffer+offset,p-decrypt_buffer-offset);
    do_update_public_param(LCNS_EXPIRED_DATE,temp,NULL);
    offset += p-decrypt_buffer-offset;
    // 客户标识
    if(decrypt_buffer[offset++] != LCNS_SEP)
        return LCS_VERIFY_ERR;
    memset(temp,0,sizeof temp);
    p = strchr(decrypt_buffer+offset,LCNS_SEP);
    if(p==NULL)
        return LCS_VERIFY_ERR;
    assert( (p-decrypt_buffer-offset) <= sizeof(temp) );
    memcpy(temp,decrypt_buffer+offset,p-decrypt_buffer-offset);
    do_update_public_param(LCNS_CUST_ID,temp,NULL);
    offset += p-decrypt_buffer-offset;
    pos = offset;
    return 0;

}
int ks_cardlib_license::parse_data_file(const char *decrypt_buffer,std::string &value,int &pos) {
    int offset,len,x;
    char temp[64];
    char *p;
    offset = 0;
    if(decrypt_buffer[offset++] != LCNS_SEP)
        return LCS_PARAM_FORMAT_ERR;

    memset(temp,0,sizeof temp);
    p = (char*)strchr(decrypt_buffer+offset,LCNS_SEP);
    if(p == NULL)
        return LCS_PARAM_FORMAT_ERR;
    switch(decrypt_buffer[offset]) {
    case 's':
        // for string
        offset++;
        break;
    case 'd':
        offset++;
        break;
    case 'i':
        offset++;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        break;
    default:
        return LCS_PARAM_FORMAT_ERR;
    }
    len = p-decrypt_buffer-offset;
    memcpy(temp,decrypt_buffer+offset,len);
    offset += len;
    x = atoi(temp);
    if(x > LCNS_PARAM_MAX_LEN || x < 0)
        return LCS_PARAM_FORMAT_ERR;
    if(decrypt_buffer[offset++] != LCNS_SEP)
        return LCS_PARAM_FORMAT_ERR;
    value = std::string(decrypt_buffer+offset,x);
    pos = offset+x;
    return 0;
}
int ks_cardlib_license::load_license_data(FILE *fp,int &pos) {
    int read_len,offset,ret;
    char *decrypt_buffer;
    decrypt_buffer = (char*)(m_file_buffer + pos);
    std::string pname,psummary,pvalue;
    offset = 0;
    // 分析参数
    do {
        ret=parse_data_file(decrypt_buffer+offset,pname,read_len);
        if(ret)
            return ret;
        assert(offset + read_len <= m_file_buffer_len);
        offset += read_len;

        ret = parse_data_file(decrypt_buffer+offset,psummary,read_len);
        if(ret)
            return ret;
        assert(offset + read_len <= m_file_buffer_len);
        offset += read_len;

        ret = parse_data_file(decrypt_buffer+offset,pvalue,read_len);
        if(ret)
            return ret;
        assert(offset + read_len <= m_file_buffer_len);
        offset += read_len;

        ret = do_update_public_param(pname.c_str(),pvalue.c_str(),psummary.c_str());
        if(ret)
            return ret;

    } while(offset + pos < m_file_buffer_len);
    return 0;
}

// 加载授权文件
int ks_cardlib_license::load_license_file(const char *lc_path /*= NULL*/) {
    FILE *fp;
    int ret,pos;
    if(is_load_pubkey()==0) {
        return LCS_UNAUTH_ERR;
    }
    if(m_file_buffer != NULL) {
        free(m_file_buffer);
        m_file_buffer  = NULL;
    }

    m_license_file = lc_path;

    fp = fopen(lc_path,"rb");
    if(fp == NULL)
        return LCS_READ_FILE_ERR;

    fseek(fp,0L,SEEK_END);
    m_current_file_size = ftell(fp);
    fseek(fp,0L,SEEK_SET);

    ret = decrypt_license_file(fp);

    fclose(fp);

    if(ret)
        return ret;

    ret = load_license_header(fp,pos);
    if(ret)
        return ret;
    ret = load_license_data(fp,pos);
    if(ret)
        return ret;
    if(m_file_buffer != NULL) {
        free(m_file_buffer);
        m_file_buffer  = NULL;
    }
    return 0;
}
// 获取授权文件中的公共参数
int ks_cardlib_license::get_public_param(const char *param_name,char *param_value,int maxlen) {
    LICENSE_PARAM_TYPE::const_iterator iter;
    ks_cllcns_param_t param;
    iter = m_public_param.find(param_name);
    if(iter == m_public_param.end())
        return -1;
    param = iter->second;
    strncpy(param_value,param.param_value.c_str(),maxlen);
    return 0;

}
// 获取授权文件中的私有参数
int ks_cardlib_license::get_private_param(const char *key,const char *param_name,char *param_value,int maxlen) {
    return -1;
}
inline int ks_cardlib_license::do_update_public_param(const char *param_name,const char *param_value,
        const char *param_comments) {
    assert(param_name != NULL);
    assert(param_value != NULL);
    LICENSE_PARAM_TYPE::iterator iter;
    ks_cllcns_param_t param;
    iter = m_public_param.find(param_name);
    if(iter != m_public_param.end()) {
        m_public_param.erase(iter);
    }
    param.param_name = param_name;
    param.param_flag = PARAM_PUB;
    param.param_value = param_value;
    if(param_comments != NULL)
        param.param_summary = param_comments;
    m_public_param.insert(LICENSE_PARAM_TYPE::value_type(param_name,param));
    return 0;
}
// 更新授权文件中的公共参数
int ks_cardlib_license::update_public_param(const char *param_name,const char *param_summary,char *param_value) {
    if(strcmp(param_name,LCNS_VERSION)==0
      )
        return LCS_NOTSUPPORT;
    return do_update_public_param(param_name,param_value,param_summary);
}
// 更新授权文件中的私有参数
int ks_cardlib_license::update_private_param(const char *key,const char *param_name,
        const char *param_summary,char *param_value) {
    return -1;
}

static void  genkey_callback(int stage,int count,void *arg) {
    FILE *out;
    out=(FILE *)arg;
    fprintf(out,"%d",stage);
    if (stage == 3)
        fprintf(out,"\n");
    fflush(out);
}

int ks_cardlib_license::save_key_2_file(const char *file,const unsigned char *key,int key_len) {
    FILE *fp;
    int ret;
    fp = fopen(file,"w+b");
    if(fp==NULL)
        return LCS_WRITE_FILE_ERR;

    ret = fwrite(key,key_len,1,fp);
    if(ret != 1) {
        ret = LCS_WRITE_FILE_ERR;
    } else {
        ret = 0;
    }
    fclose(fp);
    return ret;
}

int ks_cardlib_license::generate_key_file(const char *privkey,const char *pubkey) {
    int ret,len,len2;
    unsigned char buffer[4096];
    unsigned char *p;
    RSA *rsa;

    rsa = RSA_generate_key(2048,65537,genkey_callback,(char*)stdout);
    p = buffer;

    len=i2d_RSAPublicKey(rsa,&p);
    ret = save_key_2_file(pubkey,buffer,len);
    if(ret) {
        RSA_free(rsa);
        return ret;
    }

    len2=i2d_RSAPrivateKey(rsa,&p);
    ret = save_key_2_file(privkey,buffer+len,len2);
    if(ret) {
        RSA_free(rsa);
        return ret;
    }
    RSA_free(rsa);
    return 0;
}

int ks_cardlib_license::get_all_parameters(std::list<ks_cllcns_param_t> &params) {
    LICENSE_PARAM_TYPE::const_iterator iter;
    ks_cllcns_param_t param;
    for(iter = m_public_param.begin(); iter != m_public_param.end(); ++iter) {
        param = iter->second;
        params.push_back(param);
    }
    for(iter = m_private_param.begin(); iter != m_private_param.end(); ++iter) {
        param = iter->second;
        params.push_back(param);
    }
    return 0;
}

int ks_cardlib_license::save_license_file(const char *license_file /*= NULL*/) {
    FILE *fp;
    int ret;
    std::string wr_file;
    std::string tmp_file;
    if(m_file_buffer != NULL) {
        free(m_file_buffer);
        m_file_buffer  = NULL;
    }
    if(license_file != NULL)
        wr_file = license_file;
    else if(!m_license_file.empty()) {
        wr_file = m_license_file;
    } else {
        return LCS_NOFILENAME_ERR;
    }

    tmp_file = wr_file + ".tmp";
    fp = fopen(tmp_file.c_str(),"w+b");
    if(fp==NULL)
        return LCS_WRITE_FILE_ERR;
    ret = save_license_2_file(fp);
    fclose(fp);
    if(ret==0) {
#ifdef WIN32
        if(_unlink(wr_file.c_str()))
            return LCS_WRITE_FILE_ERR;
#else
        if(unlink(wr_file.c_str()))
            return LCS_WRITE_FILE_ERR;
#endif
        if(rename(tmp_file.c_str(),wr_file.c_str()))
            return LCS_WRITE_FILE_ERR;
    }
    if(m_file_buffer != NULL) {
        free(m_file_buffer);
        m_file_buffer  = NULL;
    }
    return ret;
}
int ks_cardlib_license::save_license_header(FILE *fp) {
    u_char buffer[1024];
    LICENSE_PARAM_TYPE::const_iterator iter;
    ks_cllcns_param_t param;
    int offset;
    offset = 0;
    memcpy(buffer,LCNS_HEADER,strlen(LCNS_HEADER));
    offset += strlen(LCNS_HEADER);
    buffer[offset++] = LCNS_SEP;

    //
    memcpy(buffer+offset,m_license_ver,strlen(m_license_ver));
    offset += strlen(m_license_ver);
    buffer[offset++] = LCNS_SEP;
    // 有效期
    iter = m_public_param.find(LCNS_EXPIRED_DATE);
    if(iter==m_public_param.end())
        return LCS_PARAM_NOSET;
    param = iter->second;
    memcpy(buffer+offset,param.param_value.c_str(),param.param_value.length());
    offset += param.param_value.length();
    buffer[offset++] = LCNS_SEP;
    // 客户标识
    iter = m_public_param.find(LCNS_CUST_ID);
    if(iter==m_public_param.end())
        return LCS_PARAM_NOSET;
    param = iter->second;
    memcpy(buffer+offset,param.param_value.c_str(),param.param_value.length());
    offset += param.param_value.length();

    extend_file_buffer(LCNS_PARAM_MAX_LEN);

    /*
    offset = RSA_private_encrypt(offset,buffer,m_file_buffer,m_private_rsa,RSA_NO_PADDING);
    if(offset==-1)
    {
    	//ret = ERR_get_error();
    	return LCS_ENCRYPT_ERR;
    }
    */
    memcpy(m_file_buffer,buffer,offset);
    m_file_buffer_len = offset;
    return 0;

}
inline int ks_cardlib_license::write_file(FILE *fp,const unsigned char *buf,int len) {
    int r;
    r = fwrite(buf,len,1,fp);
    if(r != 1)
        return LCS_WRITE_FILE_ERR;
    return 0;
}

int ks_cardlib_license::save_data_file(unsigned char *encrypt_buffer,const std::string &value,int &pos) {
    int offset = 0;
    if(value.length() > LCNS_PARAM_MAX_LEN)
        return LCS_PARAM_FORMAT_ERR;
    offset += sprintf((char*)encrypt_buffer,"%c%d",LCNS_SEP,value.length());
    offset += sprintf((char*)encrypt_buffer+offset,"%c%s",LCNS_SEP,value.c_str());
    pos = offset;
    return 0;
}

int ks_cardlib_license::save_public_param(FILE *fp) {
    LICENSE_PARAM_TYPE::const_iterator iter;
    ks_cllcns_param_t param;
    int ret,offset,len;
    for(iter = m_public_param.begin(),len=0,offset=m_file_buffer_len; iter != m_public_param.end(); ++iter) {
        param = iter->second;
        std::string t = iter->first;
        if(param.param_name == LCNS_VERSION
                || param.param_name == LCNS_EXPIRED_DATE
                || param.param_name == LCNS_CUST_ID)
            continue;
        // 参数名
        if(t.length()+m_file_buffer_len > m_file_buffer_size) {
            if(extend_file_buffer(LCNS_EXTEND_SIZE))
                return LCS_LECK_MEMORY;
        }
        ret = save_data_file(m_file_buffer+offset,t,len);
        if(ret)
            return ret;
        offset += len;
        m_file_buffer_len += len;

        // 参数说明
        if(param.param_summary.length()+m_file_buffer_len > m_file_buffer_size) {
            if(extend_file_buffer(LCNS_EXTEND_SIZE))
                return LCS_LECK_MEMORY;
        }
        ret = save_data_file(m_file_buffer+offset,param.param_summary,len);
        if(ret)
            return ret;
        offset += len;
        m_file_buffer_len += len;

        // 参数值
        if(param.param_value.length()+m_file_buffer_len > m_file_buffer_size) {
            if(extend_file_buffer(LCNS_EXTEND_SIZE))
                return LCS_LECK_MEMORY;
        }
        ret = save_data_file(m_file_buffer+offset,param.param_value,len);
        if(ret)
            return ret;
        offset += len;
        m_file_buffer_len += len;

    }
    return 0;
}

int ks_cardlib_license::save_private_param(FILE *fp) {
    return 0;
}

int ks_cardlib_license::save_license_2_file(FILE *fp) {
    int ret,wr_len,len,sect_len;
    u_char buffer[LCNS_EXTEND_SIZE];
    char errmsg[256] = "";
    int RSA_SECT_LEN ;
    free_file_buffer();
    ret = save_license_header(fp);
    if(ret)
        return ret;
    // 保存参数内容
    ret = save_public_param(fp);
    if(ret)
        return ret;
    wr_len = 0;
    RSA_SECT_LEN = BN_num_bytes(m_private_rsa->n)-11;

    do {
        if(m_file_buffer_len - wr_len < RSA_SECT_LEN ) {
            sect_len = m_file_buffer_len - wr_len;
            len = RSA_private_encrypt(sect_len,m_file_buffer+wr_len,buffer,m_private_rsa,RSA_PKCS1_PADDING);
        } else {
            sect_len = RSA_SECT_LEN;
            len = RSA_private_encrypt(sect_len,m_file_buffer+wr_len,buffer,m_private_rsa,RSA_PKCS1_PADDING);
        }
        if(len == -1) {
            ERR_error_string(ERR_get_error(),errmsg);
            return LCS_ENCRYPT_ERR;
        }
        if(fwrite(buffer,len,1,fp)<=0)
            return LCS_WRITE_FILE_ERR;
        wr_len += sect_len;
    } while(wr_len < m_file_buffer_len);
    return 0;

}

int ks_cardlib_license::delete_param(const char *param_name) {
    LICENSE_PARAM_TYPE::iterator iter;
    iter = m_public_param.find(param_name);
    if(iter != m_public_param.end()) {
        m_public_param.erase(iter);
        return 0;
    } else {
        iter = m_private_param.find(param_name);
        if(iter != m_private_param.end()) {
            m_private_param.erase(iter);
            return 0;
        }
    }
    return -1;
}

void ks_cardlib_license::delete_all_param() {
    m_public_param.clear();
    m_private_param.clear();
}

int ks_cardlib_license::get_public_int_param(const char *param_name,int *param_value) {
    int ret;
    char v[1024+1];
    memset(v,0,sizeof v);
    ret = get_public_param(param_name,v,sizeof(v)-1);
    if(ret)
        return ret;
    *param_value = atoi(v);
    return 0;
}