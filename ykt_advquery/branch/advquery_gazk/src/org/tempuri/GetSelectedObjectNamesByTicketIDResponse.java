
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


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
 *         &lt;element name="GetSelectedObjectNamesByTicketIDResult" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
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
    "getSelectedObjectNamesByTicketIDResult"
})
@XmlRootElement(name = "GetSelectedObjectNamesByTicketIDResponse")
public class GetSelectedObjectNamesByTicketIDResponse {

    @XmlElementRef(name = "GetSelectedObjectNamesByTicketIDResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<String> getSelectedObjectNamesByTicketIDResult;

    /**
     * Gets the value of the getSelectedObjectNamesByTicketIDResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getGetSelectedObjectNamesByTicketIDResult() {
        return getSelectedObjectNamesByTicketIDResult;
    }

    /**
     * Sets the value of the getSelectedObjectNamesByTicketIDResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setGetSelectedObjectNamesByTicketIDResult(JAXBElement<String> value) {
        this.getSelectedObjectNamesByTicketIDResult = ((JAXBElement<String> ) value);
    }

}
