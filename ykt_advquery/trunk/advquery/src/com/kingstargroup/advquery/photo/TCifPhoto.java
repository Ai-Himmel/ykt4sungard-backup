/*
 * Created Wed Oct 19 16:43:23 CST 2005 by MyEclipse Hibernate Tool.
 */ 
package com.kingstargroup.advquery.photo;

import java.io.Serializable;

/**
 * A class that represents a row in the 'T_CIF_PHOTO' table. 
 * This class may be customized as it is never re-generated 
 * after being created.
 */
public class TCifPhoto
    extends AbstractTCifPhoto
    implements Serializable
{
    /**
     * Simple constructor of TCifPhoto instances.
     */
    public TCifPhoto()
    {
    }

    /**
     * Constructor of TCifPhoto instances given a composite primary key.
     * @param id
     */
    public TCifPhoto(TCifPhotoKey id)
    {
        super(id);
    }

    /* Add customized code below */

}
