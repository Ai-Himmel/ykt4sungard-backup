/*
 * Created Thu Sep 29 10:24:32 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.ecard.hibernate.tradedetail;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_TIF_TRADELOG' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TTifTradelog
    extends AbstractTTifTradelog
    implements Serializable
{
    /**
     * Simple constructor of TTifTradelog instances.
     */
    public TTifTradelog()
    {
    }

    /**
     * Constructor of TTifTradelog instances given a composite primary key.
     * @param id
     */
    public TTifTradelog(TTifTradelogKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
