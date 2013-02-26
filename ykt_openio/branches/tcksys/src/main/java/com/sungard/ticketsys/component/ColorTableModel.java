package com.sungard.ticketsys.component;

import java.util.Vector;

import javax.swing.table.AbstractTableModel;

public class ColorTableModel extends AbstractTableModel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private Vector<Object> rowData;
	private String columnNames[];

	public ColorTableModel(){
		
	}
	
	public Vector<Object> getRowData() {
		return rowData;
	}

	public void setRowData(Vector<Object> rowData) {
		this.rowData = rowData;
	}

	public String[] getColumnNames() {
		return columnNames;
	}

	public void setColumnNames(String[] columnNames) {
		this.columnNames = columnNames;
	}
	
	public int getColumnCount() {
		return columnNames.length;
	}

	public String getColumnName(int column) {
		return columnNames[column];
	}

	public int getRowCount() {
		return rowData.size();
	}

	public Object getValueAt(int row, int column) {
		Object[] obj = (Object[]) rowData.get(row);
		return obj[column];
	}

	@SuppressWarnings("rawtypes")
	public Class getColumnClass(int column) {
		return (getValueAt(0, column).getClass());
	}

	public void setValueAt(Object value, int row, int column) {
		Object[] obj = (Object[]) rowData.get(row);
		obj[column] = value;
	}

	public boolean isCellEditable(int row, int column) {
		return (column != 0);
	}
}