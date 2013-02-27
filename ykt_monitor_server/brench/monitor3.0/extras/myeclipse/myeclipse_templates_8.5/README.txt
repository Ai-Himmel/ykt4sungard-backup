MyEclipse Reverse-Engineering Templates

Version: 8.5
Minimum required MyEclipse version: 8.5

Using custom templates with the MyEclipse Reverse-Engineering Process:

1) Unzip this archive into a convenient location. We recommend using a project
   in your Eclipse workspace.

2) Edit the velocity templates you wish to customize.
   
Note: POJO templates are present in the pojo folder
      DAO template in the dao folder
      HBM templates in the hbm folder
   
3) Optional: Though not necessary, it is recommended that you delete the
   velocity templates you do not plan to customize. This will prevent future
   confusion over which templates are being processed by MyEclipse.

4) Invoke the JPA/EJB3/Hibernate Reverse-Engineering wizard and select 
   "Use custom templates". Manually enter or click the browse button to select the 
   myeclipse_templates_8.5 folder.
   
   Warning: Do *not* select the dao, hbm or pojo folder, please select the 
            parent myeclipse_templates_8.5 folder only.
   
During the code generation process, MyEclipse gives precedence to user
defined templates by searching the custom template location prior to 
consulting the internal templates shipped with MyEclipse.
   
   