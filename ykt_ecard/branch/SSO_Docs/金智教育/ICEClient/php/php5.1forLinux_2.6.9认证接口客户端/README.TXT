IDStar 2.1 PHP5.1.1认证接口
---------------------


软件编译环境
------------
Linux 2.6.9-1.667(fedora)
php 5.1.1
gcc 3.4.2


安装
----
把安装包解开放在 /opt/目录下
目录说明：
/opt/idstar/etc		配置文件目录
/opt/idstar/lib		库
/opt/idstar/php		PHP 接口源码
/opt/idstar/include	C 客户端头文件
/opt/idstar/doc     php接口api说明
/opt/idstar/example  php例程


配置客户端参数
------------
更新 /opt/idstar/etc/client.properties中的参数

ids.UserName = connet_username
ids.Password = connect_password
IdentityManager.Proxy=IdentityManager:tcp -p 20000 -h your_server_ip



配置PHP
-------
修改 $(PHP_HOME)/lib/php.ini 加入如下配置
extension_dir = /opt/idatar/lib
extension=libIdstarPhp.so


启动Apache
----------
在启动 apache前需要设置 库的加载路径，如下
export LD_LIBRARY_PATH=/opt/idstar/lib
apachectl start

或者加入到系统的搜索路径中去
编辑/etc/ld.so.conf 加入
/opt/idstar/lib

注：
  安装包提供的二进制文件是特定环境编制而成，如果软件版本有出入，可能存在需重新编译情况。 
