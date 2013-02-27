MyEclipse Build ID: 20060122-4.1-GA
Date: 28th January 2006

Using custom templates with the MyEclipse 4.1.1 Hibernate Reverse-Engineering Process.

1) Unzip this archive into a convenient location. We recommend using a project
   in your Eclipse workspace.

2) Edit the velocity templates you are interested in customizing. 
   
   Note: 
   POJO templates are present in the pojo folder
   DAO template in the dao folder
   HBM templates in the hbm folder
   
3) Optional: Though not necessary, it is recommended that you delete the
   velocity templates you do not plan to customize. This will prevent future
   confusion over which templates are being processed by MyEclipse.

4) Invoke the Hibernate Reverse-Engineering wizard and select "Use custom 
   templates". Manually enter or click the browse button to select the 
   myeclipse_templates_4.1.1 folder. Note: the template location browser limits 
   select to projects in the current workspace. Non-workspace location must be 
   manually entered. (This location restriction will be lifted in MyEclipse 
   4.1.1).
   
   Warning: Do *not* select the dao, hbm or pojo folder, please select the 
            parent myeclipse_tempmlates_4.1.1 folder only.
   
5) During the code generation process, MyEclipse gives precedence to user
   defined templates by searching the custom template location prior to 
   consulting the internal templates shipped with MyEclipse 4.1.
   
   