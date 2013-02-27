package org.king.template.util;

import org.apache.commons.lang.StringUtils;

import java.util.List;
import java.util.Stack;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-4
 */
public class DeviceXmlUtil {
    /**
     * �����豸���νṹxml
     *
     * @param list .
     * @return .
     */
    public static String generateXml(List list) {
        if (list == null || list.size() == 0) {
            return "";
        }
        StringBuffer xml = new StringBuffer("<?xml version='1.0' encoding='UTF-8'?>");
        xml.append("<Root>");
        Object[] row;

        Stack stack = new Stack();
        for (int i = 0; i < list.size(); i++) {
            row = (Object[]) list.get(i);

            xml.append("<TreeNode ");
            xml.append("Title='").append(row[1]).append("'");
            if (row[3] != null && StringUtils.isNotBlank(row[3].toString())) {
                xml.append(" DisableData=\"").append(row[0]).append("\"");
            } else {
                xml.append(" CheckData=\"").append(row[0]).append("\"");
            }
            xml.append(" Checked=\"false\"");
            xml.append(" >");
            if (hasChild(list, i)) {
                stack.push(row[0]);
            } else {
                xml.append(" </TreeNode>");
                if (!hasUnvisitBrother(list, i)) {
                    //���ýڵ��Ѿ������һ���ڵ㣬Ϊstack��Ӧ�Ķ������ɽ�����ǩ
                    if (i == list.size() - 1) {
                        while (!stack.isEmpty()) {
                            stack.pop();
                            xml.append(" </TreeNode>");
                        }
                    } else {
                        //���ýڵ���нڵ㣬�ҵ������ڵ�ĸ��ڵ�id����ջ��Ԫ�س�ջ��֪�����������ڵ�ĸ��ڵ�id
                        Object nextFdeviceid = ((Object[]) list.get(i + 1))[2];
                        while (!stack.isEmpty()) {
                            if (nextFdeviceid.equals(stack.peek())) {
                                break;
                            }
                            xml.append(" </TreeNode>");
                            stack.pop();
                        }
                    }
                }
            }
        }
        xml.append("</Root>");
        return xml.toString();
    }

    /**
     * �ж��ڵ�ǰindex�����Ƿ����ӽڵ�
     *
     * @param list         .
     * @param currentIndex .
     * @return
     */
    private static boolean hasChild(List list, int currentIndex) {
        if (currentIndex == list.size() - 1) {
            return false;
        }
        Object currentDeviceid = ((Object[]) list.get(currentIndex))[0];
        Object nextFdeviceid = ((Object[]) list.get(currentIndex + 1))[2];
        return currentDeviceid.equals(nextFdeviceid);
    }

    /**
     * �ж��ڵ�ǰindex�����Ƿ����ֵܽڵ�
     *
     * @param list         .
     * @param currentIndex .
     * @return
     */
    private static boolean hasUnvisitBrother(List list, int currentIndex) {
        if (currentIndex == list.size() - 1) {
            return false;
        }
        Object currentFdeviceid = ((Object[]) list.get(currentIndex))[2];
        Object nextFdeviceid = ((Object[]) list.get(currentIndex + 1))[2];
        return currentFdeviceid.equals(nextFdeviceid);
    }
}
