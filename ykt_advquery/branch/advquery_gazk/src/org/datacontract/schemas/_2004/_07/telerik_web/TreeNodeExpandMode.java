
package org.datacontract.schemas._2004._07.telerik_web;

import javax.xml.bind.annotation.XmlEnum;
import javax.xml.bind.annotation.XmlEnumValue;


/**
 * <p>Java class for TreeNodeExpandMode.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * <p>
 * <pre>
 * &lt;simpleType name="TreeNodeExpandMode">
 *   &lt;restriction base="{http://www.w3.org/2001/XMLSchema}string">
 *     &lt;enumeration value="ClientSide"/>
 *     &lt;enumeration value="ServerSide"/>
 *     &lt;enumeration value="ServerSideCallBack"/>
 *     &lt;enumeration value="WebService"/>
 *   &lt;/restriction>
 * &lt;/simpleType>
 * </pre>
 * 
 */
@XmlEnum
public enum TreeNodeExpandMode {

    @XmlEnumValue("ClientSide")
    CLIENT_SIDE("ClientSide"),
    @XmlEnumValue("ServerSide")
    SERVER_SIDE("ServerSide"),
    @XmlEnumValue("ServerSideCallBack")
    SERVER_SIDE_CALL_BACK("ServerSideCallBack"),
    @XmlEnumValue("WebService")
    WEB_SERVICE("WebService");
    private final String value;

    TreeNodeExpandMode(String v) {
        value = v;
    }

    public String value() {
        return value;
    }

    public static TreeNodeExpandMode fromValue(String v) {
        for (TreeNodeExpandMode c: TreeNodeExpandMode.values()) {
            if (c.value.equals(v)) {
                return c;
            }
        }
        throw new IllegalArgumentException(v.toString());
    }

}
