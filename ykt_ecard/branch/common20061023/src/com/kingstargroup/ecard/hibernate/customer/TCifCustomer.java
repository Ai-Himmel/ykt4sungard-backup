/*
 * Created Tue Aug 30 06:04:05 GMT 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.ecard.hibernate.customer;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_CIF_CUSTOMER' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TCifCustomer
    extends AbstractTCifCustomer
    implements Serializable
{
    /**
     * Simple constructor of TCifCustomer instances.
     */
    public TCifCustomer()
    {
    }

    /**
     * Constructor of TCifCustomer instances given a simple primary key.
     * @param cutId
     */
    public TCifCustomer(java.lang.Integer cutId)
    {
        super(cutId);
    }

    /* Add customized code below */

}
