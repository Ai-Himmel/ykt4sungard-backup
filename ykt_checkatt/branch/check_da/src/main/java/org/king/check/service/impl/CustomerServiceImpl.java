package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.king.check.dao.CustomerDAO;
import org.king.check.domain.TCustomer;
import org.king.check.service.CustomerService;
import org.springframework.jdbc.core.JdbcTemplate;

public class CustomerServiceImpl implements CustomerService{
	
	private CustomerDAO customerDAO;
    
	private JdbcTemplate jdbcTemplate;

	public void setCustomerDAO(CustomerDAO customerDAO) {
		this.customerDAO = customerDAO;
	}

	public TCustomer getCustomer(Integer custId) {
	     return (TCustomer)customerDAO.getCustomer(custId);
		
	}

	public List findCustomer(TCustomer cust) {
		StringBuffer query =new StringBuffer(" from TCustomer c where 1=1 ");
		if(cust.getCustid()!=null && cust.getCustid().intValue()>0){
			query=query.append(" and c.custid=").append(cust.getCustid());
		}
		if(cust.getCustname()!=null && !"".equals(cust.getCustname())){
			query = query.append(" and c.custname = '").append(cust.getCustname()).append("'");
		}
		List list = customerDAO.find(query.toString());
		return list;
	}

	public TCustomer findCustByStuemp(String  stuemp) {           
	
		StringBuffer query =new StringBuffer(" from TCustomer c where c.status='1' ")
		      .append(" and c.stuempno='").append(stuemp).append("'");
		List list = customerDAO.find(query.toString());
		if(list !=null && list.size()>0){
			return (TCustomer)list.get(0);
		}
		return null;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
}
