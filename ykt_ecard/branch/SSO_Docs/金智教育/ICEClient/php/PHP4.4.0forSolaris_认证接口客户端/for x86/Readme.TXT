IDStar2.1 PHP4 认证接口部署说明文档
---------------------
操作系统:solaris10
芯片:x86
php版本:php4.4.6
gcc版本:3.3.2


安装
----
把安装包解开放在 /opt/目录下
目录说明：
/opt/idstar/etc		配置文件目录
/opt/idstar/lib		库
/opt/idstar/include	C 客户端头文件



配置客户端参数
------------
更新 /opt/idstar/etc/client.properties中的参数

ids.UserName = connet_username
ids.Password = connect_password
IdentityManager.Proxy=IdentityManager:tcp -p 20000 -h your_server_ip



配置PHP
-------
修改 $(PHP_HOME)/lib/php.ini 加入如下配置
extension_dir = /opt/idstar/lib
extension=libIdstarPhp.so


启动Apache
----------
在启动 apache前需要设置 库的加载路径，如下
export LD_LIBRARY_PATH=/opt/idstar/lib
apachectl start





