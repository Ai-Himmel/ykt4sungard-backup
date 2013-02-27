package com.kingstargroup.form;

public class DictionaryResult extends AbstractResult {
	/** The value of the simple setsid property. */
	private Integer itemNo;

	/** The value of the simple setname property. */
	private String itemName;

	public String getItemName() {
		return itemName;
	}

	public void setItemName(String itemName) {
		this.itemName = itemName;
	}

	public Integer getItemNo() {
		return itemNo;
	}

	public void setItemNo(Integer itemNo) {
		this.itemNo = itemNo;
	}

	public DictionaryResult(Integer itemNo, String itemName) {
		super();
		// TODO Auto-generated constructor stub
		this.itemName = itemName;
		this.itemNo = itemNo;
	}

}
