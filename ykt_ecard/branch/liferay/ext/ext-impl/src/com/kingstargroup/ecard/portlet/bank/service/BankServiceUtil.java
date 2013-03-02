package com.kingstargroup.ecard.portlet.bank.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public class BankServiceUtil {
	
	public static String getBankBindingAccount(TCustomer tcustomer,String stuempno)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		return bankService.getBankBindingAccount(tcustomer,stuempno);
	}
	
	public static String updateBankBindingAccount(TCustomer tcustomer,String stuempno,String bankacc)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		return bankService.updateBankBindingAccount(tcustomer, stuempno, bankacc);
	}
	
	public static boolean deleteBankBindingAccount(TCustomer tcustomer,String stuempno)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		return bankService.deleteBankBindingAccount(tcustomer,stuempno,true);
	}
	
	public static String getLinkBankBindingAcc( String stuempno)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		return bankService.getLinkBankBindingAcc(stuempno);
	}
	public static void linkBindingOper( String stuempno,String bankAcc,String operType)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		bankService.linkBindingOper(stuempno, bankAcc, "",operType);
	}
	
	public static void linkBindingOperWithAuth( String stuempno,String bankAcc,String authcode,String operType)throws PortalException{
		BankService bankService = BankServiceFactory.getService();
		bankService.linkBindingOper(stuempno, bankAcc, authcode,operType);
	}

}
