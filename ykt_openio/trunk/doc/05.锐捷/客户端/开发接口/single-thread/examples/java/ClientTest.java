import com.star.sam.spiclient.SAMSPIClient;

public class ClientTest {
	public static void main(String[] args) {

    	if(args.length < 3){
    		System.out.println("Parameters: <ip> <manager id> <manager password>\r\n");
    		return;
    	}

    	final String ip = args[0];
    	final String managerId = args[1];
    	final String managerPass = args[2];

		String result = SAMSPIClient.login(managerId, managerPass, ip, 8443);
		System.out.println(result);

		String cmd = "adduser:userid=\"spi05\",password=\"111\",username=\"yj\",usergroupname=\"ROOT\",sex=\"2\",freeauth=\"1\",certType=\"2\",certno=\"123123\",edu=\"3\",postcode=\"200237\",address=\"ÉÏº£,Ðì»ã\",tel=\"64765896\",mobile=\"139\",email=\"asf@asd.com\",usermac=\"aaaaaaaaaaaa\",nasip=\"192.168.0.231\",nasport=\"18\",authorIp=\"192.168.0.212\",filterId=\"abcd\",loginInfo=\"welcome\",userPrivilege=\"0\",uservlan=\"123\",userip=\"192.168.0.1\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "queryUser:userid=\"spi05\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "moduser:userid=\"spi05\",password=\"222\",username=\"°¡°¡°¢\",ADDRESS=\"~!@#$%^&*()_+|`-=\\{}[]:\";'<>?/.,\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "queryUser:userid=\"spi05\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);
		
		cmd = "pay:userid=\"spi05\",fee=\"123\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "queryar:userid=\"spi05\",fromdate=\"2005-06-21 11:18:24\",todate=\"2005-06-21 11:18:29\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "queryLoginFailLog:userid=\"wj\",fromdate=\"2008-01-01 15:31:46\",todate=\"2008-06-16 15:32:52\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "suspenduser:userid=\"spi05\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);
		
		cmd = "GETENCRYPTPASSWORD:PASSWORD=\"111\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "VERIFYPASSWORD:USERID=\"test\",PASSWORD=\"111\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "deluser:userid=\"spi05\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);

		cmd = "REGUSER:userid=\"test5\",password=\"111\",username=\"yj\",usergroupname=\"test\","
			+ "sex=\"2\",freeauthen=\"1\",certType=\"2\",certno=\"123123\",edu=\"3\",postcode=\"200237\","
			+ "address=\"ÉÏº£,Ðì»ã\",tel=\"64765896\",mobile=\"139\",email=\"asf@asd.com\","
			+ "usermac=\"aaaaaaaaaaaa\",nasip=\"192.168.0.231\",nasport=\"18\",authorIp=\"192.168.0.212\","
			+ "filterId=\"abcd\",loginInfo=\"welcome\",userPrivilege=\"0\",uservlan=\"123\","
			+ "userip=\"192.168.0.1\",memo=\"±¸×¢\";";
		result = SAMSPIClient.command(cmd);
		System.out.println(result);
		
		result = SAMSPIClient.logout();
		System.out.println(result);
	}
}
