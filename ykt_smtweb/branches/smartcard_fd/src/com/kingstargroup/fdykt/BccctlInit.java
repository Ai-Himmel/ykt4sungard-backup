package com.kingstargroup.fdykt;

import com.kingstar.bcc.bccclt;

public class BccctlInit {
	private static bccclt bcc = null;
	public static int drtpno = -1;
	private BccctlInit(){
		
	}
	public static bccclt getBccctlInstance(){
		if(null==bcc){
			bcc = new bccclt();
			//bcc.BCCCLTInit(1);			
			bcc.XPackInit(1);
				
			drtpno = bcc.AddDrtpNode(KSConstant.DRTP_IP.getBytes(), KSConstant.DRTP_PORT);
			return bcc;
		}else{
			return bcc;
		}
	}
}

