package com.kingstargroup.ecard;

import com.kingstar.bcc.bccclt;

public class BccctlInit {
	private static bccclt bcc = null;
	public static int drtpno = -1;
	private BccctlInit(){
		
	}
	public static bccclt getBccctlInstance(){
		if(null==bcc){
			bcc = new bccclt();
			bcc.BCCCLTInit(1);			
			bcc.XPackInit(1);
			drtpno = bcc.AddDrtpNode(KSConfiguration.getInstance().getProperty("drtpip").getBytes(), KSConfiguration.getInstance().getPropertyAsInt("drtpport",4000));
			return bcc;
		}else{
			return bcc;
		}
	}
}

