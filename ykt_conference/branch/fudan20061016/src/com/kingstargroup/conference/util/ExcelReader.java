package com.kingstargroup.conference.util;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DecimalFormat;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.poifs.filesystem.POIFSFileSystem;

/**
 * @author Jimmy Liu
 */
public class ExcelReader {
    private POIFSFileSystem excelFile = null;//file
    private HSSFWorkbook wb = null;//book [includes sheet]
    private HSSFSheet sheet = null;
    private HSSFRow row = null;
    private HSSFCell cell = null; //cell,the content which contains
    private int sheetNum = 0;	//第sheetnum个工作表
    private int rowNum = 0;
    private FileInputStream fis = null;
    private String fileName = "";

    public ExcelReader() {
    }

    public ExcelReader(String fileName) {
        openFile(fileName);
    }

    public void setRowNum(int rowNum) {
        this.rowNum = rowNum;
    }

    public void setSheetNum(int sheetNum) {
        this.sheetNum = sheetNum;
    }

    /**
     * 读取excel文件获得HSSFWorkbook对象
     * @param fileName
     */
    public void openFile(String fileName) {
        this.fileName = fileName;
        File f = new File(fileName);
        if (f.exists()) {
            try {
                fis = new FileInputStream(f);
                excelFile = new POIFSFileSystem(fis);
                wb = new HSSFWorkbook(excelFile);
                fis.close();
                if(null == wb){
                }else{
                 //   System.out.println("WorkBook不为空");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("===========================>>>>>>>>>>>>>>>>>>>>>>>>>excel File  not exist");
        }
    }

    /**
     * 返回sheet表数目
     * @return int
     */
    public int getSheetCount() {
        int sheetCount = -1;
        sheetCount = wb.getNumberOfSheets();
        return sheetCount;
    }

    /**
     * sheetNum下的记录行数
     * @return int
     */
    public int getRowCount() {
        if(null == wb) System.out.println("=============>WorkBook为空");
        HSSFSheet sheet = wb.getSheetAt(this.sheetNum);
        int rowCount = -1;
        rowCount = sheet.getLastRowNum();
        return rowCount;
    }

    /**
     * 读取指定sheetNum的rowCount
     * @param sheetNum
     * @return int
     */
    public int getRowCount(int sheetNum) {
        HSSFSheet sheet = wb.getSheetAt(sheetNum);
        int rowCount = -1;
        rowCount = sheet.getLastRowNum();
        return rowCount;
    }

    /**
     * 得到指定行的内容
     * @param lineNum
     * @return String[]
     */
    public String[] readExcelLine(int lineNum) {
        return readExcelLine(this.sheetNum, lineNum);
    }

    /**
     * 指定工作表和行数的内容
     * @param sheetNum
     * @param lineNum
     * @return String[]
     */
    public String [] readExcelLine(int sheetNum, int lineNum) {
        if (sheetNum < 0 || lineNum < 0) return null;
        String[] strExcelLine = null;
        try {
            sheet = wb.getSheetAt(sheetNum);
            row = sheet.getRow(lineNum);

            int cellCount = row.getLastCellNum();

            strExcelLine = new String[cellCount];
            for (int i = 0; i < cellCount; i++) {
                strExcelLine[i] = "";
                if (null != row.getCell((short) i)) {
                    switch (row.getCell((short) i).getCellType()) {
                        case HSSFCell.CELL_TYPE_FORMULA :
                            strExcelLine[i] = "FORMULA ";
                            break;
                        case HSSFCell.CELL_TYPE_NUMERIC :
                            strExcelLine[i] = String.valueOf(row.getCell((short) i).getNumericCellValue());
                            break;
                        case HSSFCell.CELL_TYPE_STRING :
                            strExcelLine[i] = row.getCell((short) i).getStringCellValue();
                            break;
                        case HSSFCell.CELL_TYPE_BLANK :
                            strExcelLine[i] = "";
                            break;
                        default :
                            strExcelLine[i] = "";
                            break;
                    }
                    //如果读取的是科学计数法的格式，则转换为普通格式
                    //added by wangtongjun at 20060626
                    if (null != strExcelLine[i] &&
                            strExcelLine[i].indexOf(".") != -1 &&
                            strExcelLine[i].indexOf("E") != -1) {
                        DecimalFormat df = new DecimalFormat();
                        strExcelLine[i] = df.parse(strExcelLine[i]).toString();
                    }

                    //如果读取的是数字格式，并且以".0"结尾格式，则转换为普通格式
                    //added by wangtongjun at 20060713
                    if (null != strExcelLine &&
                            strExcelLine[i].endsWith(".0")) {
                        int size = strExcelLine[i].length();
                        strExcelLine[i] = strExcelLine[i].substring(0, size - 2);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return strExcelLine;
    }

    /**
     * 读取指定列的内容
     * @param cellNum
     * @return String 
     */
    public String readStringExcelCell(int cellNum) {
        return readStringExcelCell(this.rowNum, cellNum);
    }
    
    /**
     * 指定行和列编号的内容
     * @param rowNum
     * @param cellNum
     * @return String 
     */
    public String readStringExcelCell(int rowNum, int cellNum) {
        return readStringExcelCell(this.sheetNum, rowNum, cellNum);
    }

    /**
     * 指定工作表、行、列下的内容
     * @param sheetNum
     * @param rowNum
     * @param cellNum
     * @return String
     */
    public String readStringExcelCell(int sheetNum, int rowNum, int cellNum) {
        String strExcelCell = "";
        if (sheetNum < 0 || rowNum < 0) return null;

        try {
            sheet = wb.getSheetAt(sheetNum);
            row = sheet.getRow(rowNum);
            /**
             * modified by wangtongjun
             * bug description:
             * if the cell is empty ,the behind data can't get
             * for null point exception deal
             */
            if (null != row.getCell((short) cellNum)) { //add this condition judge
                switch (row.getCell((short) cellNum).getCellType()) {
                    case HSSFCell.CELL_TYPE_FORMULA :
                        strExcelCell = "FORMULA ";
                        break;

                    case HSSFCell.CELL_TYPE_NUMERIC : {
                        strExcelCell = String.valueOf(row.getCell((short) cellNum).getNumericCellValue());
                    }
                    break;

                    case HSSFCell.CELL_TYPE_STRING :
                        strExcelCell = row.getCell((short) cellNum).getStringCellValue();
                        break;
                    default :
                }
                //如果读取的是科学计数法的格式，则转换为普通格式
                //added by wangtongjun at 20060626
                if (null != strExcelCell &&
                        strExcelCell.indexOf(".") != -1 &&
                        strExcelCell.indexOf("E") != -1) {
                    DecimalFormat df = new DecimalFormat();
                    strExcelCell = df.parse(strExcelCell).toString();
                }

                //如果读取的是数字格式，并且以".0"结尾格式，则转换为普通格式
                //added by wangtongjun at 20060713
                if (null != strExcelCell &&
                        strExcelCell.endsWith(".0")) {
                    int size = strExcelCell.length();
                    strExcelCell = strExcelCell.substring(0, size - 2);
                }


            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return strExcelCell;
    }

    public void writeExcelLine(String fileName, String[] strLine) {
        try {
            File f = new File(fileName + ".xls");
            if (f.isFile()) {
                FileOutputStream fileOut = new FileOutputStream(f);
                sheet = wb.createSheet("Sheet1");
                row = sheet.createRow(0);
                int cellNum = strLine.length;
                for (int i = 0; i < cellNum; i++) {
                    row.createCell((short) i).setCellValue(strLine[i]);
                }
                wb.write(fileOut);
                fileOut.close();
            }
        }
        catch (FileNotFoundException e) {
        }
        catch (IOException e) {
        }
    }

    public void writeExcelLine(String fileName, String[] strLine, int iRownum) {
        try {
            File f = new File(fileName + ".xls");
            if (f.isFile()) {
                FileOutputStream fileOut = new FileOutputStream(f);
                sheet = wb.getSheet("Sheet1");
                if (null == sheet) {
                    sheet = wb.createSheet("Sheet1");
                }
                row = sheet.createRow(iRownum);
                int cellNum = strLine.length;
                for (int i = 0; i < cellNum; i++) {
                    HSSFCell cell = row.createCell((short)i);
                    cell.setEncoding(HSSFCell.ENCODING_UTF_16);
                    cell.setCellValue(strLine[i]);
                }
                wb.write(fileOut);
                fileOut.close();
            }
        }
        catch (FileNotFoundException e) {
        }
        catch (IOException e) {
        }
    }

    public void writeExcelCell(int sheetNum, int rowNum, int cellNum, String strCell) {
        sheet = wb.getSheetAt(sheetNum);
        row = sheet.getRow(rowNum);
        cell = row.getCell((short) cellNum);
        cell.setCellValue(strCell);
        try {
            File f = new File(fileName);
            if (f.isFile()) {
                FileOutputStream fileOut = new FileOutputStream(f);
                sheet = wb.createSheet("Sheet1");
                row = sheet.createRow(1);
                //int cellNum=strLine.length;
                for (int i = 0; i < 10; i++) {
                    //row.createCell((short)i).setCellValue(strLine[i]);
                }
                wb.write(fileOut);
                fileOut.close();
            }
        }
        catch (FileNotFoundException e) {
        }
        catch (IOException e) {
        }
    }


    public static void main(String args[]) throws Exception {
        ExcelReader readExcel = new ExcelReader();
        readExcel.openFile("C:\\all.xls");
        readExcel.setSheetNum(0);	//设置读取索引为0的工作表
        //总行数
        int count = readExcel.getRowCount();
        System.out.println(readExcel.readStringExcelCell(1, 5));
        for (int i = 0; i <= count; i++) {
            String[] rows = readExcel.readExcelLine(i);
            for (int j = 0; j < rows.length; j++) {
                System.out.print(j+" "+rows[j]+"  ");
            }
            System.out.print("\n");
        }


    }

}