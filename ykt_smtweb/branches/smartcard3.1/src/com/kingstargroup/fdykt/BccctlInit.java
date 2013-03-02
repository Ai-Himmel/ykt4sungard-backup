package com.kingstargroup.fdykt;

import com.kingstar.bcc.bccclt;

public class BccctlInit {
	private static bccclt bcc = null;
	public static int drtpno1 = -1;
	public static int drtpno2 = -1;
	private BccctlInit(){
		
	}
	public static bccclt getBccctlInstance(){
		if(null==bcc){
			bcc = new bccclt();
			bcc.BCCCLTInit(2);			
			bcc.XPackInit(2);
			drtpno1 = bcc.AddDrtpNode(KSConfiguration.getInstance().getProperty("drtpip1").getBytes(), KSConfiguration.getInstance().getPropertyAsInt("drtpport1",4000));
			drtpno2 = bcc.AddDrtpNode(KSConfiguration.getInstance().getProperty("drtpip2").getBytes(), KSConfiguration.getInstance().getPropertyAsInt("drtpport2",4000));
			return bcc;
		}else{
			return bcc;
		}
	}
}

