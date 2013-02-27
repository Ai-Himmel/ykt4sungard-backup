package com.kingstargroup.form;

public class PositioResult extends AbstractResult{
 /** The value of the simple x property. */
    private java.lang.String x;

    /** The value of the simple y property. */
    private java.lang.Integer y;
    
    private java.lang.Integer pos;
    
    private java.lang.Integer flag;
    
  
	/**
	 * 
	 */
	public PositioResult() {
		super();
		// TODO Auto-generated constructor stub
	}


	/**
	 * @param x
	 * @param y
	 * @param pos
	 * @param flag
	 */
	public PositioResult(String x, Integer y, Integer pos, Integer flag) {
		this.x = x;
		this.y = y;
		this.pos = pos;
		this.flag = flag;
	}


	


	public java.lang.String getX() {
		return x;
	}


	public void setX(java.lang.String x) {
		this.x = x;
	}


	public java.lang.Integer getY() {
		return y;
	}


	public void setY(java.lang.Integer y) {
		this.y = y;
	}


	public java.lang.Integer getPos() {
		return pos;
	}


	public void setPos(java.lang.Integer pos) {
		this.pos = pos;
	}


	public java.lang.Integer getFlag() {
		return flag;
	}


	public void setFlag(java.lang.Integer flag) {
		this.flag = flag;
	}


}

