/*
 * Created Wed Oct 19 14:07:21 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.advquery.shopposlog;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_CIF_SHOP_POS_LOG' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TCifShopPosLog
    extends AbstractTCifShopPosLog
    implements Serializable
{
    /**
     * Simple constructor of TCifShopPosLog instances.
     */
    public TCifShopPosLog()
    {
    }

    /**
     * Constructor of TCifShopPosLog instances given a composite primary key.
     * @param id
     */
    public TCifShopPosLog(TCifShopPosLogKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
