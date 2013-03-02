package org.king.check.dao;

import org.king.check.domain.TCustomer;
import org.king.framework.dao.DAO;

import java.io.Serializable;
import java.util.List;


public interface CustomerDAO extends DAO {

    public TCustomer getCustomer(Serializable id);

    public List find(String query);

    public TCustomer getCustomerByStuempno(String stuempno);
}
