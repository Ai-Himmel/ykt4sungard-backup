
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.telerik_web.RadTreeNodeData;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="node" type="{http://schemas.datacontract.org/2004/07/Telerik.Web.UI}RadTreeNodeData" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "node"
})
@XmlRootElement(name = "GetChildOrganizationalUnits")
public class GetChildOrganizationalUnits {

    @XmlElementRef(name = "node", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<RadTreeNodeData> node;

    /**
     * Gets the value of the node property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link RadTreeNodeData }{@code >}
     *     
     */
    public JAXBElement<RadTreeNodeData> getNode() {
        return node;
    }

    /**
     * Sets the value of the node property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link RadTreeNodeData }{@code >}
     *     
     */
    public void setNode(JAXBElement<RadTreeNodeData> value) {
        this.node = ((JAXBElement<RadTreeNodeData> ) value);
    }

}
