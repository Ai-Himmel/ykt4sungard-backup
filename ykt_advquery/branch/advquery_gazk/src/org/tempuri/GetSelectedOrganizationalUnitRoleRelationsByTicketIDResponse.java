
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
 *         &lt;element name="GetSelectedOrganizationalUnitRoleRelationsByTicketIDResult" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
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
    "getSelectedOrganizationalUnitRoleRelationsByTicketIDResult"
})
@XmlRootElement(name = "GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse")
public class GetSelectedOrganizationalUnitRoleRelationsByTicketIDResponse {

    @XmlElementRef(name = "GetSelectedOrganizationalUnitRoleRelationsByTicketIDResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> getSelectedOrganizationalUnitRoleRelationsByTicketIDResult;

    /**
     * Gets the value of the getSelectedOrganizationalUnitRoleRelationsByTicketIDResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getGetSelectedOrganizationalUnitRoleRelationsByTicketIDResult() {
        return getSelectedOrganizationalUnitRoleRelationsByTicketIDResult;
    }

    /**
     * Sets the value of the getSelectedOrganizationalUnitRoleRelationsByTicketIDResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setGetSelectedOrganizationalUnitRoleRelationsByTicketIDResult(JAXBElement<ArrayOfguid> value) {
        this.getSelectedOrganizationalUnitRoleRelationsByTicketIDResult = ((JAXBElement<ArrayOfguid> ) value);
    }

}
