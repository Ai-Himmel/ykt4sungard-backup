/*
 * Created Thu Mar 30 09:56:27 CST 2006 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.conference.hibernate.form;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_ATTENDEE_LIST' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TAttendeeList
    extends AbstractTAttendeeList
    implements Serializable
{
    /**
     * Simple constructor of TAttendeeList instances.
     */
    public TAttendeeList()
    {
    }

    /**
     * Constructor of TAttendeeList instances given a composite primary key.
     * @param id
     */
    public TAttendeeList(TAttendeeListKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
