/*
 * Created Thu Sep 01 09:31:37 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.ecard.hibernate.account;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_AIF_ACCOUNT' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TAifAccount
    extends AbstractTAifAccount
    implements Serializable
{
    /**
     * Simple constructor of TAifAccount instances.
     */
    public TAifAccount()
    {
    }

    /**
     * Constructor of TAifAccount instances given a simple primary key.
     * @param accountId
     */
    public TAifAccount(java.lang.String accountId)
    {
        super(accountId);
    }

    /* Add customized code below */

}
