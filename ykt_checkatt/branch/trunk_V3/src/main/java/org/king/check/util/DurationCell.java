package org.king.check.util;

import org.extremecomponents.table.bean.Column;
import org.extremecomponents.table.cell.AbstractCell;
import org.extremecomponents.table.core.TableModel;

public class DurationCell extends AbstractCell {

	@Override
	protected String getCellValue(TableModel model, Column column) {
		Object value = column.getValue();
		String duration = "";
		if (value != null) {
			try {
				duration = DateUtilExtend.getDuration(Integer.parseInt(value.toString()));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return duration;
	}
}
