1. 一卡通子系统在目录 yktsubsystem

    test子目录下为测试客户端，测试程序要求安装 python 2.3 版本
	代码中有两个常量
	HOST = 子系统 IP
	PORT = 子系统侦听端口
	testclient.py  [数据文件]      发送单包数据
	使用方法:
	    testclient.py -h [主机IP] -p [端口] [数据文件 ...]

    data1.xml 为测试数据文件

    yktsys.ini 为子系统配置文件
     	path = 为插件模块的路径
     	port = 为子系统侦听的端口号
    
2. 子系统插件模块在 simpleplugin 目录下 
    simpleplugin.cpp 为示例代码
    XMFile.cpp XMLFile.h 为 XML 文档解析类，该类要求系统安装了 msxml3
    ksf_pack.h 定义了 XML 中结点的常量

3.include 目录下为头文件
    def.h 所有结构的定义


系统结构是这样的,我提供一个服务端程序,这个程序用于接收收我们系统发送过来的数据，当服务端接收到正确的数据之后就会调用插件（DLL）的接口方法，你需要做的就是按照DLL接口开发处理数据的代码就可以了。Simplelplugin就是一个DLL规范例子，是用VC６。０编译的，这个稍做修改就可以在CBuilder６。０下使用。在Simpleplugin代码中有很详细的接口说明，在include/def.h文件中有数据包格式的说明。

         测试客户端是一个脚本程序，主要是用来模拟向你发送数据，这样就不需要由我来发送数据了。使用方法，先安装python　２。３，使用方法 testclient.py –h 127.0.0.1 data1.xml,这样就可以将data1.xml里的数据发送给服务端，你就可以测试你的DLL了。这个数据包你可以自己写。

         子系统有两个配置要注意。

         [CONNECT]

COUNT=3

ALLOWIP1=127.0.0.1

表示服务端允许接收来自这个IP的数据

[SERVER]

PORT=5000     ＃服务端使用的端口，不要修改

BINDIP=10.49.188.13　＃如果有两块以上的网卡就需要这个设置了。

         

         我们目前不提供Delphi的例子，不过你也可以按照C++代码修改成Delphi的程序，也是可以用的。

         下面是两个功能的数据包格式，你只需要使用这两个功能就可以了

 

功能号:400000 挂失,解挂,注销,换卡

<card-info>

         <card>

                   <phy-id>卡物理ID</phy-id>

                   <cardid>交易卡号</cardid>

                   <stuempno>学工号</stuempno>

                   <blk-version>版本号</blk-version>

                   <flag>标志 0:解挂,1:挂失,2注销,3:过期,9换卡 </flag>

         </card>

</card-info>

４０００００这个功能会发送所有的卡，包括临时卡，你可以过滤掉没有学工号的数据

 

功能号: 400002         发行新卡

<card-info>

         <card>

                   <card-id>交易卡号</card-id>

                   <phy-id>物理卡号</phy-id>

                   <stuemp>学工号</stuemp>

                   <dept>单位代码</dept>

                   <spc-fld>专业代码</spc-fld>

                   <exp-date>有效日期</exp-date>

                   <sex>性别代码</sex>

                   <cut-type>客户类别代码</cut-type>

                   <fee-type>收费类别代码</fee-type>

                   <flag>０：暂时不使用，默认为０</flag>

         </card>

</card-info>

４００００２这个功能会发送只有学工号的数据。所有代码都是由我们系统定义的，如果需要可以将这些字典表给你。


联系方式：
	汤成
	55664159
	msn : cashtang@msn.com
	email : cheng.tang@kingstargroup.com