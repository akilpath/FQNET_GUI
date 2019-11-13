Qt based user interface for FQNET TDC

Set up instructions:

1. `git clone https://github.com/FermilabQuantumNetwork/FQNET_GUI.git`

2. install CENTOS 7 3.10.0-957.el7.x86_64

3. install GCC

4. install qt-opensource-linux-x64-5.12.3

5. add the user to the sudoers (wheel group) \
On centos: 
https://phoenixnap.com/kb/how-to-create-add-sudo-user-centos

6. add the user to dialoutgroup\
On centos: `usermod -a -G examplegroup exampleusername` \
https://www.howtogeek.com/50787/add-a-user-to-a-group-or-second-group-on-linux/

7. add the `/lib` folder to the end of bashrc file

On Centos, bashrc is located in `/etc/bashrc/' \

Example: \
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cptlab/Desktop/FQNET_GUI/lib/`

8. reboot

9. open .pro file

10. run


