unit def;

interface

const
  IP_LEN = 15;
  MAC_LEN = 18;
  CRC_LEN = 16;
  MODULE_NAME_LEN = 256;
  MAX_PATH_LEN = 1024;

  RET_OK = 1;
  RET_FAILD = 2;

type
  // 服务器定义
  ksf_server_conf = record
    ip : array[0..IP_LEN] of char;
    mac : array[0..MAC_LEN] of char;
    port : Integer;
  end;
  Pksf_server_conf = ^ksf_server_conf;
  
  // 接收数据包定义  
  ksf_xml_data = packed record
    length : Longint;               // 数据段长度
    func_no : Integer;              // 功能号
    count : Longint;                // 数据段中包含的 CARD 信息个数
    data : Char;// 数据段，内容为解密后的内容,以 '\0' 作为结尾符
  end;
  Pksf_xml_data = ^ksf_xml_data;

  // 返回结果定义
  ksf_ret_result = Integer;
  ksf_card_result = record
    ret : ksf_ret_result;         // 返回结果,可以是  RET_OK , RET_FAILD
    pack_index : Integer;         // 处理的包的 index
  end;
  Pksf_card_result = ^ksf_card_result;

  // 接口函数定义
  lp_module_init = function:Integer; stdcall;
  lp_module_release = function:Integer; stdcall;
  lp_module_receive = function(svr : Pksf_server_conf;
                              data : Pksf_xml_data;
                              result : Pksf_card_result):Integer; stdcall;

  ksf_plugin_module = record
    module_name : array[0..MODULE_NAME_LEN] of char;     	// 模块名称
    module_path : array[0..MAX_PATH_LEN] of char;         // 模块路径
    date : array[0..8] of char;                           // 日期
    author : array[0..255] of char;                       // 发行人
    major_ver : ShortInt;                                 // 主版本号、次版本号
    minor_ver : ShortInt;
    module_init : lp_module_init;                         // 模块初始化函数指针
    module_release : lp_module_release;                   // 模块释放函数指针
    module_receive : lp_module_receive;                   // 模块主功能函数，用与保存数据
  end;
  Pksf_plugin_module = ^ksf_plugin_module;

implementation

end.
