package org.king.security.service;

import org.king.framework.service.Service;

public interface PayManageService extends Service{
	public String epay(String str[]);
	
	public String epayerrorcode(String code);
	public String epaymd5errorcode(String v_oid,String v_status,String v_amount,String v_currency,String key);
}
