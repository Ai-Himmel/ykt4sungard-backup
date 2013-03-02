	Idstar2 Win32 接口说明

Idstar2 Win32的接口使用 Com对象，使用前需要
 (1) 将“IDStarV3.0认证接口\ICEClient\Win32\COM”下所有的.Dll文件拷贝到客户端应用所在服务器中的某一个目录下，建议目录名称为英文且全路径无空格。
 (2) 修改组件所在文件夹下的client.properties 文件，按照部署Java客户端的方法修改其中的参数。
 (3) 运行组件目录下的Reqiste或者直接输入命令regsvr32 idstar.dll进行注册。可以使用UnRegiste脚本进行反注册。

【注意】
（1）	当com组件应用在IIS服务器上的asp或者asp.net的时候，如果重新启动了Server端或者修改了Client端的配置，都要重新启动IIS服务器。
（2）	必须先修改client.properties再注册组件，修改该文件后需要重新注册




ASP和Php都调用 Com对象

Com对象接口说明：
ProgID :  Idstar.IdentityManager
接口：
String GetUserNameByID(String UserID) 取用户姓名, 
	参数：UserID——登录名
	返回：用户姓名

Variant GetUserAttribute(String UserID, String AttrName) 取用户的属性
	参数：	UserID——登录名	 
		AttrName —— 属性名
	返回：
		Vaiant 数组，属性存在多值，

Variant GetUserGroup(String UserID) 取用户组

....


	

