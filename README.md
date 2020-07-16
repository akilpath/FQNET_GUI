Qt based user interface for FQNET TDC

compile instructions:

1. install CENTOS 7 3.10.0-957.el7.x86_64

2. install GCC

3. install qt-opensource-linux-x64-5.12.3

4. add the user to the sudoers (wheel group), add the user to dialoutgroup

5. add libraries to bashrc

example


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/cptlab/Desktop/FQNET_GUI/lib/

6. reboot


7. open .pro file

8. run

9. requires for compile mesa-libGL-devel.x86_64 and GCC-G++

daisy (native qtag program) requires gt4 libraries. on centos is just intstall libqtgui4.. etc
on RHEL7 install sudo yum install qt-devel.x86_64 qt-devel.i686
