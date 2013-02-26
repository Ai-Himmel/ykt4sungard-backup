package com.sungard.util;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.Component;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Vector;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-26
 */
public class ExportUtil {
    public static void exportExcel(File file, TableModel model) throws IOException {
        if (file == null) {
            return;
        }
        Workbook wb = new HSSFWorkbook();
        Sheet sheet = wb.createSheet("sheet");

        int columnCount = model.getColumnCount();
        int rowCount = model.getRowCount();
        for (int i = 0; i <= rowCount; i++) {
            Row row = sheet.createRow(i);
            for (int j = 0; j < columnCount; j++) {
                Cell cell = row.createCell(j);
                cell.setCellType(Cell.CELL_TYPE_STRING);
                if (i == 0) {
                    //create header
                    cell.setCellValue(model.getColumnName(j));
                } else {
                    Object value = model.getValueAt(i - 1, j);
                    cell.setCellValue(value == null ? "" : value.toString());
                }
            }
        }
        // Write the output to a file
        FileOutputStream fileOut = new FileOutputStream(file);
        wb.write(fileOut);
        fileOut.close();
    }

    public static File saveAs(Component parent) {
        File file = null;
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setAcceptAllFileFilterUsed(false);
        // 添加excel文件的过滤器
        fileChooser.addChoosableFileFilter(new ExportFileFilter("Excel 97-2003 工作簿(*.xls)", ".xls"));
        // 下面这句是去掉显示所有文件这个过滤器。
        int result = fileChooser.showSaveDialog(parent);
        // JFileChooser.APPROVE_OPTION是个整型常量，代表0。就是说当返回0的值我们才执行相关操作，否则什么也不做。
        if (result == JFileChooser.APPROVE_OPTION) {
            file = fileChooser.getSelectedFile();
            if (file.exists()) {
                if (!file.renameTo(file)) {
                    file = null;
                    JOptionPane.showMessageDialog(parent, "保存失败，文件被占用", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                String fileName = file.getAbsolutePath();
                if (!fileName.endsWith(".xls")) {
                    fileName += ".xls";
                }
                file = new File(fileName);
            }
        }
        return file;
    }

    public static void main(String[] args) throws IOException {
        DefaultTableModel model = new DefaultTableModel();
        model.addColumn("日期");
        model.addColumn("人数");
        model.addColumn("人次");
        model.addColumn("火车票（元）");
        model.addColumn("汽车票（元）");
        model.addColumn("证件费（元）");
        model.addColumn("其它一（元）");
        model.addColumn("其它二（元）");
        model.addColumn("合计（元）");
        for (int i = 0; i < 10; i++) {
            Vector row = new Vector();
            row.add("transDate");
            row.add("personNumber");
            row.add("payNumber");
            row.add("medicineFee");
            row.add("dressingFee");
            row.add("injectionFee");
            row.add("vaccineFee");
            row.add("otherFee");
            row.add("totalFee");
            model.addRow(row);
        }

        File file = saveAs(null);
        if (file != null) {
            exportExcel(file, model);
        }
    }
}
