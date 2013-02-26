package com.sungard;

import com.sungard.common.Configuration;
import com.sungard.print.AbstractDocument;
import com.sungard.print.PosDocument;
import com.sungard.print.Printer;

/**
 * .
 * User: Yiming.You
 * Date: 2011-7-7
 */
public class PrintServer {
    public static void main(String[] args) {
        Configuration.load();
        Printer printer = new Printer();
        AbstractDocument document = new PosDocument();
        String content = "火车票收款单<br>学号：20101132<br>姓名：张三<br>班级：计算机01<br>火车票：12.7元<br>汽车票:3元<br>证件费:7元<br>其它一:4元<br>其它二:0元<br>费用合计:26.7元<br>扣款员:游毅明<br>日期:2011-06-16 14:05";
        document.addPage(content);
        printer.setDocument(document);
        printer.print();
    }
}
