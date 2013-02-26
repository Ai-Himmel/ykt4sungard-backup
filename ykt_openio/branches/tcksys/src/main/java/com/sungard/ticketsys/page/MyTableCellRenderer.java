package com.sungard.ticketsys.page;

import javax.swing.table.DefaultTableCellRenderer;

public class MyTableCellRenderer extends DefaultTableCellRenderer {
	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	public MyTableCellRenderer() {
		super();
	}

	public void setValue(Object value) {
		super.setValue(value);
	}
/*	
 * 改变JTable的背景色
	public Component getTableCellRendererComponent(JTable table, 
	           Object value, boolean isSelected,boolean cellHasFocus, 
	           int row,int col) { 
	    
	         switch(row){ 
	         case 0: 
	         case 1: 
	              this.setBackground(Color.red); 
	              break; 
	         case 2: 
	         case 3: 
	              this.setBackground(Color.blue); 
	              break; 
	         } 
	   if(isSelected){ 
	      //这里写如果�?中后你想表现出来的效�?    
	   } 
	   if(cellHasFocus){ 
	      //这里写如果获得焦点后你想表现出来的效�?    

	   } 
	   this.setText((String)value); 
	   return this; 
	   }*/
}
