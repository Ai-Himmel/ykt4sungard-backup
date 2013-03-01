
package org.datacontract.schemas._2004._07.telerik_web;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOfRadTreeNodeData complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOfRadTreeNodeData">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="RadTreeNodeData" type="{http://schemas.datacontract.org/2004/07/Telerik.Web.UI}RadTreeNodeData" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOfRadTreeNodeData", propOrder = {
    "radTreeNodeData"
})
public class ArrayOfRadTreeNodeData {

    @XmlElement(name = "RadTreeNodeData", required = true, nillable = true)
    protected List<RadTreeNodeData> radTreeNodeData;

    /**
     * Gets the value of the radTreeNodeData property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the radTreeNodeData property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getRadTreeNodeData().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link RadTreeNodeData }
     * 
     * 
     */
    public List<RadTreeNodeData> getRadTreeNodeData() {
        if (radTreeNodeData == null) {
            radTreeNodeData = new ArrayList<RadTreeNodeData>();
        }
        return this.radTreeNodeData;
    }

}
