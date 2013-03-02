/*
 * Created Tue Mar 28 13:47:05 CST 2006 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.conference.hibernate.form;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_DEV_CONFERENCE' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TDevConference
    extends AbstractTDevConference
    implements Serializable
{
    /**
     * Simple constructor of TDevConference instances.
     */
    public TDevConference()
    {
    }

    /**
     * Constructor of TDevConference instances given a composite primary key.
     * @param id
     */
    public TDevConference(TDevConferenceKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
