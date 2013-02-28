package com.kingstar.bcc;

import org.apache.commons.lang.StringUtils;
import org.king.common.Configuration;
import org.king.common.Constant;

public class BccctlInit {
    private static bccclt bcc = null;
    public static int drtpno1 = -1;
    public static int drtpno2 = -1;

    private BccctlInit() {
    }

    public static bccclt getBccctlInstance() {
        if (null == bcc) {
            bcc = new bccclt();
            bcc.BCCCLTInit(2);
            bcc.XPackInit(2);
            String drtpip1 = Configuration.getProperty(Constant.DRTPIP1);
            String drtpip2 = Configuration.getProperty(Constant.DRTPIP2);
            if (StringUtils.isNotBlank(drtpip1)) {
                drtpno1 = bcc.AddDrtpNode(Configuration.getProperty("drtpip1").getBytes(), Configuration.getIntProperty("drtpport1", 4000));
            }
            if (StringUtils.isNotBlank(drtpip2)) {
                drtpno2 = bcc.AddDrtpNode(Configuration.getProperty("drtpip2").getBytes(), Configuration.getIntProperty("drtpport2", 4000));
            }
            return bcc;
        } else {
            return bcc;
        }
    }
}

