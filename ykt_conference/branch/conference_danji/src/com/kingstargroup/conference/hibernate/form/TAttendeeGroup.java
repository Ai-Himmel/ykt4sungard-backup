/*
 * Created Thu Mar 30 09:56:03 CST 2006 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.conference.hibernate.form;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_ATTENDEE_GROUP' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TAttendeeGroup
    extends AbstractTAttendeeGroup
    implements Serializable
{
    /**
     * Simple constructor of TAttendeeGroup instances.
     */
    public TAttendeeGroup()
    {
    }

    /**
     * Constructor of TAttendeeGroup instances given a composite primary key.
     * @param id
     */
    public TAttendeeGroup(TAttendeeGroupKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
