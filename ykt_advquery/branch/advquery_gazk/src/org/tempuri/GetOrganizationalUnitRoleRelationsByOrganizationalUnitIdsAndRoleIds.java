
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
 *         &lt;element name="organizationalUnitIds" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
 *         &lt;element name="roleIds" type="{http://schemas.microsoft.com/2003/10/Serialization/Arrays}ArrayOfguid" minOccurs="0"/>
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
    "organizationalUnitIds",
    "roleIds"
})
@XmlRootElement(name = "GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds")
public class GetOrganizationalUnitRoleRelationsByOrganizationalUnitIdsAndRoleIds {

    @XmlElementRef(name = "organizationalUnitIds", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> organizationalUnitIds;
    @XmlElementRef(name = "roleIds", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfguid> roleIds;

    /**
     * Gets the value of the organizationalUnitIds property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getOrganizationalUnitIds() {
        return organizationalUnitIds;
    }

    /**
     * Sets the value of the organizationalUnitIds property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setOrganizationalUnitIds(JAXBElement<ArrayOfguid> value) {
        this.organizationalUnitIds = ((JAXBElement<ArrayOfguid> ) value);
    }

    /**
     * Gets the value of the roleIds property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public JAXBElement<ArrayOfguid> getRoleIds() {
        return roleIds;
    }

    /**
     * Sets the value of the roleIds property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfguid }{@code >}
     *     
     */
    public void setRoleIds(JAXBElement<ArrayOfguid> value) {
        this.roleIds = ((JAXBElement<ArrayOfguid> ) value);
    }

}
