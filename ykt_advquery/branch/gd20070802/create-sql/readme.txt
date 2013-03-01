我在redhat9上安装了最新商城的版本 验证码的图片就是出不来 
我装的linux服务器版 是不是linux不支持ttf格式？？


1、安装GD库
2、在profile 加上export CATALINA_OPTS=-Djava.awt.headless=true;

/root
vi .bash_profile
编辑
执行. .bash_profile
