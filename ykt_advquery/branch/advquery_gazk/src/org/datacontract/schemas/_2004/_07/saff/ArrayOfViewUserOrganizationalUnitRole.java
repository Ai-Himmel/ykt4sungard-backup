
package org.datacontract.schemas._2004._07.saff;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOfView_User_OrganizationalUnit_Role complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOfView_User_OrganizationalUnit_Role">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="View_User_OrganizationalUnit_Role" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}View_User_OrganizationalUnit_Role" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOfView_User_OrganizationalUnit_Role", propOrder = {
    "viewUserOrganizationalUnitRole"
})
public class ArrayOfViewUserOrganizationalUnitRole {

    @XmlElement(name = "View_User_OrganizationalUnit_Role", required = true, nillable = true)
    protected List<ViewUserOrganizationalUnitRole> viewUserOrganizationalUnitRole;

    /**
     * Gets the value of the viewUserOrganizationalUnitRole property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the viewUserOrganizationalUnitRole property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getViewUserOrganizationalUnitRole().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link ViewUserOrganizationalUnitRole }
     * 
     * 
     */
    public List<ViewUserOrganizationalUnitRole> getViewUserOrganizationalUnitRole() {
        if (viewUserOrganizationalUnitRole == null) {
            viewUserOrganizationalUnitRole = new ArrayList<ViewUserOrganizationalUnitRole>();
        }
        return this.viewUserOrganizationalUnitRole;
    }

}
