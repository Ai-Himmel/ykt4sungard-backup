package com.kingstar.format;


public interface Formatter  {

	public boolean isNeedtime();

	public void setNeedtime(boolean needtime);
	
	public void setSeparator(String i) ;
	
	public String getFormatData();

}