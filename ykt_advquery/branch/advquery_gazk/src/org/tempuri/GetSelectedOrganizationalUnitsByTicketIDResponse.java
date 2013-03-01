
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;


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
 *         &lt;element name="GetSelectedOrganizationalUnitsByTicketIDResult" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
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
    "getSelectedOrganizationalUnitsByTicketIDResult"
})
@XmlRootElement(name = "GetSelectedOrganizationalUnitsByTicketIDResponse")
public class GetSelectedOrganizationalUnitsByTicketIDResponse {

    @XmlElementRef(name = "GetSelectedOrganizationalUnitsByTicketIDResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> getSelectedOrganizationalUnitsByTicketIDResult;

    /**
     * Gets the value of the getSelectedOrganizationalUnitsByTicketIDResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getGetSelectedOrganizationalUnitsByTicketIDResult() {
        return getSelectedOrganizationalUnitsByTicketIDResult;
    }

    /**
     * Sets the value of the getSelectedOrganizationalUnitsByTicketIDResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setGetSelectedOrganizationalUnitsByTicketIDResult(JAXBElement<ArrayOfguid> value) {
        this.getSelectedOrganizationalUnitsByTicketIDResult = ((JAXBElement<ArrayOfguid> ) value);
    }

}
