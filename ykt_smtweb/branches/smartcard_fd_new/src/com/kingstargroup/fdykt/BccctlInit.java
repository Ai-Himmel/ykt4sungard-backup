package com.kingstargroup.fdykt;

import com.kingstar.bcc.bccclt;

public class BccctlInit {
	private static bccclt bcc = null;
	public static int drtpno1 = -1;
	public static int drtpno2 =-1;
	private BccctlInit(){
		
	}
	public static bccclt getBccctlInstance(){
		
		if(null==bcc){
			
			bcc = new bccclt();
			//System.out.println("--new bccclt()-");
			bcc.BCCCLTInit(2);			
			//System.out.println("--BCCCLTInit-");
			bcc.XPackInit(2);
			//System.out.println("--XPackInit-");
			drtpno1 = bcc.AddDrtpNode(KSConfiguration.getInstance().getProperty("drtpip").getBytes(), KSConfiguration.getInstance().getPropertyAsInt("drtpport",4000));
			drtpno2 = bcc.AddDrtpNode(KSConfiguration.getInstance().getProperty("qcdrtpip").getBytes(), KSConfiguration.getInstance().getPropertyAsInt("drtpport",4000));
			return bcc;
		}else{
			//System.out.println("--bcc- not null-");
			return bcc;
		}
	}
}

