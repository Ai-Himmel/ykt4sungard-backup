/*
 * Created Tue Nov 14 13:16:00 CST 2006 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.form;

import java.io.Serializable;

/**
 * A class that represents a row in the 'MONITORS' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class Monitors
    extends AbstractMonitors
    implements Serializable
{
    /**
     * Simple constructor of Monitors instances.
     */
    public Monitors()
    {
    }

    /**
     * Constructor of Monitors instances given a composite primary key.
     * @param id
     */
    public Monitors(MonitorsKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
