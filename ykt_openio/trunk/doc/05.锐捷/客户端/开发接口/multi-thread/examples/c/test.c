#include <stdio.h>
#include <windows.h> 

typedef char * (__stdcall *fCommand)(char *,char *,char *,int, char *);
typedef char * (__stdcall *fInit)(); 

char *ip;
char *managerId;
char *managerPass;
const static int port = 8443;

void testCmd(fCommand commondFunc, const char *cmdString)
{
	char *result;
	result = (commondFunc)(managerId, managerPass, ip, port, cmdString);
	printf("%s\r\n", result);
}

void main(int argc, char* argv[])
{
	HINSTANCE hinstLib = NULL;
    fInit init;
	fCommand command;

	if(argc < 4)
	{
		printf("Parameters: <ip> <manager id> <manager password>\r\n");
		return -1;
	}

	ip = argv[1];
	managerId = argv[2];
	managerPass = argv[3];

	//load dll
	hinstLib = LoadLibrary("samspiclient"); 	

	if (hinstLib != NULL)
	{
		//调用fInit函数进行初始化
		init = (fInit) GetProcAddress(hinstLib, "fInit"); 
		if (init != NULL)
		{
			(init)();
		}
	}

	command = (fCommand)GetProcAddress(hinstLib, "fCommandTS"); 
	if(NULL == command)
	{
		printf("error: function fCommandTS not found!\r\n");
		FreeLibrary(hinstLib);
		exit(2);
	}

	/****下面是各种命令得一些示例***********/
    //testCmd(command, "adduser:userid=\"bbb123456\",password=\"test123456\";");
    //testCmd(command, "adduser:userid=\"test\",password=\"111\",username=\"yj\",usergroupname=\"test\",sex=\"2\",freeauth=\"1\",certType=\"2\",certno=\"123123\",edu=\"3\",postcode=\"200237\",address=\"shanghai,xuhui\",tel=\"64765896\",mobile=\"139\",email=\"asf@asd.com\",usermac=\"aaaaaaaaaaaa\",nasip=\"192.168.0.231\",nasport=\"18\",authorIp=\"192.168.0.212\",filterId=\"abcd\",loginInfo=\"welcome\",userPrivilege=\"0\",uservlan=\"123\",userip=\"192.168.0.1\";");
	//testCmd(command, "adduser:userid=\"test3\",password=\"111\",usergroupname=\"mon\";");
    //testCmd(command, "ADDUSER:userid=\"test4\",passWORD=\"222\",userprivilege=\"23\",freeauthen=\"2\";");
	//testCmd(command, "queryUser:userid=\"wj\";");
	//testCmd(command, "moduser:userid=\"test3\",usergroupname=\"test\",atname=\"mon\";");
	//testCmd(command, "moduser:userid=\"test3\",atname=\"default\";");
	//testCmd(command, "moduser:userid=\"test3\",usergroupname=\"ROOT\";");
	//testCmd(command, "moduser:userid=\"test3\",password=\"111\",username=\"yj\",usergroupname=\"test\",sex=\"2\",freeauth=\"1\",certType=\"2\",certno=\"123123\",edu=\"3\",postcode=\"200237\",address=\"shanghai,xuhui\",tel=\"64765896\",mobile=\"139\",email=\"asf@asd.com\",usermac=\"aaaaaaaaaaaa\",nasip=\"192.168.0.231\",nasport=\"18\",authorIp=\"192.168.0.212\",filterId=\"abcd\",loginInfo=\"welcome\",userPrivilege=\"0\",uservlan=\"123\",userip=\"192.168.0.1\";");
	//testCmd(command, "moduser:userid=\"test3\",password=\"222\",username=\"aaa\",ADDRESS=\"~!@#$%^&*()_+|`-=\\{}[]:\";'<>?/.,\";");
	//testCmd(command, "moduser:userid=\"test3\",password=\"222\",USERGROUPNAME=\"test\",atname=\"test\";");
	//testCmd(command, "pay:userid=\"test2\",fee=\"123\";");
	//testCmd(command, "pay:userid=\"test2\",fee=\"12.12\";");
	//testCmd(command, "deluser:userid=\"test\";");
	//testCmd(command, "deluser:userid=\"TEST2\";");
	//testCmd(command, "queryar:userid=\"aaaa00000001\",fromdate=\"2005-06-02 13:33:30\",todate=\"2005-06-02 13:34:31\";");
	//testCmd(command, "queryar:userid=\"aaaa00000001\",fromdate=\"2005-06-02 13:33:30\";");
	//testCmd(command, "queryar:userid=\"wj\",todate=\"2008-01-01 13:34:31\";");
	//testCmd(command, "GETENCRYPTPASSWORD:PASSWORD=\"111\";");
	//testCmd(command, "queryLoginFailLog:userid=\"test\",fromdate=\"2005-06-16 15:31:46\",todate=\"2005-06-16 15:32:53\";");
	//testCmd(command, "queryLoginFailLog:userid=\"test\",fromdate=\"2005-06-16 15:31:46\";");
	//testCmd(command, "queryLoginFailLog:userid=\"test\",todate=\"2005-06-16 15:26:38\";");
	//testCmd(command, "suspenduser:userid=\"test2\";");
	//testCmd(command, "moduser:userid=\"test2\",atname=\"mon\";");

	testCmd(command, "GETENCRYPTPASSWORD:PASSWORD=\"111\";");

	testCmd(command, "adduser:userid=\"spi05\",password=\"111\",username=\"yj\",usergroupname=\"ROOT\",sex=\"2\",freeauth=\"1\",certType=\"2\",certno=\"123123\",edu=\"3\",postcode=\"200237\",address=\"上海,徐汇\",tel=\"64765896\",mobile=\"139\",email=\"asf@asd.com\",usermac=\"aaaaaaaaaaaa\",nasip=\"192.168.0.231\",nasport=\"18\",authorIp=\"192.168.0.212\",filterId=\"abcd\",loginInfo=\"welcome\",userPrivilege=\"0\",uservlan=\"123\",userip=\"192.168.0.1\";");

	testCmd(command, "VERIFYPASSWORD:USERID=\"spi05\",PASSWORD=\"111\";");

	testCmd(command, "queryUser:userid=\"spi05\";");

	testCmd(command, "moduser:userid=\"spi05\",password=\"222\",username=\"啊啊阿\",ADDRESS=\"~!@#$%^&*()_+|`-=\\{}[]:\";'<>?/.,\";");

	testCmd(command, "queryUser:userid=\"spi05\";");

	testCmd(command, "pay:userid=\"spi05\",fee=\"123\";");

	testCmd(command, "queryar:userid=\"spi05\",fromdate=\"2005-06-21 11:18:24\",todate=\"2005-06-21 11:18:29\";");

	testCmd(command, "queryLoginFailLog:userid=\"wj\",fromdate=\"2008-01-01 15:31:46\",todate=\"2008-06-16 15:32:52\";");

	testCmd(command, "deluser:userid=\"spi05\";");

    //退出时，free dll	
	FreeLibrary(hinstLib);
}
