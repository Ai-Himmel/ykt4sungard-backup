package org.king.check.service;

import java.util.List;

import org.king.check.domain.TCustomer;

public interface CustomerService {
	
	public TCustomer getCustomer(Integer custId );
	
	public List  findCustomer(TCustomer cust);
	
	public TCustomer findCustByStuemp(String  stuemp) ;

}
