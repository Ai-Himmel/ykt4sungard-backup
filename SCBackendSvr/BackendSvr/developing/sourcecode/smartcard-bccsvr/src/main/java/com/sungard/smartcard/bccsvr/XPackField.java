/*
 * XPackField.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	XPackField.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

/**
 * XPack协议中的字段定义类.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-5
 * 
 */
public class XPackField {
    public final static String[] TYPE_NAME = new String[] { "null", // 0
            "char", // 1
            "vs_char", // 2
            "unsigned char", // 3
            "int", // 4
            "double", // 5
            "字段索引不存在或Handle错误" // -1
    };
    private int Col = 0;
    private String Name = null;
    private int Type = 0;
    private int Length = 0;

    public XPackField(int col, String name, int type, int len) {
        Col = col;
        Name = new String(name);
        Type = type;
        Length = len;
    }

    public int GetCol() {
        return Col;
    }

    public String GetName() {
        return Name;
    }

    public int GetType() {
        return Type;
    }

    public int GetLength() {
        return Length;
    }

    public static String GetTypeName(int type) {
        switch (type) {
        case -1:
            return TYPE_NAME[TYPE_NAME.length - 1];
        default:
            return TYPE_NAME[type];
        }
    }

    public String toString() {
        return "" + Col + ":" + Name + ":" + GetTypeName(Type) + ":" + Length;
    }
}
