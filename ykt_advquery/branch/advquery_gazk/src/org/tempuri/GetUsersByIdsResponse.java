
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ArrayOfUser;


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
 *         &lt;element name="GetUsersByIdsResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfUser" minOccurs="0"/>
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
    "getUsersByIdsResult"
})
@XmlRootElement(name = "GetUsersByIdsResponse")
public class GetUsersByIdsResponse {

    @XmlElementRef(name = "GetUsersByIdsResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfUser> getUsersByIdsResult;

    /**
     * Gets the value of the getUsersByIdsResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfUser }{@code >}
     *     
     */
    public JAXBElement<ArrayOfUser> getGetUsersByIdsResult() {
        return getUsersByIdsResult;
    }

    /**
     * Sets the value of the getUsersByIdsResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfUser }{@code >}
     *     
     */
    public void setGetUsersByIdsResult(JAXBElement<ArrayOfUser> value) {
        this.getUsersByIdsResult = ((JAXBElement<ArrayOfUser> ) value);
    }

}
