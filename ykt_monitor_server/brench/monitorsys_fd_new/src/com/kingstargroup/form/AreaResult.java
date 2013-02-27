package com.kingstargroup.form;

public class AreaResult extends AbstractResult{
 /** The value of the simple setsid property. */
    private java.lang.Integer itemNo;

    /** The value of the simple setname property. */
    private java.lang.String itemName;
    
    public java.lang.String getItemName() {
		return itemName;
	}

	public void setItemName(java.lang.String itemName) {
		this.itemName = itemName;
	}

	public java.lang.Integer getItemNo() {
		return itemNo;
	}

	public void setItemNo(java.lang.Integer itemNo) {
		this.itemNo = itemNo;
	}

	public AreaResult(Integer itemNo,String itemName) {
		super();
		// TODO Auto-generated constructor stub
		this.itemName = itemName;
		this.itemNo = itemNo;
	}


}

