size_t code_convert(const char *from_encoding, const char *to_encoding,const char *from_str, const size_t from_str_len,char **to_str, size_t *to_str_len);
size_t Ucs2leToGb2312(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len);
size_t Gb2312ToUcs2le(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len);
size_t Utf8ToGb2312(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len);
size_t Gb2312ToUtf8(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len);

