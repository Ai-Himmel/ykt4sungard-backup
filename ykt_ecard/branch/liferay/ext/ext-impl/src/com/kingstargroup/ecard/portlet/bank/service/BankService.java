package com.kingstargroup.ecard.portlet.bank.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public interface BankService {
	
	public String getBankBindingAccount(TCustomer tcustomer,String stuempno)throws PortalException;
	public String updateBankBindingAccount(TCustomer tcustomer,String stuempno,String bankacc)throws PortalException;
	public boolean deleteBankBindingAccount(TCustomer tcustomer,String stuempno,boolean flag)throws PortalException;
	
	public String getLinkBankBindingAcc( String stuempno)throws PortalException;
	public void linkBindingOper( String stuempno,String bankAcc,String authcode,String operType)throws PortalException;
	
}
