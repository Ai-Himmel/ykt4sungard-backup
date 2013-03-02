package org.king.check.domain;

/**
 * TArea entity. @author MyEclipse Persistence Tools
 */

public class TArea extends AbstractTArea implements java.io.Serializable {

    // Constructors

    /** default constructor */
    public TArea() {
    }

	/** minimal constructor */
    public TArea(String areaCode) {
       super(areaCode);
    }
    
    /** full constructor */
    public TArea(String areaCode, String areaName, String fareaCode, Integer areaLevel, String addr, String remark, String oldareaCode) {
       super(areaCode, areaName, fareaCode, areaLevel, addr, remark, oldareaCode);
    }
}