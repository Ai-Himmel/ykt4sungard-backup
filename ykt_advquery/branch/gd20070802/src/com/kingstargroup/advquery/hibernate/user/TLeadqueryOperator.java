/*
 * Created Wed Nov 09 18:55:23 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.advquery.hibernate.user;

import java.io.Serializable;
import java.util.Set;

/**
 * A class that represents a row in the 'T_LEADQUERY_OPERATOR' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TLeadqueryOperator
    extends AbstractTLeadqueryOperator
    implements Serializable
{
    /**
     * Simple constructor of TLeadqueryOperator instances.
     */
    public TLeadqueryOperator()
    {
    }

    /**
     * Constructor of TLeadqueryOperator instances given a simple primary key.
     * @param operCode
     */
    public TLeadqueryOperator(java.lang.String operCode)
    {
        super(operCode);
    }
    
    public void setFuncList(Set funcList) {
    	this.funcList = funcList;
    }
    
    public Set getFuncList() {
    	return funcList;
    }
    
    public void setStoreList(Set storeList) {
    	this.storeList = storeList;
    }
    
    public Set getStoreList() {
    	return storeList;
    }
    
    private Set funcList;
    private Set storeList;
    /* Add customized code below */

}
