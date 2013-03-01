/*
 * Created Mon Dec 05 14:57:16 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.advquery.dept;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_CIF_DEPT' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TCifDept
    extends AbstractTCifDept
    implements Serializable
{
    /**
     * Simple constructor of TCifDept instances.
     */
    public TCifDept()
    {
    }
  

    /**
     * Constructor of TCifDept instances given a simple primary key.
     * @param deptCode
     */
    public TCifDept(java.lang.String deptCode)
    {
        super(deptCode);
    }

    /* Add customized code below */

}
